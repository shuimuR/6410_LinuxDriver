#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>

int main(int argc, char *argv)
{
    int fd, ret;
    struct pollfd pfd[1];

    fd = open("/dev/KeyIntr", O_RDWR);
	if(fd < 0)
		printf("Can't open!\n");

    pfd[0].fd = fd;
    pfd[0].events = POLLIN;
    unsigned char KeyVal = 0;
    while(1)
    {
        ret = poll(pfd, 1, 2000);
        if(ret == 0)
        {
            printf("Time out\n");
        }
        else
        {
            read(fd, &KeyVal, 1);
            printf("KeyVal = %d\n", KeyVal);
        }
    }
    return 0;
}
