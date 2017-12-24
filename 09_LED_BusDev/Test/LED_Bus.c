#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;
	int val = 1;
	fd = open("/dev/LEDBus", O_RDWR);
	if(fd < 0)
		printf("Can't open!\n");

	unsigned char val1[4] = {0, 1, 0, 1};
	unsigned char val2[4] = {1, 0, 1, 0};
	unsigned char *ValP = val1;

	while(1)
	{
		write(fd, ValP, 4);
		if(ValP == val1)
		{
			printf("Send val1\n");
			ValP = val2;
		}
		else if(ValP == val2)
		{
			printf("Send val2\n");
			ValP = val1;
		}
		sleep(1);
	}
	return 0;
}
