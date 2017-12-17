#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd;
	int val = 1;
	fd = open("/dev/KeyIntr", O_RDWR);
	if(fd < 0)
		printf("Can't open!\n");

	unsigned char KeyVals= 0;
	unsigned int KeyPressCount = 0;
	unsigned long KeyFlag;
	while(1)
	{
		read(fd, KeyVals, sizeof(KeyVals));
		printf("S%d Press\n", KeyVals+2);
	}
	return 0;	
}
