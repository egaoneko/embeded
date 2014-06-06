#include <stdio.h>
#include <stdlib.h> /*for exit*/
#include <unistd.h> /*for open/close..*/
#include <fcntl.h> /*for O_RFONLY */
#include <sys/ioctl.h> /*for ioctl*/
#include <sys/types.h> 
#include <linux/fb.h> /* for fb_var_screeninfo,
FBIOGET_VSCREENINFO*/

#define FBDEVFILE "/dev/fb"
#define COLS 640
#define ROWS 640

typedef unsigned char ubyte;

unsigned short makepixel(ubyte r, ubyte g, ubyte b) {
      return(unsigned short)(((r>>3)<<11)||((g<<2)<<6)|(b>>3));
    }
    
int main(){
            int fd, status, offset;
            struct fb_var_screeninfo fbvar;
            unsigned short pixel;
            
            fd = open(FBDEVFILE, O_RDWR);
            if(fd<0) {
                      printf("Error fbdev open\n"); exit(1);
            }
            
            /* red pixel @(50, 100) */
            offset = 100*COLS*2 + 50*2;
            if(lseek(fd, offset, SEEK_SET) < 0) {
                    printf("Error fbdev lseek\n"); exit(1);
            }
            pixel = makepixel(255, 0, 0); /*red pixel*/
            write(fd, &pixel, 2); /*write 2byte(16bit)*/
            
            /*green pixel @ (100,100) */
            offset = 100*COLS*2+150*2;
            if(lseek(fd, offset, SEEK_SET) < 0) {
                          printf("Error fbdev lseek\n"); exit(1);
            }
            pixel = makepixel(0, 0, 255); /*blue pixel*/
            write(fd, &pixel, 2); /*write 2byte(16bit)*/
            
            close(fd);
            exit(0);
            return 0;
}
