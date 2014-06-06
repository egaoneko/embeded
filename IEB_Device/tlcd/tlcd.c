#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>


#define FBDEVFILE "/dev/fb"

typedef unsigned char ubyte;

void setbox(struct fb_var_screeninfo *fbvar , unsigned char *pfbdata, int color , int x , int y, int big);

void setpixel(struct fb_var_screeninfo* , unsigned char *pfbdata , int color , int x , int y);

unsigned char makepixel(ubyte r , ubyte g , ubyte b);

int main ()
{
	int fbfd;
	int ret; 
	struct fb_var_screeninfo fbvar;
	unsigned char *pfbdata;
	long int screensize = 0;

	fbfd = open(FBDEVFILE , O_RDWR);
	if(fbfd < 0)
	{
		perror("fbdev open");
		exit(1);
	}
	
	ret = ioctl(fbfd, FBIOGET_VSCREENINFO, &fbvar);

	if(ret < 0)
	{
		perror("fbdev ioctl");
		exit(1);
	}
	
	printf("bits_per_pixel %x\n", fbvar.bits_per_pixel);

	screensize = fbvar.xres * fbvar.yres * fbvar.bits_per_pixel / 8;
	printf("screensize %x\n", screensize);

	pfbdata = (unsigned char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

	if((unsigned)pfbdata == (unsigned)-1)
	{
		perror("fbdev mmap");
		exit(1);
	}
	else{
		printf("pfbdata %x\n", pfbdata);
	}

	setbox( &fbvar, pfbdata, 0 , 200 , 200 , 100);

	munmap(pfbdata , screensize);
	close(fbfd);
	exit(0);
	return 0; 
}

unsigned char makepixel(ubyte r ,ubyte g ,ubyte b)
{
	return (unsigned char)(((r>>3)<<11) | ((g>>2)<<5)|(b>>3));
}

void setpixel(struct fb_var_screeninfo *fbvar, unsigned char *pfbdata, int color, int xpos, int ypos)
{
	unsigned char *setpixel_fbdata = pfbdata;
	struct fb_var_screeninfo *setpixel_fbvar = fbvar;
	int offset;
	unsigned char pixel;
	offset = ypos*(*setpixel_fbvar).xres+xpos;
	pixel = makepixel(0,255,0);
	*(setpixel_fbdata+offset) = pixel;
}

void setbox(struct fb_var_screeninfo *fbvar, unsigned char *pfbdata, int color, int xpos, int ypos, int k)
{
	unsigned char *setdot_fbdata = pfbdata;
	struct fb_var_screeninfo *setdot_fbvar = fbvar;
	int offset;
	unsigned char pixel;
	int x,y;
	for(x = 0 ; x < k ; x++)
	{
		for(y = 0; y < k ; y++)
		{
			offset = (ypos+y)*(*setdot_fbvar).xres+(xpos+x);
			pixel = makepixel(11,111,217);
			*(setdot_fbdata+offset);
		}
	}
}

