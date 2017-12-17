#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd;
	int val = 1;
	fd = open("/dev/ScanKey1", O_RDWR);
	if(fd < 0)
		printf("Can't open!\n");

	unsigned char KeyVals[6] = {0};
	unsigned int KeyPressCount = 0;
	unsigned long KeyFlag;
	while(1)
	{
		read(fd, KeyVals, sizeof(KeyVals));
		KeyFlag = KeyVals[0] +  KeyVals[1] + KeyVals[2] + KeyVals[3] + KeyVals[4] + KeyVals[5];
		if(KeyFlag != 0)
		{
			printf("Button S2: %s\n", KeyVals[0] ? "Pressed": "Released");
			printf("Button S3: %s\n", KeyVals[1] ? "Pressed": "Released");
			printf("Button S4: %s\n", KeyVals[2] ? "Pressed": "Released");
			printf("Button S5: %s\n", KeyVals[3] ? "Pressed": "Released");
			printf("Button S6: %s\n", KeyVals[4] ? "Pressed": "Released");
			printf("Button S7: %s\n", KeyVals[5] ? "Pressed": "Released");
		}
	}
	return 0;	
}
