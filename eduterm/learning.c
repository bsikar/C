/* MIT License
 *
 * Copyright (c) 2021 Brighton Sikarskie
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define _XOPEN_SOURCE 600 // posix_openpt(), grantpt(), unlockpt() ...
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <ctype.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

const char* shell = "/bin/sh";

/* pty - pseudoterminal interfaces
 * `man pty`: 
 * A pseudoterminal (sometimes abbreviated "pty") is a pair of
 * virtual character devices that provide a bidirectional
 * communication channel.  One end of the channel is called the
 * master; the other end is called the slave.
 */
struct PTY {
    int master;
    int slave;
};

/* X - a portable, network-transparent window system
 * The  X Window System is a network transparent window system which runs on a wide range of computing and
 * graphics machines.  It should be relatively straightforward to build the X.Org Foundation software dis-
 * tribution  on  most  ANSI C and POSIX compliant systems.  Commercial implementations are also available
 * for a wide range of platforms.
 */
struct X11 {
    /* fd - file descriptor
     * To the kernel, all open files are referred to by File Descriptors. 
     * A file descriptor is a non-negative number, but I am specifing int here
     * instead of unsigned int because PTY.master and PTY.slave must be int. 
     */
    int fd;
    /* dpy - short for display
     * Display - Specifies the connection to the X server.
     */
    Display* dpy;
    /* screen - screen
     * Screen is a terminal program in Linux which allows us to use a virtual
     * as full-screen window manager 
     */
    int screen;
    /* root - the parent/root window
     * Specifies the parent window 
     */
    Window parent;
    /* termwin - the terminal window
     * termwin is drawable which is input only
     * A drawable could be a window or a pixmap
     */
    Drawable termwin;
    /* GC - graphics context
     * Graphics context -
     * Various information for graphics output is stored in a graphics context such as foreground
     * pixel, background pixel, line width, clipping region, and so on. A graphics context can
     * only be used with drawables that have the same root and the same depth as the graphics
     * context.
     */
    GC termgc;
    /* col_fg - the color of the foreground
     * col_bg - the color of the background
     */
    unsigned long col_fg;
    unsigned long col_bg;
    /* w - width, takes in account for the font size
     * h - height, takes in account for the font size
     * w - the width of the drawable on the display
     * h - the height of the drawable on the display
     */
    unsigned int w;
    unsigned int h;
    /* XFontStruct is a struct
     * xfont - specifies the font used
     */
    XFontStruct* xfont;
    /* font_width - the width of the font, can be used for dimentions
     * font_height - the height of the font, can be used for dimentions
     */
    unsigned int font_width;
    unsigned int font_height;
    /* buf - the buffer for text that will get displayed
     * buf_w - how many characters are in each row
     * buf_h - how many characters are in each col
     * buf_x - the buffer for the curser x cordinate
     * buf_y - the buffer for the curser y cordinate
     */
    char* buf;
    unsigned int buf_w;
    unsigned int buf_h;
    unsigned int buf_x;
    unsigned int buf_y;
};

bool set_term_size(struct PTY*, struct X11*);
bool pt_pair(struct PTY*);
void x11_key(XKeyEvent *, struct PTY*);
void x11_redraw(struct X11*);

int main(void) {
    struct PTY pty;
    struct X11 x11;
    
    if (!set_term_size(&pty, &x11)) {
        return 1;
    }
    if ( !pt_pair(&pty)) {
        return 1;
    }

    return 0;
}

bool set_term_size(struct PTY *pty, struct X11 *x11) {
    struct winsize ws = {
        .ws_col = x11->buf_w,
        .ws_row = x11->buf_h
    };
    /* This is the very same ioctl that normal programs use to query the
     * window size. Normal programs are actually able to do this, too,
     * but it makes little sense: Setting the size has no effect on the
     * PTY driver in the kernel (it just keeps a record of it) or the
     * terminal emulator. IIUC, all that's happening is that subsequent
     * ioctls will report the new size -- until another ioctl sets a new
     * size.
     *
     * I didn't see any response to ioctls of normal programs in any of
     * the popular terminals (XTerm, VTE, st). They are not informed by
     * the kernel when a normal program issues an ioctl like that.
     *
     * On the other hand, if we were to issue this ioctl during runtime
     * and the size actually changed, child programs would get a
     * SIGWINCH.
     *
     *
     * man ioctl_tty.2:
     * TIOCSWINSZ      const struct winsize *argp 
     *              Set window size. 
     * The struct used by these ioctls is defined as 
     *
     * struct winsize { 
     *          unsigned short ws_row; 
     *          unsigned short ws_col; 
     *          unsigned short ws_xpixel; // unused
     *          unsigned short ws_ypixel; // unused 
     * }; 
     *
     * When the window size changes, a SIGWINCH signal is sent to the foreground process group. 
     *
     * SIGWINCH - signal window [size] change, it is used to signal a change in window size
     */
    if (ioctl(pty->master, TIOCSWINSZ, &ws) == -1) {
        return false;
    }
    return true;
}

bool pt_pair(struct PTY* pty) {
    char* slave_name;

    /* Opens the PTY master device. This is the file descriptor that
     * we're reading from and writing to in our terminal emulator.
     *
     * We're going for BSD-style management of the controlling terminal:
     * Don't try to change anything now (O_NOCTTY), we'll issue an
     * ioctl() later on.
     *
     * O_RDWR: This argument flag, this request opens the file read/write.
     * O_NOCTTY: This creation flag:
     *   prevent the OS from assigning the opened 
     *   file as the process's controlling terminal 
     *   when opening a TTY device file
     */
    pty->master = posix_openpt(O_RDWR | O_NOCTTY);
    if (pty->master == -1) {
        perror("posix_openpt");
        return false;
    }
    /* grantpt() and unlockpt() are housekeeping functions that have to
     * be called before we can open the slave FD. Refer to the man pages
     * on what they do.
     */
    if (grantpt(pty->master) == -1 || unlockpt(pty->master) == -1) {
        perror("grantpt");
        return false;
    }
    /* Up until now, we only have the master FD. We also need a file
     * descriptor for our child process. We get it by asking for the
     * actual path in /dev/pts which we then open using a regular
     * open(). So, unlike pipe(), you don't get two corresponding file
     * descriptors in one go.
     */
    slave_name = ptsname(pty->master);
    if (slave_name == NULL) {
        perror("ptsname");
        return false;
    }
    pty->slave = open(slave_name, O_RDWR | O_NOCTTY);
    if (pty->slave == -1) {
        perror("open(slave_name)");
        return false;
    }
    return true;
}

void x11_key(XKeyEvent* ev, struct PTY* pty) {
    /* I have no clue why this is 32 here
     */
    char buf[32];
    KeySym ksym;
    int num = XLookupString(ev, buf, sizeof buf, &ksym, 0);
    for (int i = 0; i < num; ++i) {
        write(pty->master, &buf[i], 1);
    }
}

void x11_redraw(struct X11* x11) {
    /* I do not know why 1 is here
     */
    char buf[1];
}
