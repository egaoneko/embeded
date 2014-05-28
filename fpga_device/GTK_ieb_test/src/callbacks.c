#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fnd_test.h"
#include "dot_test.h"
#include "led_test.h"
#include "st_motor_test.h"
#include "dc_motor_test.h"
#include <stdio.h>


void
on_togglebutton1_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd1_a_tog();
}


void
on_togglebutton3_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd1_b_tog();
}


void
on_togglebutton4_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd1_g_tog();
}


void
on_togglebutton2_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd1_f_tog();
}


void
on_togglebutton6_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd1_c_tog();
}


void
on_togglebutton5_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd1_e_tog();
}


void
on_togglebutton7_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd1_d_tog();
}


void
on_togglebutton8_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd1_dp_tog();
}


void
on_togglebutton11_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd2_b_tog();
}


void
on_togglebutton12_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd2_g_tog();
}


void
on_togglebutton9_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd2_a_tog();

}


void
on_togglebutton10_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd2_f_tog();

}


void
on_togglebutton14_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd2_c_tog();

}


void
on_togglebutton13_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd2_e_tog();

}


void
on_togglebutton15_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd2_d_tog();

}


void
on_togglebutton16_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd2_dp_tog();

}

/****************************** FND 3   ****************************/
void
on_togglebutton19_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_b_tog();

}


void
on_togglebutton20_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_g_tog();

}


void
on_togglebutton17_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_a_tog();

}


void
on_togglebutton18_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_f_tog();

}


void
on_togglebutton22_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_c_tog();

}


void
on_togglebutton21_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_e_tog();

}


void
on_togglebutton23_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_d_tog();

}


void
on_togglebutton24_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_dp_tog();

}


void
on_togglebutton27_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_b_tog();

}


void
on_togglebutton28_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_g_tog();

}


void
on_togglebutton25_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_a_tog();

}


void
on_togglebutton26_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_f_tog();

}


void
on_togglebutton30_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_c_tog();

}


void
on_togglebutton29_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_e_tog();

}


void
on_togglebutton31_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_d_tog();

}


void
on_togglebutton32_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_dp_tog();

}


void
on_togglebutton35_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd5_b_tog();

}


void
on_togglebutton36_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd5_g_tog();

}


void
on_togglebutton33_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd5_a_tog();

}


void
on_togglebutton34_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd5_f_tog();

}


void
on_togglebutton38_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd5_c_tog();

}


void
on_togglebutton37_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd5_e_tog();

}


void
on_togglebutton40_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd5_dp_tog();

}


void
on_togglebutton43_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd6_b_tog();
}


void
on_togglebutton44_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd6_g_tog();

}


void
on_togglebutton41_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd6_a_tog();

}


void
on_togglebutton42_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd6_f_tog();
}


void
on_togglebutton46_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd6_c_tog();

}


void
on_togglebutton45_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd6_e_tog();

}


void
on_togglebutton47_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd6_d_tog();

}


void
on_togglebutton48_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd6_dp_tog();

}


void
on_togglebutton51_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_b_tog();

}


void
on_togglebutton52_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_g_tog();

}


void
on_togglebutton49_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_a_tog();

}


void
on_togglebutton50_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_f_tog();

}


void
on_togglebutton54_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_c_tog();

}


void
on_togglebutton53_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_e_tog();

}


void
on_togglebutton55_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_d_tog();

}


void
on_togglebutton56_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_dp_tog();

}


void
on_togglebutton59_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd8_b_tog();
}


void
on_togglebutton60_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd8_g_tog();

}


void
on_togglebutton57_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd8_a_tog();

}


void
on_togglebutton58_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd8_f_tog();

}


void
on_togglebutton62_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd8_c_tog();

}


void
on_togglebutton61_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd8_e_tog();

}


void
on_togglebutton63_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd8_d_tog();
}


void
on_togglebutton64_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd8_dp_tog();

}


void
on_togglebutton39_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd5_d_tog();
}


void
on_togglebutton141_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd2_on_off();
}


void
on_togglebutton144_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	fnd5_on_off();
}


void
on_togglebutton142_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd3_on_off();

}


void
on_togglebutton145_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd6_on_off();

}


void
on_togglebutton146_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd7_on_off();

}


void
on_togglebutton147_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd8_on_off();

}


void
on_togglebutton140_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd1_on_off();

}


void
on_togglebutton143_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	fnd4_on_off();

}


void
on_togglebutton65_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot1_tog();
}



void
on_togglebutton66_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot2_tog();
}


void
on_togglebutton67_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot3_tog();

}


void
on_togglebutton68_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot4_tog();

}


void
on_togglebutton69_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot5_tog();

}


void
on_togglebutton71_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot7_tog();

}


void
on_togglebutton72_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot8_tog();

}


void
on_togglebutton73_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot9_tog();

}


void
on_togglebutton70_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	dot6_tog();
}


void
on_togglebutton74_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot10_tog();

}


void
on_togglebutton75_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot11_tog();

}


void
on_togglebutton76_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot12_tog();

}


void
on_togglebutton77_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot13_tog();

}


void
on_togglebutton78_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot14_tog();

}


void
on_togglebutton79_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot15_tog();

}


void
on_togglebutton80_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot16_tog();

}


void
on_togglebutton81_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot17_tog();

}


void
on_togglebutton82_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	dot18_tog();
}


void
on_togglebutton83_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	dot19_tog();
}


void
on_togglebutton84_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot20_tog();

}


void
on_togglebutton85_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot21_tog();

}


void
on_togglebutton86_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot22_tog();

}


void
on_togglebutton87_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot23_tog();

}


void
on_togglebutton88_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot24_tog();

}


void
on_togglebutton89_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot25_tog();

}


void
on_togglebutton90_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot26_tog();

}


void
on_togglebutton91_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	dot27_tog();
}


void
on_togglebutton95_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	dot31_tog();
}


void
on_togglebutton92_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot28_tog();

}


void
on_togglebutton93_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot29_tog();

}


void
on_togglebutton94_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot30_tog();

}


void
on_togglebutton96_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot32_tog();

}


void
on_togglebutton97_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot33_tog();

}


void
on_togglebutton98_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot34_tog();

}


void
on_togglebutton99_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot35_tog();
}


void
on_togglebutton150_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	dot_all_tog();
}


void
on_togglebutton130_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	led1_tog();
}


void
on_togglebutton131_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	led2_tog();

}


void
on_togglebutton132_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	led3_tog();

}


void
on_togglebutton133_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	led4_tog();

}


void
on_togglebutton134_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	led5_tog();

}


void
on_togglebutton135_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	led6_tog();

}


void
on_togglebutton136_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	led7_tog();

}


void
on_togglebutton137_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	led8_tog();

}


void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	st_forward();
}


void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	st_reverse();
}


void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	speed_up();
}


void
on_button9_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	speed_down();
}


void
on_button10_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	st_stop();
}


void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	dc_forward();
}


void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	dc_left_turn();
}


void
on_button3_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	dc_stop();
}


void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	dc_right_turn();
}


void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	dc_reverse();
}



void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer	user_data)
{
	clcd_test();

}

gboolean
on_ieb_window_destroy_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
 gtk_exit( 0 );
  return FALSE;
}


gboolean
on_ieb_window_delete_event             (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
 gtk_exit( 0 );
  return FALSE;
}

