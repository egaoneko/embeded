#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "callbacks.h"
#include "fnd_test.h"
#include "support.h"
#include "interface.h"
#include "main.h"

#include <gnome.h>

#define fnd_dev "/dev/fnd"
#define MAXFND 	8

#define FND_SET(buf_num,data)	{ buf[buf_num] |= data ; write(dev, buf, MAXFND);}
#define FND_CLEAR(buf_num,data)	{ buf[buf_num] &= ~(data) ; write(dev, buf, MAXFND);}
	
static unsigned char buf[MAXFND +1];
static int dev, i;
GtkWidget *fnd_handle[64];

static int check_fnd1_a, check_fnd1_b, check_fnd1_c, check_fnd1_d, check_fnd1_e, check_fnd1_f, check_fnd1_g, check_fnd1_dp;
static int check_fnd2_a, check_fnd2_b, check_fnd2_c, check_fnd2_d, check_fnd2_e, check_fnd2_f, check_fnd2_g, check_fnd2_dp;
static int check_fnd3_a, check_fnd3_b, check_fnd3_c, check_fnd3_d, check_fnd3_e, check_fnd3_f, check_fnd3_g, check_fnd3_dp;
static int check_fnd4_a, check_fnd4_b, check_fnd4_c, check_fnd4_d, check_fnd4_e, check_fnd4_f, check_fnd4_g, check_fnd4_dp;
static int check_fnd5_a, check_fnd5_b, check_fnd5_c, check_fnd5_d, check_fnd5_e, check_fnd5_f, check_fnd5_g, check_fnd5_dp;
static int check_fnd6_a, check_fnd6_b, check_fnd6_c, check_fnd6_d, check_fnd6_e, check_fnd6_f, check_fnd6_g, check_fnd6_dp;
static int check_fnd7_a, check_fnd7_b, check_fnd7_c, check_fnd7_d, check_fnd7_e, check_fnd7_f, check_fnd7_g, check_fnd7_dp;
static int check_fnd8_a, check_fnd8_b, check_fnd8_c, check_fnd8_d, check_fnd8_e, check_fnd8_f, check_fnd8_g, check_fnd8_dp;
static int check_fnd1_on, check_fnd2_on, check_fnd3_on, check_fnd4_on, check_fnd5_on, check_fnd6_on, check_fnd7_on, check_fnd8_on;

int fnd_init(){
	dev = open (fnd_dev, O_RDWR);
	if(dev <0) {
		fprintf(stderr, "cannot open fnd (%d)", dev);
		exit(2);
	}
	memset(buf, 0 , sizeof(buf));
	
	check_fnd1_a = check_fnd1_b = check_fnd1_c = check_fnd1_d = check_fnd1_e = check_fnd1_f = check_fnd1_g = check_fnd1_dp = 0;
	check_fnd2_a = check_fnd2_b = check_fnd2_c = check_fnd2_d = check_fnd2_e = check_fnd2_f = check_fnd2_g = check_fnd2_dp = 0;
	check_fnd3_a = check_fnd3_b = check_fnd3_c = check_fnd3_d = check_fnd3_e = check_fnd3_f = check_fnd3_g = check_fnd3_dp = 0;
	check_fnd4_a = check_fnd4_b = check_fnd4_c = check_fnd4_d = check_fnd4_e = check_fnd4_f = check_fnd4_g = check_fnd4_dp = 0;
	check_fnd5_a = check_fnd5_b = check_fnd5_c = check_fnd5_d = check_fnd5_e = check_fnd5_f = check_fnd5_g = check_fnd5_dp = 0;
	check_fnd6_a = check_fnd6_b = check_fnd6_c = check_fnd6_d = check_fnd6_e = check_fnd6_f = check_fnd6_g = check_fnd6_dp = 0;
	check_fnd7_a = check_fnd7_b = check_fnd7_c = check_fnd7_d = check_fnd7_e = check_fnd7_f = check_fnd7_g = check_fnd7_dp = 0;
	check_fnd8_a = check_fnd8_b = check_fnd8_c = check_fnd8_d = check_fnd8_e = check_fnd8_f = check_fnd8_g = check_fnd8_dp = 0;
	check_fnd1_on = check_fnd2_on = check_fnd3_on = check_fnd4_on = check_fnd5_on = check_fnd6_on = check_fnd7_on = check_fnd8_on =0; 

	fnd_handle[0] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton1");
	fnd_handle[1] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton2");
	fnd_handle[2] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton3");
	fnd_handle[3] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton4");
	fnd_handle[4] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton5");
	fnd_handle[5] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton6");
	fnd_handle[6] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton7");
	fnd_handle[7] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton8");
	fnd_handle[8] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton9");
	fnd_handle[9] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton10");
	fnd_handle[10] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton11");
	fnd_handle[11] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton12");
        fnd_handle[12] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton13");
        fnd_handle[13] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton14");
        fnd_handle[14] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton15");
        fnd_handle[15] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton16");

        fnd_handle[16] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton17");
        fnd_handle[17] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton18");
        fnd_handle[18] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton19");
        fnd_handle[19] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton20");
        fnd_handle[20] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton21");
	fnd_handle[21] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton22");
        fnd_handle[22] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton23");
        fnd_handle[23] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton24");

        fnd_handle[24] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton25");
        fnd_handle[25] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton26");
        fnd_handle[26] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton27");
        fnd_handle[27] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton28");
        fnd_handle[28] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton29");
        fnd_handle[29] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton30");
        fnd_handle[30] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton31");
	fnd_handle[31] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton32");

        fnd_handle[32] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton33");
        fnd_handle[33] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton34");
        fnd_handle[34] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton35");
        fnd_handle[35] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton36");
        fnd_handle[36] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton37");
        fnd_handle[37] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton38");
        fnd_handle[38] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton39");
        fnd_handle[39] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton40");

        fnd_handle[40] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton41");
	fnd_handle[41] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton42");
        fnd_handle[42] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton43");
        fnd_handle[43] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton44");
        fnd_handle[44] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton45");
        fnd_handle[45] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton46");
        fnd_handle[46] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton47");
        fnd_handle[47] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton48");

        fnd_handle[48] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton49");
        fnd_handle[49] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton50");
        fnd_handle[50] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton51");
	fnd_handle[51] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton52");
        fnd_handle[52] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton53");
        fnd_handle[53] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton54");
        fnd_handle[54] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton55");
        fnd_handle[55] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton56");

        fnd_handle[56] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton57");
        fnd_handle[57] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton58");
        fnd_handle[58] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton59");
        fnd_handle[59] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton60");
        fnd_handle[60] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton61");
	fnd_handle[61] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton62");
        fnd_handle[62] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton63");
        fnd_handle[63] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton64");
	
	return 0;
}

void fnd1_on_off(){

        if (! check_fnd1_on)
        { 
		for( i=0; i<8; i++)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), TRUE);

		check_fnd1_a = check_fnd1_b = check_fnd1_c = check_fnd1_d = check_fnd1_e = \
		check_fnd1_f = check_fnd1_g = check_fnd1_dp = 1;

		FND_SET(0, 0xff);     check_fnd1_on = 1;
	}
        else    { 
		for( i=0; i<8; i++)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), FALSE);

		check_fnd1_a = check_fnd1_b = check_fnd1_c = check_fnd1_d = check_fnd1_e = \ 
		check_fnd1_f = check_fnd1_g = check_fnd1_dp = 0;
		FND_CLEAR(0, 0xff);   check_fnd1_on = 0;
		}
}

void fnd2_on_off(){
        if (! check_fnd2_on)
        {	
		for( i=8; i<16; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), TRUE);

                check_fnd2_a = check_fnd2_b = check_fnd2_c = check_fnd1_d = check_fnd1_e = \
                check_fnd2_f = check_fnd2_g = check_fnd2_dp = 1;

		FND_SET(1, 0xff);     check_fnd2_on = 1;
	 }
        else    { 

		for( i=8; i<16; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), FALSE);

                check_fnd2_a = check_fnd2_b = check_fnd2_c = check_fnd2_d = check_fnd2_e = \
                check_fnd2_f = check_fnd2_g = check_fnd2_dp = 0;
		
		FND_CLEAR(1, 0xff);   check_fnd2_on = 0;
	 }
}

void fnd3_on_off(){
        if (! check_fnd3_on)
        { 
		for( i=16; i<24; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), TRUE);

                check_fnd3_a = check_fnd3_b = check_fnd3_c = check_fnd3_d = check_fnd3_e = \
                check_fnd3_f = check_fnd3_g = check_fnd3_dp = 1;
	
		FND_SET(2, 0xff);     check_fnd3_on = 1; 
	}
        else    { 
		for( i=16; i<24; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), FALSE);

                check_fnd3_a = check_fnd3_b = check_fnd3_c = check_fnd3_d = check_fnd3_e = \
                check_fnd3_f = check_fnd3_g = check_fnd3_dp = 0;
		
		FND_CLEAR(2, 0xff);   check_fnd3_on = 0;
	 }
}

void fnd4_on_off(){
        if (! check_fnd4_on)
                {
		for( i=24; i<32; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), TRUE);

                check_fnd4_a = check_fnd4_b = check_fnd4_c = check_fnd4_d = check_fnd4_e = \
                check_fnd4_f = check_fnd4_g = check_fnd4_dp = 1;
		 FND_SET(3, 0xff);     check_fnd4_on = 1;
	 }
        else    {
		for( i=24; i<32; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), FALSE);

                check_fnd4_a = check_fnd4_b = check_fnd4_c = check_fnd4_d = check_fnd4_e = \
                check_fnd4_f = check_fnd4_g = check_fnd4_dp = 0;

		FND_CLEAR(3, 0xff);   check_fnd4_on = 0;
	 }
}

void fnd5_on_off(){
        if (! check_fnd5_on)
        {
		for( i=32; i<40; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), TRUE);

                check_fnd5_a = check_fnd5_b = check_fnd5_c = check_fnd5_d = check_fnd5_e = \
                check_fnd5_f = check_fnd5_g = check_fnd5_dp = 1;
		
		 FND_SET(4, 0xff);     check_fnd5_on = 1;
	 }
        else    { 
		for( i=32; i<40; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), FALSE);

                check_fnd5_a = check_fnd5_b = check_fnd5_c = check_fnd5_d = check_fnd5_e = \
                check_fnd5_f = check_fnd5_g = check_fnd5_dp = 0;

		FND_CLEAR(4, 0xff);   check_fnd5_on = 0; }
}

void fnd6_on_off(){
        if (! check_fnd6_on)
        {
		for( i=40; i<48; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), TRUE);

                check_fnd6_a = check_fnd6_b = check_fnd6_c = check_fnd6_d = check_fnd6_e = \
                check_fnd6_f = check_fnd6_g = check_fnd6_dp = 1;

		 FND_SET(5, 0xff);     check_fnd6_on = 1; 
	}
        else    { 
		for( i=40; i<48; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), FALSE);

                check_fnd6_a = check_fnd6_b = check_fnd6_c = check_fnd6_d = check_fnd6_e = \
                check_fnd6_f = check_fnd6_g = check_fnd6_dp = 0;
	
		FND_CLEAR(5, 0xff);   check_fnd6_on = 0;
	 }
}

void fnd7_on_off(){
        if (! check_fnd7_on)
        { 
		for( i=48; i<56; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), TRUE);

                check_fnd7_a = check_fnd7_b = check_fnd7_c = check_fnd7_d = check_fnd7_e = \
                check_fnd7_f = check_fnd7_g = check_fnd7_dp = 1;

		FND_SET(6, 0xff);     check_fnd7_on = 1;
	 }
        else    { 
		for( i=48; i<56; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), FALSE);

                check_fnd7_a = check_fnd7_b = check_fnd7_c = check_fnd7_d = check_fnd7_e = \
                check_fnd7_f = check_fnd7_g = check_fnd7_dp = 0;
		
		FND_CLEAR(6, 0xff);   check_fnd7_on = 0; 
	}
}

void fnd8_on_off(){
        if (! check_fnd8_on)
        {
		for( i=56; i<64; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), TRUE);

                check_fnd8_a = check_fnd8_b = check_fnd8_c = check_fnd8_d = check_fnd8_e = \
                check_fnd8_f = check_fnd8_g = check_fnd8_dp = 1;

		 FND_SET(7, 0xff);     check_fnd8_on = 1; }
        else    {
		for( i=56; i<64; i++)
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fnd_handle[i]), FALSE);

                check_fnd8_a = check_fnd8_b = check_fnd8_c = check_fnd8_d = check_fnd8_e = \
                check_fnd8_f = check_fnd8_g = check_fnd8_dp = 0;
		 FND_CLEAR(7, 0xff);   check_fnd8_on = 0;
	 }
}

/*********************    FND1    ************************/               

void fnd1_a_tog(){
	if (! check_fnd1_a)
		{ FND_SET(0, 0x01);	check_fnd1_a = 1; }
	else 	{ FND_CLEAR(0, 0x01);	check_fnd1_a = 0; }
}
void  fnd1_b_tog(){
	if (! check_fnd1_b)
		{ FND_SET(0, 0x02);	check_fnd1_b = 1; }
	else 	{ FND_CLEAR(0, 0x02);	check_fnd1_b = 0; }

}
void  fnd1_c_tog(){
	if (! check_fnd1_c)
		{ FND_SET(0, 0x04);	check_fnd1_c = 1; }
	else 	{ FND_CLEAR(0, 0x04);	check_fnd1_c = 0; }

}
void  fnd1_d_tog(){
	if (! check_fnd1_d)
		{ FND_SET(0, 0x08);	check_fnd1_d = 1; }
	else 	{ FND_CLEAR(0, 0x08);	check_fnd1_d = 0; }

}
void  fnd1_e_tog(){
	if (! check_fnd1_e)
		{ FND_SET(0, 0x10);	check_fnd1_e = 1; }
	else 	{ FND_CLEAR(0, 0x10);	check_fnd1_e = 0; }

}
void  fnd1_f_tog(){
	if (! check_fnd1_f)
		{ FND_SET(0, 0x20);	check_fnd1_f = 1; }
	else 	{ FND_CLEAR(0, 0x20);	check_fnd1_f = 0; }

}
void  fnd1_g_tog(){
	if (! check_fnd1_g)
		{ FND_SET(0, 0x40);	check_fnd1_g = 1; }
	else 	{ FND_CLEAR(0, 0x40);	check_fnd1_g = 0; }

}
void  fnd1_dp_tog(){
	if (! check_fnd1_dp)
		{ FND_SET(0, 0x80);	check_fnd1_dp = 1; }
	else 	{ FND_CLEAR(0, 0x80);	check_fnd1_dp = 0; }

}

/*********************    FND2    ************************/ 
              
void fnd2_a_tog(){
	if (! check_fnd2_a)
		{ FND_SET(1, 0x01);	check_fnd2_a = 1; }
	else 	{ FND_CLEAR(1, 0x01);	check_fnd2_a = 0; }
}
void  fnd2_b_tog(){
	if (! check_fnd2_b)
		{ FND_SET(1, 0x02);	check_fnd2_b = 1; }
	else 	{ FND_CLEAR(1, 0x02);	check_fnd2_b = 0; }

}
void  fnd2_c_tog(){
	if (! check_fnd2_c)
		{ FND_SET(1, 0x04);	check_fnd2_c = 1; }
	else 	{ FND_CLEAR(1, 0x04);	check_fnd2_c = 0; }

}
void  fnd2_d_tog(){
	if (! check_fnd2_d)
		{ FND_SET(1, 0x08);	check_fnd2_d = 1; }
	else 	{ FND_CLEAR(1, 0x08);	check_fnd2_d = 0; }

}
void  fnd2_e_tog(){
	if (! check_fnd2_e)
		{ FND_SET(1, 0x10);	check_fnd2_e = 1; }
	else 	{ FND_CLEAR(1, 0x10);	check_fnd2_e = 0; }

}
void  fnd2_f_tog(){
	if (! check_fnd2_f)
		{ FND_SET(1, 0x20);	check_fnd2_f = 1; }
	else 	{ FND_CLEAR(1, 0x20);	check_fnd2_f = 0; }

}
void  fnd2_g_tog(){
	if (! check_fnd2_g)
		{ FND_SET(1, 0x40);	check_fnd2_g = 1; }
	else 	{ FND_CLEAR(1, 0x40);	check_fnd2_g = 0; }

}
void  fnd2_dp_tog(){
	if (! check_fnd2_dp)
		{ FND_SET(1, 0x80);	check_fnd2_dp = 1; }
	else 	{ FND_CLEAR(1, 0x80);	check_fnd2_dp = 0; }

}

/*********************    FND3    ************************/ 
              
void fnd3_a_tog(){
	if (! check_fnd3_a)
		{ FND_SET(2, 0x01);	check_fnd3_a = 1; }
	else 	{ FND_CLEAR(2, 0x01);	check_fnd3_a = 0; }
}
void  fnd3_b_tog(){
	if (! check_fnd3_b)
		{ FND_SET(2, 0x02);	check_fnd3_b = 1; }
	else 	{ FND_CLEAR(2, 0x02);	check_fnd3_b = 0; }

}
void  fnd3_c_tog(){
	if (! check_fnd3_c)
		{ FND_SET(2, 0x04);	check_fnd3_c = 1; }
	else 	{ FND_CLEAR(2, 0x04);	check_fnd3_c = 0; }

}
void  fnd3_d_tog(){
	if (! check_fnd3_d)
		{ FND_SET(2, 0x08);	check_fnd3_d = 1; }
	else 	{ FND_CLEAR(2, 0x08);	check_fnd3_d = 0; }

}
void  fnd3_e_tog(){
	if (! check_fnd3_e)
		{ FND_SET(2, 0x10);	check_fnd3_e = 1; }
	else 	{ FND_CLEAR(2, 0x10);	check_fnd3_e = 0; }

}
void  fnd3_f_tog(){
	if (! check_fnd3_f)
		{ FND_SET(2, 0x20);	check_fnd3_f = 1; }
	else 	{ FND_CLEAR(2, 0x20);	check_fnd3_f = 0; }

}
void  fnd3_g_tog(){
	if (! check_fnd3_g)
		{ FND_SET(2, 0x40);	check_fnd3_g = 1; }
	else 	{ FND_CLEAR(2, 0x40);	check_fnd3_g = 0; }

}
void  fnd3_dp_tog(){
	if (! check_fnd3_dp)
		{ FND_SET(2, 0x80);	check_fnd3_dp = 1; }
	else 	{ FND_CLEAR(2, 0x80);	check_fnd3_dp = 0; }

}


/*********************    FND4    ************************/
              
void fnd4_a_tog(){
        if (! check_fnd4_a)
                { FND_SET(3, 0x01);     check_fnd4_a = 1; }
        else    { FND_CLEAR(3, 0x01);   check_fnd4_a = 0; }
}
void  fnd4_b_tog(){
        if (! check_fnd4_b)
                { FND_SET(3, 0x02);     check_fnd4_b = 1; }
        else    { FND_CLEAR(3, 0x02);   check_fnd4_b = 0; }

}
void  fnd4_c_tog(){
        if (! check_fnd4_c)
                { FND_SET(3, 0x04);     check_fnd4_c = 1; }
        else    { FND_CLEAR(3, 0x04);   check_fnd4_c = 0; }

}
void  fnd4_d_tog(){
        if (! check_fnd4_d)
                { FND_SET(3, 0x08);     check_fnd4_d = 1; }
        else    { FND_CLEAR(3, 0x08);   check_fnd4_d = 0; }

}
void  fnd4_e_tog(){
        if (! check_fnd4_e)
                { FND_SET(3, 0x10);     check_fnd4_e = 1; }
        else    { FND_CLEAR(3, 0x10);   check_fnd4_e = 0; }

}
void  fnd4_f_tog(){
        if (! check_fnd4_f)
                { FND_SET(3, 0x20);     check_fnd4_f = 1; }
        else    { FND_CLEAR(3, 0x20);   check_fnd4_f = 0; }

}
void  fnd4_g_tog(){
        if (! check_fnd4_g)
                { FND_SET(3, 0x40);     check_fnd4_g = 1; }
        else    { FND_CLEAR(3, 0x40);   check_fnd4_g = 0; }

}
void  fnd4_dp_tog(){
        if (! check_fnd4_dp)
                { FND_SET(3, 0x80);     check_fnd4_dp = 1; }
        else    { FND_CLEAR(3, 0x80);   check_fnd4_dp = 0; }

}

/*********************    FND5    ************************/

void fnd5_a_tog(){
        if (! check_fnd5_a)
                { FND_SET(4, 0x01);     check_fnd5_a = 1; }
        else    { FND_CLEAR(4, 0x01);   check_fnd5_a = 0; }
}
void  fnd5_b_tog(){
        if (! check_fnd5_b)
                { FND_SET(4, 0x02);     check_fnd5_b = 1; }
        else    { FND_CLEAR(4, 0x02);   check_fnd5_b = 0; }

}
void  fnd5_c_tog(){
        if (! check_fnd5_c)
                { FND_SET(4, 0x04);     check_fnd5_c = 1; }
        else    { FND_CLEAR(4, 0x04);   check_fnd5_c = 0; }

}
void  fnd5_d_tog(){
        if (! check_fnd5_d)
                { FND_SET(4, 0x08);     check_fnd5_d = 1; }
        else    { FND_CLEAR(4, 0x08);   check_fnd5_d = 0; }

}
void  fnd5_e_tog(){
        if (! check_fnd5_e)
                { FND_SET(4, 0x10);     check_fnd5_e = 1; }
        else    { FND_CLEAR(4, 0x10);   check_fnd5_e = 0; }

}
void  fnd5_f_tog(){
        if (! check_fnd5_f)
                { FND_SET(4, 0x20);     check_fnd5_f = 1; }
        else    { FND_CLEAR(4, 0x20);   check_fnd5_f = 0; }

}
void  fnd5_g_tog(){
        if (! check_fnd5_g)
                { FND_SET(4, 0x40);     check_fnd5_g = 1; }
        else    { FND_CLEAR(4, 0x40);   check_fnd5_g = 0; }

}
void  fnd5_dp_tog(){
        if (! check_fnd5_dp)
                { FND_SET(4, 0x80);     check_fnd5_dp = 1; }
        else    { FND_CLEAR(4, 0x80);   check_fnd5_dp = 0; }

}



/*********************    FND6    ************************/

void fnd6_a_tog(){
        if (! check_fnd6_a)
                { FND_SET(5, 0x01);     check_fnd6_a = 1; }
        else    { FND_CLEAR(5, 0x01);   check_fnd6_a = 0; }
}
void  fnd6_b_tog(){
        if (! check_fnd6_b)
                { FND_SET(5, 0x02);     check_fnd6_b = 1; }
        else    { FND_CLEAR(5, 0x02);   check_fnd6_b = 0; }

}
void  fnd6_c_tog(){
        if (! check_fnd6_c)
                { FND_SET(5, 0x04);     check_fnd6_c = 1; }
        else    { FND_CLEAR(5, 0x04);   check_fnd6_c = 0; }

}
void  fnd6_d_tog(){
        if (! check_fnd6_d)
                { FND_SET(5, 0x08);     check_fnd6_d = 1; }
        else    { FND_CLEAR(5, 0x08);   check_fnd6_d = 0; }

}
void  fnd6_e_tog(){
        if (! check_fnd6_e)
                { FND_SET(5, 0x10);     check_fnd6_e = 1; }
        else    { FND_CLEAR(5, 0x10);   check_fnd6_e = 0; }

}
void  fnd6_f_tog(){
        if (! check_fnd6_f)
                { FND_SET(5, 0x20);     check_fnd6_f = 1; }
        else    { FND_CLEAR(5, 0x20);   check_fnd6_f = 0; }

}
void  fnd6_g_tog(){
        if (! check_fnd6_g)
                { FND_SET(5, 0x40);     check_fnd6_g = 1; }
        else    { FND_CLEAR(5, 0x40);   check_fnd6_g = 0; }

}
void  fnd6_dp_tog(){
        if (! check_fnd6_dp)
                { FND_SET(5, 0x80);     check_fnd6_dp = 1; }
        else    { FND_CLEAR(5, 0x80);   check_fnd6_dp = 0; }

}

/*********************    FND7    ************************/

void fnd7_a_tog(){
        if (! check_fnd7_a)
                { FND_SET(6, 0x01);     check_fnd7_a = 1; }
        else    { FND_CLEAR(6, 0x01);   check_fnd7_a = 0; }
}
void  fnd7_b_tog(){
        if (! check_fnd7_b)
                { FND_SET(6, 0x02);     check_fnd7_b = 1; }
        else    { FND_CLEAR(6, 0x02);   check_fnd7_b = 0; }

}
void  fnd7_c_tog(){
        if (! check_fnd7_c)
                { FND_SET(6, 0x04);     check_fnd7_c = 1; }
        else    { FND_CLEAR(6, 0x04);   check_fnd7_c = 0; }

}
void  fnd7_d_tog(){
        if (! check_fnd7_d)
                { FND_SET(6, 0x08);     check_fnd7_d = 1; }
        else    { FND_CLEAR(6, 0x08);   check_fnd7_d = 0; }

}
void  fnd7_e_tog(){
        if (! check_fnd7_e)
                { FND_SET(6, 0x10);     check_fnd7_e = 1; }
        else    { FND_CLEAR(6, 0x10);   check_fnd7_e = 0; }

}
void  fnd7_f_tog(){
        if (! check_fnd7_f)
                { FND_SET(6, 0x20);     check_fnd7_f = 1; }
        else    { FND_CLEAR(6, 0x20);   check_fnd7_f = 0; }

}
void  fnd7_g_tog(){
        if (! check_fnd7_g)
                { FND_SET(6, 0x40);     check_fnd7_g = 1; }
        else    { FND_CLEAR(6, 0x40);   check_fnd7_g = 0; }

}
void  fnd7_dp_tog(){
        if (! check_fnd7_dp)
                { FND_SET(6, 0x80);     check_fnd7_dp = 1; }
        else    { FND_CLEAR(6, 0x80);   check_fnd7_dp = 0; }

}

/*********************    FND8    ************************/

void fnd8_a_tog(){
        if (! check_fnd8_a)
                { FND_SET(7, 0x01);     check_fnd8_a = 1; }
        else    { FND_CLEAR(7, 0x01);   check_fnd8_a = 0; }
}
void  fnd8_b_tog(){
        if (! check_fnd8_b)
                { FND_SET(7, 0x02);     check_fnd8_b = 1; }
        else    { FND_CLEAR(7, 0x02);   check_fnd8_b = 0; }

}
void  fnd8_c_tog(){
        if (! check_fnd8_c)
                { FND_SET(7, 0x04);     check_fnd8_c = 1; }
        else    { FND_CLEAR(7, 0x04);   check_fnd8_c = 0; }

}
void  fnd8_d_tog(){
        if (! check_fnd8_d)
                { FND_SET(7, 0x08);     check_fnd8_d = 1; }
        else    { FND_CLEAR(7, 0x08);   check_fnd8_d = 0; }

}
void  fnd8_e_tog(){
        if (! check_fnd8_e)
                { FND_SET(7, 0x10);     check_fnd8_e = 1; }
        else    { FND_CLEAR(7, 0x10);   check_fnd8_e = 0; }

}
void  fnd8_f_tog(){
        if (! check_fnd8_f)
                { FND_SET(7, 0x20);     check_fnd8_f = 1; }
        else    { FND_CLEAR(7, 0x20);   check_fnd8_f = 0; }

}
void  fnd8_g_tog(){
        if (! check_fnd8_g)
                { FND_SET(7, 0x40);     check_fnd8_g = 1; }
        else    { FND_CLEAR(7, 0x40);   check_fnd8_g = 0; }

}
void  fnd8_dp_tog(){
        if (! check_fnd8_dp)
                { FND_SET(7, 0x80);     check_fnd8_dp = 1; }
        else    { FND_CLEAR(7, 0x80);   check_fnd8_dp = 0; }

}





unsigned char asc_to_fnd(int n){
        unsigned char c;

                switch (n) {
                        /* 여러가지 문자를 추가할수 있다 */
                        case  0: c = 0x3f; break;
                        case  1: c = 0x06; break;
                        case  2: c = 0x5b; break;
                        case  3: c = 0x4f; break;
                        case  4: c = 0x66; break;
                        case  5: c = 0x6d; break;
                        case  6: c = 0x7d; break;
                        case  7: c = 0x07; break;
                        case  8: c = 0x7f; break;
                        case  9: c = 0x67; break;
                        default: c = 0x00; break;
                }
        return c;
}

