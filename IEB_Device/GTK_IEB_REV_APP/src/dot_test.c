#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gnome.h>

#include "callbacks.h"
#include "dot_test.h"
#include "support.h"
#include "interface.h"
#include "main.h"

#define dot_dev	"/dev/dot"
#define DOT_COL	5

#define DOT_SET(col_num, data)   { dot_col[col_num] &= data ; write(dev, dot_col, DOT_COL);}
#define DOT_CLEAR(col_num, data) { dot_col[col_num] |= ~(data) ; write(dev, dot_col, DOT_COL);}

static unsigned char dot_col[5] = {0};
static int dev;
static int check_dot1, check_dot2, check_dot3, check_dot4, check_dot5, \
	   check_dot6, check_dot7, check_dot8, check_dot9, check_dot10, \
	   check_dot11, check_dot12, check_dot13, check_dot14, check_dot15,\
	   check_dot16, check_dot17, check_dot18, check_dot19, check_dot20, \
	   check_dot21, check_dot22, check_dot23, check_dot24, check_dot25,\
	   check_dot26, check_dot27, check_dot28, check_dot29, check_dot30, \
	   check_dot31, check_dot32, check_dot33, check_dot34, check_dot35;
static int check_dot_all;

GtkWidget *dot_handle[35];

void dot_init(){

	dev = open(dot_dev, O_RDWR);
	if (dev <0) {
		fprintf(stderr, "cannot open /dev/dot (%d)",dev);
		exit(2);
	}

	memset(dot_col, 0x7F, sizeof(dot_col));

	DOT_SET(0, 0X7F);
	DOT_SET(1, 0X7F);
	DOT_SET(2, 0X7F);
	DOT_SET(3, 0X7F);
	DOT_SET(4, 0X7F);

	check_dot1 = check_dot2 = check_dot3 = check_dot4 = check_dot5 = \
	check_dot6 = check_dot7 = check_dot8 = check_dot9 = check_dot10 = \
        check_dot11 = check_dot12 = check_dot13 = check_dot14 = check_dot15 = \
	check_dot16 = check_dot17 = check_dot18 = check_dot19 = check_dot20 = \
        check_dot21 = check_dot22 = check_dot23 = check_dot24 = check_dot25 = \
	check_dot26 = check_dot27 = check_dot28 = check_dot29 = check_dot30 = \
        check_dot31 = check_dot32 = check_dot33 = check_dot34 = check_dot35 = 0;
	check_dot_all =0;
	
	dot_handle[0] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton65");
	dot_handle[1] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton66");
	dot_handle[2] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton67");
	dot_handle[3] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton68");
	dot_handle[4] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton69");

	dot_handle[5] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton70");
	dot_handle[6] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton71");
	dot_handle[7] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton72");
	dot_handle[8] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton73");
	dot_handle[9] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton74");

	dot_handle[10] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton75");
	dot_handle[11] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton76");
	dot_handle[12] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton77");
	dot_handle[13] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton78");
	dot_handle[14] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton79");
	
	dot_handle[15] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton80");
	dot_handle[16] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton81");
	dot_handle[17] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton82");
	dot_handle[18] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton83");
	dot_handle[19] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton84");

	dot_handle[20] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton85");
	dot_handle[21] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton86");
	dot_handle[22] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton87");
	dot_handle[23] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton88");
	dot_handle[24] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton89");

	dot_handle[25] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton90");
	dot_handle[26] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton91");
	dot_handle[27] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton92");
	dot_handle[28] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton93");
	dot_handle[29] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton94");

	dot_handle[30] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton95");
	dot_handle[31] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton96");
	dot_handle[32] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton97");
	dot_handle[33] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton98");
	dot_handle[34] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton99");
}

void dot_all_tog (){
	
	int i;

	
	if (!check_dot_all){
		DOT_SET(0, 0x7F); DOT_SET(1, 0x7F); DOT_SET(2, 0x7F); DOT_SET(3, 0x7F); DOT_SET(4, 0x7F);
		
		for (i=0 ; i <35; i++)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dot_handle[i]), TRUE);
		
	   	check_dot1 = check_dot2 = check_dot3 = check_dot4 = check_dot5 = \
	   	check_dot6 = check_dot7 = check_dot8 = check_dot9 = check_dot10 = \
           	check_dot11 = check_dot12 = check_dot13 = check_dot14 = check_dot15 = \
	   	check_dot16 = check_dot17 = check_dot18 = check_dot19 = check_dot20 = \
	        check_dot21 = check_dot22 = check_dot23 = check_dot24 = check_dot25 = \
	   	check_dot26 = check_dot27 = check_dot28 = check_dot29 = check_dot30 = \
           	check_dot31 = check_dot32 = check_dot33 = check_dot34 = check_dot35 = 1;	

		check_dot_all =1;
	}
	else {	DOT_CLEAR(0, 0x7F); DOT_CLEAR(1, 0x7F); DOT_CLEAR(2, 0x7F); \
		DOT_CLEAR(3, 0x7F); DOT_CLEAR(4, 0x7F);
		
		for (i=0 ; i <35; i++)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dot_handle[i]), FALSE);
		
		check_dot1 = check_dot2 = check_dot3 = check_dot4 = check_dot5 = \
	   	check_dot6 = check_dot7 = check_dot8 = check_dot9 = check_dot10 = \
           	check_dot11 = check_dot12 = check_dot13 = check_dot14 = check_dot15 = \
	   	check_dot16 = check_dot17 = check_dot18 = check_dot19 = check_dot20 = \
           	check_dot21 = check_dot22 = check_dot23 = check_dot24 = check_dot25 = \
	   	check_dot26 = check_dot27 = check_dot28 = check_dot29 = check_dot30 = \
           	check_dot31 = check_dot32 = check_dot33 = check_dot34 = check_dot35 = 0;	
		
		check_dot_all =0;
	}

}

/*************************   ROW1   ************************/
void dot1_tog(){
        if (! check_dot1)
                { DOT_SET(0, 0x7E);     check_dot1 = 1; }
        else    { DOT_CLEAR(0, 0x7E);   check_dot1 = 0; }
}

void dot2_tog(){
        if (! check_dot2)
                { DOT_SET(1, 0x7E);     check_dot2 = 1; }
        else    { DOT_CLEAR(1, 0x7E);   check_dot2 = 0; }
}
void dot3_tog(){
        if (! check_dot3)
                { DOT_SET(2, 0x7E);     check_dot3 = 1; }
        else    { DOT_CLEAR(2, 0x7E);   check_dot3 = 0; }
}

void dot4_tog(){
        if (! check_dot4)
                { DOT_SET(3, 0x7E);     check_dot4 = 1; }
        else    { DOT_CLEAR(3, 0x7E);   check_dot4 = 0; }
}

void dot5_tog(){
        if (! check_dot5)
                { DOT_SET(4, 0x7E);     check_dot5 = 1; }
        else    { DOT_CLEAR(4, 0x7E);   check_dot5 = 0; }
}


/*************************   ROW2   ************************/
void dot6_tog(){
        if (! check_dot6)
                { DOT_SET(0, 0x7D);     check_dot6 = 1; }
        else    { DOT_CLEAR(0, 0x7D);   check_dot6 = 0; }
}

void dot7_tog(){
        if (! check_dot7)
                { DOT_SET(1, 0x7D);     check_dot7 = 1; }
        else    { DOT_CLEAR(1, 0x7D);   check_dot7 = 0; }
}
void dot8_tog(){
        if (! check_dot8)
                { DOT_SET(2, 0x7D);     check_dot8 = 1; }
        else    { DOT_CLEAR(2, 0x7D);   check_dot8 = 0; }
}

void dot9_tog(){
        if (! check_dot9)
                { DOT_SET(3, 0x7D);     check_dot9 = 1; }
        else    { DOT_CLEAR(3, 0x7D);   check_dot9 = 0; }
}

void dot10_tog(){
        if (! check_dot10)
                { DOT_SET(4, 0x7D);     check_dot10 = 1; }
        else    { DOT_CLEAR(4, 0x7D);   check_dot10 = 0; }
}

/*************************   ROW3   ************************/
void dot11_tog(){
        if (! check_dot11)
                { DOT_SET(0, 0x7B);     check_dot11 = 1; }
        else    { DOT_CLEAR(0, 0x7B);   check_dot11 = 0; }
}

void dot12_tog(){
        if (! check_dot12)
                { DOT_SET(1, 0x7B);     check_dot12 = 1; }
        else    { DOT_CLEAR(1, 0x7B);   check_dot12 = 0; }
}
void dot13_tog(){
        if (! check_dot13)
                { DOT_SET(2, 0x7B);     check_dot13 = 1; }
        else    { DOT_CLEAR(2, 0x7B);   check_dot13 = 0; }
}

void dot14_tog(){
        if (! check_dot14)
                { DOT_SET(3, 0x7B);     check_dot14 = 1; }
        else    { DOT_CLEAR(3, 0x7B);   check_dot14 = 0; }
}

void dot15_tog(){
        if (! check_dot15)
                { DOT_SET(4, 0x7B);     check_dot15 = 1; }
        else    { DOT_CLEAR(4, 0x7B);   check_dot15 = 0; }
}

/*************************   ROW4   ************************/
void dot16_tog(){
        if (! check_dot16)
                { DOT_SET(0, 0x77);     check_dot16 = 1; }
        else    { DOT_CLEAR(0, 0x77);   check_dot16 = 0; }
}

void dot17_tog(){
        if (! check_dot17)
                { DOT_SET(1, 0x77);     check_dot17 = 1; }
        else    { DOT_CLEAR(1, 0x77);   check_dot17 = 0; }
}
void dot18_tog(){
        if (! check_dot18)
                { DOT_SET(2, 0x77);     check_dot18 = 1; }
        else    { DOT_CLEAR(2, 0x77);   check_dot18 = 0; }
}

void dot19_tog(){
        if (! check_dot19)
                { DOT_SET(3, 0x77);     check_dot19 = 1; }
        else    { DOT_CLEAR(3, 0x77);   check_dot19 = 0; }
}

void dot20_tog(){
        if (! check_dot20)
                { DOT_SET(4, 0x77);     check_dot20 = 1; }
        else    { DOT_CLEAR(4, 0x77);   check_dot20 = 0; }
}

/*************************   ROW5   ************************/
void dot21_tog(){
        if (! check_dot21)
                { DOT_SET(0, 0x6F);     check_dot21 = 1; }
        else    { DOT_CLEAR(0, 0x6F);   check_dot21 = 0; }
}

void dot22_tog(){
        if (! check_dot22)
                { DOT_SET(1, 0x6F);     check_dot22 = 1; }
        else    { DOT_CLEAR(1, 0x6F);   check_dot22 = 0; }
}
void dot23_tog(){
        if (! check_dot23)
                { DOT_SET(2, 0x6F);     check_dot23 = 1; }
        else    { DOT_CLEAR(2, 0x6F);   check_dot23 = 0; }
}

void dot24_tog(){
        if (! check_dot24)
                { DOT_SET(3, 0x6F);     check_dot24 = 1; }
        else    { DOT_CLEAR(3, 0x6F);   check_dot24 = 0; }
}

void dot25_tog(){
        if (! check_dot25)
                { DOT_SET(4, 0x6F);     check_dot25 = 1; }
        else    { DOT_CLEAR(4, 0x6F);   check_dot25 = 0; }
}


/*************************   ROW6   ************************/
void dot26_tog(){
        if (! check_dot26)
                { DOT_SET(0, 0x5F);     check_dot26 = 1; }
        else    { DOT_CLEAR(0, 0x5F);   check_dot26 = 0; }
}

void dot27_tog(){
        if (! check_dot27)
                { DOT_SET(1, 0x5F);     check_dot27 = 1; }
        else    { DOT_CLEAR(1, 0x5F);   check_dot27 = 0; }
}
void dot28_tog(){
        if (! check_dot28)
                { DOT_SET(2, 0x5F);     check_dot28 = 1; }
        else    { DOT_CLEAR(2, 0x5F);   check_dot28 = 0; }
}

void dot29_tog(){
        if (! check_dot29)
                { DOT_SET(3, 0x5F);     check_dot29 = 1; }
        else    { DOT_CLEAR(3, 0x5F);   check_dot29 = 0; }
}

void dot30_tog(){
        if (! check_dot30)
                { DOT_SET(4, 0x5F);     check_dot30 = 1; }
        else    { DOT_CLEAR(4, 0x5F);   check_dot30 = 0; }
}


/*************************   ROW7  ************************/
void dot31_tog(){
        if (! check_dot31)
                { DOT_SET(0, 0x3F);     check_dot31 = 1; }
        else    { DOT_CLEAR(0, 0x3F);   check_dot31 = 0; }
}

void dot32_tog(){
        if (! check_dot32)
                { DOT_SET(1, 0x3F);     check_dot32 = 1; }
        else    { DOT_CLEAR(1, 0x3F);   check_dot32 = 0; }
}
void dot33_tog(){
        if (! check_dot33)
                { DOT_SET(2, 0x3F);     check_dot33 = 1; }
        else    { DOT_CLEAR(2, 0x3F);   check_dot33 = 0; }
}

void dot34_tog(){
        if (! check_dot34)
                { DOT_SET(3, 0x3F);     check_dot34 = 1; }
        else    { DOT_CLEAR(3, 0x3F);   check_dot34 = 0; }
}

void dot35_tog(){
        if (! check_dot35)
                { DOT_SET(4, 0x3F);     check_dot35 = 1; }
        else    { DOT_CLEAR(4, 0x3F);   check_dot35 = 0; }
}

