#ifndef __DEV_H__
#define __DEV_H__

#include <stdio.h>
#include <fcntl.h>

/* Dev_Key */
#include <asm/ioctls.h>

/* Dev_Init */
#define DEV_NUM	6

/* KEY */
#define dbg(x...)       printf(x)
#define K_NUM0  13
#define K_NUM1  9
#define K_NUM2  10
#define K_NUM3  11
#define K_NUM4  5
#define K_NUM5  6
#define K_NUM6  7
#define K_NUM7  1
#define K_NUM8  2
#define K_NUM9  3
#define K_DOT   14
#define K_ADD   4
#define K_SUB   8
#define K_MUL   12
#define K_DIV   16
#define K_EQU   15

/* CLCD */
#define	MAXCHR  32
#define	HCHR	0
#define LCHR	16

/* DOT */
#define DOT_DISPLAY	0
#define DOT_COL		5

/* FND */
/*
 *	bit# pos
 *
 *	  --0--
 *	5|     |1
 *	  --6--
 *	4|     |2
 *	  --3--  o7
 */
#define MAXFND		8

/* BTN */
#define GPIO_BTN_READ       0x1000

/* Dev_FD */
static char keyDev[] = "/dev/key";
static int  keyFd = (-1);
static char lcdDev[] = "/dev/clcd";
static int  lcdFd = (-1);
static char dotDev[] = "/dev/dot";
static int  dotFd = (-1);
static char fndDev[] = "/dev/fnd";
static int  fndFd = (-1);
static char btnDev[] = "/dev/BTN";
static int  btnFd = (-1);
static char ledDev[] = "/dev/led";
static int  ledFd = (-1);

/* KEY_FUN */
//unsigned char key_get(int tmo);

/* FND_FUN */
unsigned char asc_to_fnd(int n);
void fnd_clear(char* s, char* fnd_buf);

/* ETC_FUN */
void error_handling(char *msg, int fd);

/* DOT_FUN */
unsigned char asc_to_dot(int asc);

/* LED Write */
void led_start(int *dev, int num);

#endif
