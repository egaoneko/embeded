#include <stdio.h>
#include <fcntl.h>
#include <time.h>

int main(){
	unsigned int i;
	unsigned int j;
	char rdata[40];

	int fd;
	
	fd= open("/dev/CC2420", O_RDWR);
	printf("open results : %d\n",fd);

	for(i=0;i<10;i++){
		if(read(fd,rdata,11) == -1)
			printf("read : failed\n");
		else{
			printf("received packet :");
			for(j=0;j<rdata[0];j++)
				printf(" %X",rdata[j]);
			printf("\n");
		}

	}

	close(fd);
	return 0;
}

