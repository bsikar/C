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

#define _DEFAULT_SOURCE // this is for usleep()
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

#define SNAKE_BODY 'O'
#define SNAKE_FOOD '@'
#define SNAKE_TICK 75000
#define WIDTH      40
#define HEIGHT     20

enum Direction {
    LEFT,
    RIGHT,
    DOWN,
    UP,
    STILL
};

struct Position {
    int x;
    int y;
};

struct Snake {
    struct Position position;
    int length;
    enum Direction direction;
    struct Position tail[(WIDTH*HEIGHT)-1];
};

int main(void) {
    srand(time(NULL));
    struct Snake snake = {{WIDTH/2, HEIGHT/2}, 1, STILL, {{WIDTH/2, HEIGHT/2}}};
    struct Position food = {rand()%WIDTH, rand()%HEIGHT};

    initscr();
    timeout(0);
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    for (;;) {
        switch (tolower(getch())) {
        case 'q':
        case 27: // esc key
            goto end;
        case 'w':
        case 'k':
        case KEY_UP:
            if (snake.direction != DOWN) {
                snake.direction = UP;
            }
            break;
        case 'a':
        case 'h':
        case KEY_LEFT:
            if (snake.direction != RIGHT) {
                snake.direction = LEFT;
            }
            break;
        case 's':
        case 'j':
        case KEY_DOWN:
            if (snake.direction != UP) {
                snake.direction = DOWN;
            }
            break;
        case 'd':
        case 'l':
        case KEY_RIGHT:
            if (snake.direction != LEFT) {
                snake.direction = RIGHT;
            }
            break;
        default:
            break;
        }

        switch (snake.direction) {
        case LEFT:
            --snake.position.x;
            break;
        case RIGHT:
            ++snake.position.x;
            break;
        case DOWN:
            ++snake.position.y;
            break;
        case UP:
            --snake.position.y;
            break;
        case STILL:
            break;
        }

        if (snake.position.x == food.x && snake.position.y == food.y) {
            ++snake.length;
            food.x = rand() % WIDTH;
            food.y = rand() % HEIGHT;
        }

        if (snake.position.x < 0
                || snake.position.x >= WIDTH
                || snake.position.y < 0
                || snake.position.y >= HEIGHT) {
            goto end;
        }

        int x1 = snake.tail[0].x;
        int y1 = snake.tail[0].y;
        snake.tail[0].x = snake.position.x;
        snake.tail[0].y = snake.position.y;
        int x2, y2;
        for (int i = 1; i < snake.length; ++i) {
            x2 = snake.tail[i].x;
            y2 = snake.tail[i].y;
            snake.tail[i].x = x1;
            snake.tail[i].y = y1;
            x1 = x2;
            y1 = y2;
        }

        erase();
        for (int y = -1; y <= HEIGHT; ++y) {
            for (int x = -1; x <= WIDTH; ++x) {
                if (x < WIDTH && y < HEIGHT
                        && x >= 0 && y >= 0) {
                    if (x == snake.position.x && y == snake.position.y) {
                        addch(SNAKE_BODY);
                    } else if (x == food.x && y == food.y) {
                        addch(SNAKE_FOOD);
                    } else {
                        bool didPrint = false;
                        for (int i = 0; i < snake.length; ++i) {
                            if (snake.position.x == snake.tail[i].x
                                    && snake.position.y == snake.tail[i].y
                                    && i != 0) {
                                goto end;
                            } else if (x == snake.tail[i].x
                                    && y == snake.tail[i].y) {
                                addch(SNAKE_BODY);
                                didPrint = true;
                                break;
                            }
                        }
                        if (!didPrint) {
                            addch(' ');
                        }
                    }
                } else {
                    addch('*');
                }
            }
            addch('\n');
        }
        printw("Press Q to Quit\tScore: %d", snake.length);
        refresh();
        if (snake.direction == UP || snake.direction == DOWN) {
            usleep(SNAKE_TICK + 30000);
        } else {
            usleep(SNAKE_TICK);
        }
    }

end:
    clear();
    printw("Final Score: %d\n", snake.length);
    refresh();
    timeout(-1);
    getch();
    endwin();

    return 0;
}
