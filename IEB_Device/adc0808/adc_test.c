/*
 * X-HYPER270-TKU IEB Board Rev
 * ADC Control Program
 * 2006-08-23	<kjlee@hybus.net>
 */

#include    <stdio.h>
#include    <fcntl.h>

#define ADC_VR          0x3
#define ADC_LS          0x2
#define ADC_LOOP        0x1

#define CONVT		500

#define adc_dev		"/dev/adc0808"

int main_menu(void){
	char key;
	printf("\n");
	printf("******** ADC Check MENU ********\n");
	printf("* 1. ADC LOOPBACK TEST	       *\n");
	printf("* 2. ADC Lignt Sensor TEST     *\n");
	printf("* 3. ADC VR		       *\n");
	printf("* 0. Exit Program              *\n");
	printf("********************************\n");
	printf("\n");

	printf("Select the command number : ");
	key = getc(stdin);
	getc(stdin);
	return key;
}

int main(int ac, char *av[]){
	unsigned char adc_value;
	char key, data;
	int cnt, dev, conf = 0;
	
	dev = open(adc_dev, O_RDWR);
    	if(dev < 0){
        fprintf(stderr, "Cannot open ADC (%d)", dev);
        exit(2);
    	}

	while((key = main_menu()) != 0x30)
	{
		switch(key)
		{
			case 0x31:
				printf("--------------\n");
				printf("  Input Data  \n");
				printf("--------------\n");
				printf("\n");
				data = getc(stdin);
				getc(stdin);
				ioctl(dev, ADC_LOOP, (unsigned long)data);
				break;
			case 0x32:
				printf("ADC Light Sensor TEST\n");
			 	ioctl(dev, ADC_LS, 0);
				break;
			case 0x33:
				printf("ADC VR TEST\n");
				ioctl(dev, ADC_VR, 0);
				break;
			default:
				printf("Unknow command...\n");
				conf = 1;
				break;
        	}
		if(conf != 1)
		{
			for(cnt = 0; cnt <= CONVT; cnt++)
			{
				read(dev, &adc_value, sizeof(adc_value));
				printf("ADC Data = %x\n", adc_value);
			}
		}
		conf = 0;
	}
	printf("Exit Program\n");
	close(dev);
	return 0;
}
      
