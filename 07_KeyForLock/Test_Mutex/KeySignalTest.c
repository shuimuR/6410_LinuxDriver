#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int fd;
unsigned char KeyVal = 0;

void SignalIOFunc(int signum)
{
    read(fd, &KeyVal, 1);
    printf("The key val = %d\n", KeyVal);
}

int main(int atgc, char **argv)
{
    int ret,OFlags;

    signal(SIGIO, SignalIOFunc);

    fd = open("/dev/KeyIntr", O_RDWR);
    if(fd < 0)
    {
        printf("Open /dev/KeyIntr error\n");
        return -1;
    }

    fcntl(fd, F_SETOWN, getpid());

    OFlags = fcntl(fd, F_GETFL);

    fcntl(fd, F_SETFL, OFlags | FASYNC);

    read(fd, &KeyVal, 1);
    while(1)
    {
        sleep(1000);
    }

    return 0;
}
