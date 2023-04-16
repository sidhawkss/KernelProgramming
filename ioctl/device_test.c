#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#define CMD_1 _IOW('x','y',int32_t*)

int main(void){
		int f = open("/dev/PLANBDEVICE", O_RDWR);
		if(!f)
			printf("[!]Failed\n");
		else
			printf("[*]Device opened!\n");
		int num=10;
		ioctl(f, CMD_1, (int32_t *) &num);
		return 0;
}