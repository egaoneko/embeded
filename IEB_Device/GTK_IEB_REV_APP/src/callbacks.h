#include <gnome.h>
#include <fcntl.h>
#include <stdio.h>
#include "fnd_test.h"
#include "dot_test.h"

void
on_togglebutton1_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);


void
on_togglebutton2_pressed               (GtkButton       *button,
                                        gpointer         user_data);

void
on_togglebutton2_released              (GtkButton       *button,
                                        gpointer         user_data);

void
on_togglebutton3_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton4_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton2_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton6_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton5_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton7_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton8_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton11_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton12_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton9_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton10_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton14_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton13_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton15_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton16_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton19_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton20_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton17_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton18_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton22_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton21_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton23_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton24_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton27_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton28_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton25_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton26_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton30_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton29_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton31_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton32_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton35_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton36_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton33_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton34_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton38_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton37_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton40_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton43_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton44_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton41_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton42_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton46_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton45_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton47_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton48_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton51_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton52_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton49_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton50_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton54_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton53_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton55_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton56_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton59_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton60_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton57_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton58_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton62_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton61_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton63_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton64_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton39_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton141_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton144_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton142_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton145_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton146_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton147_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton140_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton143_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton70_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton65_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton66_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_togglebutton66_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton67_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton68_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton69_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton71_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton72_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton73_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton70_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton74_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton75_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton76_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton77_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton78_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton79_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton80_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton81_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton82_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton83_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton84_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton85_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton86_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton87_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton88_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton89_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton90_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton91_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton95_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton92_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton93_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton94_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton96_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton97_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton98_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton99_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton150_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton130_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton131_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton132_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton133_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton134_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton135_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton136_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_togglebutton137_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button9_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button10_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button3_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_ieb_window_destroy_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_ieb_window_delete_event             (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);
