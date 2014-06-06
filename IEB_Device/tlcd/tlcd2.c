#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#define FBDEVFILE "/dev/fb"

int main(){
    int fb;
    int status;
    struct fb_var_screeninfo fbvar;
    struct fb_fix_screeninfo fbfix;

    fb=open(FBDEVFILE, O_RDWR);
    if(fb<0) {
        printf("Error fbdev open\n"); exit(1);
    }
    status = ioctl(fb, FBIOGET_VSCREENINFO, &fbvar);
    if(status < 0) {
        printf("Error fbdev ioctl(FSCREENINFO)\n"); exit(1);
    }
    status = ioctl(fb, FBIOGET_FSCREENINFO, &fbfix);
    if(status < 0) {
        printf("Error fbdev ioctl(FSCREENINFO)\n"); exit(1);
    }
    printf("x-resolution : %d\n",fbvar.xres);
    printf("y-resolution : %d\n",fbvar.xres);
    printf("x-resolution(virtual) : %d\n", fbvar.xres_virtual);
    printf("y-resolution(virtual) : %d\n", fbvar.yres_virtual);
    printf("bpp: %d\n", fbvar.bits_per_pixel);
    printf("length of frame buffer memory : %d\n", fbfix.smem_len);

    close(fb);
    exit(0);
    return 0;
}
