#include <stdio.h>
#include <signal.h>

void MySigFun(int signum)
{
    static int cnt = 0;
    printf("cnt = %d, Signum = %d\n", ++cnt, signum);
}

int main(int argc, char **argv)
{
    signal(SIGUSR1, MySigFun);
    while(1)
    {
        sleep(1000);
    }
    return 0;
}
