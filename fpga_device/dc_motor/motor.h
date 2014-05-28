#define _EDU_CS3			0x12200000

#define DEVICE_NAME			"dc_motor"	        
#define OSTIMER_IRQ			IRQ_OST1

#define Sec_Clk				3686400
#define Usec_Clk			(Sec_Clk/100000)   // 100uSec

#define OSTIMER_ON	OIER |= OIER_E1; OSSR = OSSR_M1 
#define OSTIMER_OFF	OIER &= ~OIER_E1; OSSR = OSSR_M1 

static void *mem_base;
#define MOTOR   (*((volatile unsigned char *)(mem_base)))

#define MOTOR_SetBit(x) { dc_motor_port |= (1<<x); MOTOR = dc_motor_port; }
#define MOTOR_ClearBit(x) { dc_motor_port &= ~(1<<x); MOTOR = dc_motor_port; }

