#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	printf("Hello World, I'm your game!\n");
	int fd = open("/dev/fb0", O_RDWR);
	printf(fd);
	close(fd);
	exit(EXIT_SUCCESS);
}
