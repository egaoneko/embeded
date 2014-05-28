#include "main.h"

#define clcd_dev "/dev/clcd"
#define key_dev  "/dev/key"
#define MAXCHAR	32

int
main (int argc, char *argv[])
{
  
#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif
  gnome_init ("ieb", VERSION, argc, argv);

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  ieb_window = create_ieb_window ();

  fnd_init();
  dot_init();
  led_init();
  st_motor_init();
  dc_motor_init();
  clcd_init();
  key_init();
 
  gtk_widget_show (ieb_window);
  ptimer = gtk_timeout_add(200, UpdateProgressTimer, NULL);
  gtk_main ();
  return 0;
}

gint UpdateProgressTimer(gpointer data)
{
	unsigned char key_num,i;
	
	GtkWidget *handle[16];
	read(dev2, &key_num, sizeof(key_num));
	//printf(" Push Key Num %d \n", key_num);
	
	handle[0] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton100");
	handle[1] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton101");
	handle[2] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton102");
	handle[3] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton103");
	handle[4] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton104");
	handle[5] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton105");
	handle[6] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton106");
	handle[7] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton107");
	handle[8] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton108");
	handle[9] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton109");
	handle[10] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton110");
	handle[11] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton111");
	handle[12] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton112");
	handle[13] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton113");
	handle[14] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton114");
	handle[15] = lookup_widget(GTK_WIDGET(ieb_window), "togglebutton115");

	switch (key_num){
	case 1 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[0]), TRUE); break;
	case 2 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[1]), TRUE); break;
	case 3 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[2]), TRUE); break;
	case 4 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[3]), TRUE); break;
	case 5 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[4]), TRUE); break;
	case 6 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[5]), TRUE); break;
	case 7 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[6]), TRUE); break;
	case 8 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[7]), TRUE); break;
	case 9 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[8]), TRUE); break;
	case 10 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[9]), TRUE); break;
	case 11 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[10]), TRUE); break;
	case 12 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[11]), TRUE); break;
	case 13 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[12]), TRUE); break;
	case 14 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[13]), TRUE); break;
	case 15 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[14]), TRUE); break;
	case 16 : gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[15]), TRUE); break;
	
	default :
		for(i=0 ; i< 16 ;i++)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(handle[i]), FALSE); break;
	}
	return TRUE;
}

int clcd_test(){

	GtkWidget *handle1 = 0;
	const gchar *entry_text;
	char buf[32];
	int text_len;

	handle1 = lookup_widget(GTK_WIDGET(ieb_window), "entry1");
	entry_text = gtk_entry_get_text(GTK_ENTRY(handle1));
	printf("Entry contents : %s\n", entry_text);	
	memset (buf, 0, sizeof(buf));
	text_len = strlen(entry_text);
	printf("Text len %d\n", text_len);	
	
	if(text_len >  MAXCHAR)
		text_len= MAXCHAR;
	memcpy(buf, entry_text, text_len);

	write(dev3, buf, MAXCHAR);
	
	return 0;	

}

int clcd_init(){

	dev3 = open( clcd_dev, O_RDWR);
	if(dev3 <0){
		fprintf(stderr, "cannot open /dev/clcd (%d)", dev3);
		exit(2);
	}
	return 0;
}

int key_init(){
	dev2= open( key_dev, O_RDWR);
	if(dev2 <0){
		fprintf(stderr, "cannot open /dev/key (%d)", dev2);
		exit(2);
	}
	return 0;

}
