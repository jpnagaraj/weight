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
extern char LeftThighBuf[4];
extern char LeftKneeBuf[4];
extern char RightThighBuf[4];
extern char RightKneeBuf[4];
extern char BatteryBuf[4];
extern char ThighSpeedBuf[2];
extern char KneeSpeedBuf[2];
extern char LiftBuf[2];
extern char StrideBuf[2];
extern volatile char FrameBuf[35];  
volatile char CrutchInteruptFlag;

float volt;

extern volatile char buf[80];  
volatile unsigned long int Joystick_Interrupt_Counter;
int key; 
uint32_t Count_ChannelA,Temp_Count_ChannelA; 
float weight;
extern volatile float W_Span,L_Offset,U_Load,O_Load,C_Factor;
extern volatile char W_Span_Buf[10];
extern volatile char L_Offset_Buf[10];
extern volatile char U_Load_Buf[10];
extern volatile char O_Load_Buf[10];
extern volatile char C_Factor_Buf[10];
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
	Home();	 
	_delay_ms(2000);	 
	lcd_clrscr();	 	 
 	 char pinval;
	

//		      76543210	
	DDRC  = 0b00000000;
	//		  76543210
	PORTC = 0b00001111;

 

 
/*W_Span_Buf[0] = '\0';
L_Offset_Buf[0] = '\0';
U_Load_Buf[0] = '\0';*/
	//-------------  STAR OF CONTINUOUS WHILE 1  -------------//
	while(1)
	{


	    PageOne();

	    
		if(key == '#')
		{				
			Process_Data_Page();			
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
    
 
 
  
  /*if(key == '*')
  {
  	Home();	 
	key = 0;
  }*/
  
 	}// END OF CONTINUOUS WHILE 1
	return (0);
}// END OF MAIN

//-----------------------------------  END OF MAIN FUNCTION  -------------------------------
 

/*

	if(ProcessDataPageCursor == 2)
					{
						   
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  lcd_gotoxy(8,2);
				          				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[0] = '1';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[0] = '2';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[0] = '3';
														 L_Offset = atof(L_Offset_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '4';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[0] = '5';
														 L_Offset = atof(L_Offset_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[0] = '6';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '7';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '8';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '9';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '0';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
											 }									
								         break;
								case 2:  lcd_gotoxy(9,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[1] = '1';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[1] = '2';
														 L_Offset = atof(L_Offset_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[1] = '3';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '4';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[1] = '5';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[1] = '6';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '7';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '8';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '9';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '0';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
										  }	
								         break;
								case 3:  lcd_gotoxy(10,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[2] = '1';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[2] = '2';
														 L_Offset = atof(L_Offset_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[2] = '3';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '4';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[2] = '5';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[2] = '6';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '7';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '8';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '9';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '0';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5: lcd_gotoxy(12,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[4] = '1';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[4] = '2';
														 L_Offset = atof(L_Offset_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[4] = '3';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '4';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[4] = '5';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[4] = '6';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '7';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '8';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '9';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '0';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
										  }	
								         break;
								case 6: lcd_gotoxy(13,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[5] = '1';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[5] = '2';
														 L_Offset = atof(L_Offset_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[5] = '3';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '4';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[5] = '5';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[5] = '6';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '7';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '8';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '9';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '0';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
										  }	
								         break;
								case 7: lcd_gotoxy(14,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[6] = '1';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[6] = '2';
														 L_Offset = atof(L_Offset_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[6] = '3';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '4';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[6] = '5';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[6] = '6';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '7';
														 L_Offset = atof(L_Offset_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '8';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '9';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '0';
														 L_Offset = atof(L_Offset_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
														 lcd_puts(L_Offset_Buf);
										 				 break;	
										  }	
								         break;
					        } 
						    
					}*/
