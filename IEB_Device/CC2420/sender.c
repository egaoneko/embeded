#include <stdio.h>
#include <fcntl.h>
#include <time.h>

int main(){
	unsigned int i;
	unsigned int j;
	int input;
	char data[3];

	int fd;
	
	fd= open("/dev/CC2420", O_RDWR);
	printf("open results : %d\n",fd);

	for(i=0;i<10;i++){
		for(j=0;j<3;j++){
			printf("give me a number...\n");	
			scanf("%d",&input);	
			data[j]=input;
		}

		if(write(fd,data,3) == -1)
			printf("write : failed\n");
		
		else 
			printf("@@@ transmission...\n\n");
	}

	close(fd);
	return 0;
}

