#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	struct sysinfo info;
	sysinfo(&info);
	int hours, minutes, seconds;
	hours = (info.uptime / 3600);
	minutes = ((info.uptime - (3600 * hours)) / 60);
	seconds = (info.uptime - (3600 * hours) - (minutes * 60));	
	printf("uptime: %d:%d:%d\n", hours, minutes, seconds);

	return 0;
}   	

