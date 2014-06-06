#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define led_dev "/dev/led"
void led_start(int *dev,int num);

int main(void)
{
  int dev = 0,num;
  dev = open(led_dev, O_RDWR);
   if (dev < 0){
    fprintf(stderr, "Cannot open LED Device (%d)", dev);
    exit(2);
    }
   while(1){
    printf("number input (0~13) >>");
	scanf("%d",&num);
	led_start(&dev,num);
   }
 close(dev);
}

void led_start(int *dev, int num){
  
 unsigned char data;

  switch(num){
  case 1:
   data  =0x7f;
   write(*dev, &data, sizeof(unsigned char));
   break;
  case 2:
   data  = 0xbf;
   write(*dev, &data, sizeof(unsigned char));
   break;
  case 3:
   data  = 0xdf;
   write(*dev, &data, sizeof(unsigned char));
   break;
  case 4:
   data  =0xef;
   write(*dev, &data, sizeof(unsigned char));
   break;
  case 5:
   data  = 0xf7; 
   write(*dev, &data, sizeof(unsigned char));
   break;
  case 6:
   data  =0xfb;
   write(*dev, &data, sizeof(unsigned char));
   break;
  case 7:
   data  = 0xfd; 
   write(*dev, &data, sizeof(unsigned char));
   break;
  case 8:
   data  = 0xfe;
   write(*dev, &data, sizeof(unsigned char));
   break;
 
  case 0:
   break;

 }
} 
