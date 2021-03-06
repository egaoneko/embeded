#include <stdio.h>
#include <stdlib.h> /*for exit*/
#include <unistd.h> /*for open/close..*/
#include <fcntl.h> /*for O_RFONLY */
#include <sys/ioctl.h> /*for ioctl*/
#include <sys/types.h> 
#include <linux/fb.h> /* for fb_var_screeninfo*/

#define FBDEVFILE "/dev/fb"
 
typedef unsigned char ubyte;

unsigned short makepixel(ubyte r, ubyte g, ubyte b)
{
return (unsigned short)(((r>>3)<<11)|((g>>2)<<5)|(b>>3));
}

int main()
{
int fbfd;
int ret;
struct fb_var_screeninfo fbvar;
unsigned short pixel;
int offset;
 
fbfd = open(FBDEVFILE, O_RDWR);
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
 
if(fbvar.bits_per_pixel != 16)
{
fprintf(stderr, "bpp is not 16n");
exit(1);
}

/* red pixel @ (0,0) */
if(lseek(fbfd, 0, SEEK_SET) < 0)
{
perror("fbdev lseek");
exit(1);
}
pixel = makepixel(255,0,0); /* red pixel */
write(fbfd, &pixel, 2); /* write 2byte(16bit) */
 
/* green pixel @ (100,50) */
offset = 50*fbvar.xres*(16/8)+100*(16/8);
if(lseek(fbfd, offset, SEEK_SET) < 0)
{
perror("fbdev lseek");
exit(1);
}
pixel = makepixel(0,255,0); /* green pixel */
write(fbfd, &pixel, 2); /* write 2byte(16bit) */
 

/* blue pixel @ (50,100) */
offset = 100*fbvar.xres*(16/8)+50*(16/8);
if(lseek(fbfd, offset, SEEK_SET) < 0)
{
perror("fbdev lseek");
exit(1);
}
pixel = makepixel(0,0,255); /* blue pixel */
write(fbfd, &pixel, 2); /* write 2byte(16bit) */
 
/* white pixel @ (100,100) */
offset = 100*fbvar.xres*(16/8)+100*(16/8);
if(lseek(fbfd, offset, SEEK_SET) < 0)
{
perror("fbdev lseek");
exit(1);
}
pixel = makepixel(255,255,255); /* white pixel */
write(fbfd, &pixel, 2); /* write 2byte(16bit) */
 
close(fbfd);
exit(0);
return 0;
}
 
