/*
 * Glade�� ������ �ʱ�main.c ���� �Դϴ�.������ �ʿ��մϴ�.
 * Glade�� �� ������ ����� �ʽ��ϴ�.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>



#include "interface.h"
#include "support.h"

#include "fnd_test.h"
#include "dot_test.h"
#include "led_test.h"
#include "st_motor_test.h"
#include "dc_motor_test.h"

GtkWidget *ieb_window;

int ptimer;
gint UpdateProgressTimer(gpointer data);
char key_value;

int dev3, dev2;
int clcd_test();
int clcd_init();
int key_init();

