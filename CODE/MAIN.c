//**************************************************************
//                 ******** CY V1.00  *******
//**************************************************************
//Controller:	ATmega128 (Crystal: INTERNAL 8Mhz)
//Compiler:		winAVR (AVR-GCC)
//
//				
//Date:			11/JULY/2013
//********************************************************

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avr/eeprom.h>
#include "lcd.h"
#include "Devicefunctions.h"
#include "HX711.h"
//**************  INTERNAL HEADER FILES REQUIRED  **************
 
#include "ControllerModule.h"
 

//====== SOUND RELATED DEFENITIONS ====== //
//#define SOUND_OFF
#define FALSE_MOTRO_ALARM_DEGR 2
#define fool 14.00 
 

void menu(void);
void Eprom_Write(unsigned int , unsigned char );
unsigned char EEPROM_read(unsigned int );
//************************************************************
// *************  FUNCTION DECLARATION PART ******************
//************************************************************ 


//********************* GLOBAL VARIABLES  ***********************//
///////////////////////////////////////////////////////////////////

volatile char INT0_Recieved;  //
volatile char INT1_Recieved;
 
char tempbuf[50];
 
extern volatile char FrameBuf[35];  
volatile char CrutchInteruptFlag;

float volt;

extern volatile char buf[80];  
volatile unsigned long int Joystick_Interrupt_Counter;
int key; 
volatile uint32_t Count_ChannelA,Temp_Count_ChannelA; 
extern float weight,B_Load,F_Rate,Frate_Totalizer;
extern volatile float W_Span,L_Offset,U_Load,O_Load,C_Factor,Speed;
//extern volatile char W_Span_Buf[10];
//extern volatile char L_Offset_Buf[10];
//extern volatile char U_Load_Buf[10];
//extern volatile char O_Load_Buf[10];
//extern volatile char C_Factor_Buf[10];
extern float Epromadress_W_Span EEMEM; 
extern char KeyPressedStatus;
extern volatile int TCNTCOUNT;
extern volatile unsigned int Time_counter;
//************************************************************
// *************MAIN FUNCTION STARTING************************
//************************************************************ 
int main(void)
{
 
   
 
	
	
	  

	//----------------  INITIALISATION OF MODULES  -----------------//

	Port_Init();
	 sei();
	USART0_INIT();
	USART1_INIT();
	 USART0_Transmit_Char('1');
//PORTC = 0XFF;
 		//USART1_Transmit_Char('1');
	ADC_Init();
//	_delay_ms(1000);
	lcd_init(LCD_DISP_ON);
	HX711_init(128);
	HX711_set_scale(1.f/*242300.88*/);
	HX711_set_gain(128);



	 	 
 	char pinval;
	#if F_CPU == 8000000
	 	TCNTCOUNT = 248;
	#endif

	#if F_CPU == 16000000
		TCNTCOUNT = 240;
	#endif
	

//		      76543210	
	DDRC  = 0b00000000;
	//		  76543210
	PORTC = 0b00001111;

 	W_Span = eeprom_read_float(&Epromadress_W_Span);
	L_Offset = eeprom_read_float(&Epromadress_L_Offset);
	U_Load = eeprom_read_float(&Epromadress_U_Load);
	O_Load = eeprom_read_float(&Epromadress_O_Load);
	C_Factor = eeprom_read_float(&Epromadress_C_Factor);
	Speed = eeprom_read_float(&Epromadress_Speed);


	TIMER0_INIT();
	Time_counter = 0;

	Home();	 
	_delay_ms(2000);	 
	lcd_clrscr();
 	 

  

/*W_Span_Buf[0] = '\0';
L_Offset_Buf[0] = '\0';
U_Load_Buf[0] = '\0';*/
	//-------------  STAR OF CONTINUOUS WHILE 1  -------------//
	while(1)
	{
	
  	

	    //sprintf(buf,"%d",Time_counter);
		//USART0_Transmit_String(buf); 
	    PageOne();
		    
		if(key == 'P')
		{		 
			key = GetKeyPressed();
			//	Process_Data_Page();
			Passward_Verification();
		
		}
/* 
volt = AverageADC(0,100);
sprintf(buf,"%f",volt);
USART0_Transmit_String(buf);     
USART0_Transmit_Char(13);*/

//Home();
//USART0_Transmit_Char('A');
// key = GetKeyPressed();
 
 //USART0_Transmit_Char((PINC<<4));
// USART0_Transmit_Char(key); 
     
 	}// END OF CONTINUOUS WHILE 1
	return (0);
}// END OF MAIN

//-----------------------------------  END OF MAIN FUNCTION  -------------------------------
 

 
