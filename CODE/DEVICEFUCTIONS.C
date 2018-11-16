
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avr/eeprom.h>
#include "lcd.h"
#include "Devicefunctions.h"
#include "HX711.h" 
#include "ControllerModule.h"


void PageOne(void)
{

static int Weightlength,B_Loadlength,F_Ratelength,Frate_Totalizerlength;
static int Weighttemplength,B_Loadtemplength,F_Ratetemplength,Frate_Totalizertemplength;
char Weight_Buf[10],B_Load_Buf[10],Speed_Buf[10],F_Rate_Buf[10],Frate_Totalizer_Buf[10];


	    key = GetKeyPressed();
		sprintf(buf,"%c", key);
		USART0_Transmit_String(buf);
	
    	//HX711_tare(10);
    	//Count_ChannelA = HX711_read();
		if(Time_counter >= 10)	
		{
		 
			Count_ChannelA = HX711_read();
			//Count_ChannelA = 985;
		 	//sprintf(buf,"%d",Count_ChannelA);
			//ISR_USART0_Transmit_String(buf); 
			Time_counter = 0;
		}
	    
		
		lcd_gotoxy(0,0);
 		lcd_puts("Weight");
		lcd_gotoxy(0,1);
 		lcd_puts("B Load");
		lcd_gotoxy(18,1);
 		lcd_puts("");
		lcd_gotoxy(0,2);
 		lcd_puts("Speed");
		lcd_gotoxy(18,2);
 		lcd_puts("");
		lcd_gotoxy(0,3);
 		lcd_puts("F Rate");
		lcd_gotoxy(18,3);
 		lcd_puts("");
		lcd_gotoxy(16,0);
 		lcd_puts("Kg");
		lcd_gotoxy(16,1);
 		lcd_puts("Kg/m");
		lcd_gotoxy(16,2);
 		lcd_puts("m/s");
		lcd_gotoxy(16,3);
 		lcd_puts("TPH");

		weight = ((float)Count_ChannelA -8388656.0)/67.0; 
		B_Load = (weight/W_Span);
		F_Rate = (B_Load*Speed*3.6*C_Factor);
		//sprintf(buf,"%lu", Count_ChannelA);
		//USART0_Transmit_String(buf);
	//	sprintf(Weight_Buf,"%.3f", weight);
	//	USART0_Transmit_String(buf);
		USART0_Transmit_Char(13);
		

		sprintf(Weight_Buf,"%08.2f", weight);		
		Weightlength = strlen(Weight_Buf);
			
		sprintf(B_Load_Buf,"%08.2f", B_Load);		
		B_Loadlength = strlen(B_Load_Buf);
		sprintf(F_Rate_Buf,"%08.2f", F_Rate);		
		F_Ratelength = strlen(F_Rate_Buf);

		if(Weightlength < Weighttemplength)
		{
			//lcd_clrscr();
			sprintf(Weight_Buf,"%-8s", Weight_Buf);
		 
		}
		if(B_Loadlength < B_Loadtemplength)
		{
			//lcd_clrscr();
			sprintf(B_Load_Buf,"%-8s", B_Load_Buf);
		 
		}
		if(F_Ratelength < F_Ratetemplength)
		{
			//lcd_clrscr();
			sprintf(F_Rate_Buf,"%-9s", F_Rate_Buf);
		 
		}
		lcd_gotoxy(7,0);
		lcd_puts(Weight_Buf);
		Weighttemplength =  Weightlength;
		lcd_gotoxy(7,1);
		lcd_puts(B_Load_Buf);
		B_Loadtemplength =  B_Loadlength;
		lcd_gotoxy(10,2);
		sprintf(Speed_Buf,"%05.2f", Speed);	
		lcd_puts(Speed_Buf);
		lcd_gotoxy(7,3);
		lcd_puts(F_Rate_Buf);
		F_Ratetemplength =  F_Ratelength;


		// For scrolling the page one 
		if(key == 'B')
		{
		    lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Total");
			lcd_gotoxy(0,1);
			lcd_puts("Status");
			while(key != 'A')
			{
			    key = GetKeyPressed();
				if(Time_counter >= 10)	
				{
	 
					Count_ChannelA = HX711_read();
					//Count_ChannelA = 985;
				 	//sprintf(buf,"%d",Count_ChannelA);
					//ISR_USART0_Transmit_String(buf); 
					Time_counter = 0;
				}

				weight = ((float)Count_ChannelA -8388656.0)/67.0; 
				B_Load = (weight/W_Span);
				F_Rate = (B_Load*Speed*3.6*C_Factor);
				Frate_Totalizer = ((F_Rate/216000) + Frate_Totalizer);
				if(Frate_Totalizer >= 99999.00)
				{
					Frate_Totalizer = 0;
				}
				sprintf(Frate_Totalizer_Buf,"%08.2f", Frate_Totalizer);		
				Frate_Totalizerlength = strlen(Frate_Totalizer_Buf);

				if(Frate_Totalizerlength < Frate_Totalizertemplength)
				{
					//lcd_clrscr();
					sprintf(Frate_Totalizer_Buf,"%-9s", Frate_Totalizer_Buf);
		 
				}
				lcd_gotoxy(7,0);
				lcd_puts(Frate_Totalizer_Buf);
				Frate_Totalizertemplength =  Frate_Totalizerlength;
	    		
				

			}
		}
}


void Passward_Verification(void)
{
char PasswordFlag = 0;
int ProcessDataPasswordCount = 0;
char ProcessDataPasswordBuf[8] = "0000";
char ProcessDataPassword_Set_Buf[8]="1234";
int CalibrateDataPasswordCount = 0;
char CalibrateDataPasswordBuf[8] = "0000";
char CalibrateDataPassword_Set_Buf[8]="1234";


			PasswordFlag = 0;
		 	unsigned char PasswordPageCursor = 1;
		    unsigned char PasswordLineCursor = 1;
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("   ENTER PASSWORD");
			lcd_gotoxy(0,2);
			lcd_puts("Process");
			lcd_gotoxy(0,3);
			lcd_puts("Calibrate");
			lcd_gotoxy(10,2);
			lcd_command(LCD_DISP_ON_CURSOR_BLINK);
			while(PasswordFlag != 1)
			{
				key = GetKeyPressed();
				if(key == 'A')
				{
				    _delay_ms(300);
					PasswordPageCursor--;
				}
		 	    if(key == 'B')
				{
					_delay_ms(300); 
					PasswordPageCursor++;
				}
				if(	PasswordPageCursor > 2)
				{
					PasswordPageCursor = 2;
				}
				if(	PasswordPageCursor < 1)
				{
					PasswordPageCursor = 1;
				}
				if(PasswordPageCursor == 1)
				{
					//sprintf(buf,"%d", ProcessDataPasswordCount);
					//USART0_Transmit_String(buf);
					lcd_gotoxy(10,2);
					lcd_command(LCD_DISP_ON_CURSOR_BLINK);
					if((KeyPressedStatus == 1)&&(key != 'A')&&(key!='B')&&(key != 'C')&&(key!='D')
						&&(key!='#')&&(key!='*'))
					{
						  ProcessDataPasswordBuf[ProcessDataPasswordCount] = key;
						  while(KeyPressedStatus == 1)	
						  {
							key = GetKeyPressed();
						  }
						  
						  
						  ProcessDataPasswordCount++;
						  lcd_gotoxy((ProcessDataPasswordCount+9),2);
						  lcd_putc('*');
						  lcd_gotoxy((ProcessDataPasswordCount+10),2);
						  lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						 // sprintf(buf,"%d", ProcessDataPasswordCount);
						 // USART0_Transmit_String(buf);
						  USART0_Transmit_String(ProcessDataPasswordBuf);
						  USART0_Transmit_String(ProcessDataPassword_Set_Buf);
						  while(ProcessDataPasswordCount < 4)
						  {
						  //ProcessDataPasswordBuf[ProcessDataPasswordCount] = key;
						  //sprintf(buf,"%d", ProcessDataPasswordCount);
						  //USART0_Transmit_String(buf);
						  USART0_Transmit_String(ProcessDataPasswordBuf);
						   
						  key = GetKeyPressed();
							if((KeyPressedStatus == 1)&&(key != 'A')&&(key!='B')&&(key != 'C')&&(key!='D')
								&&(key!='#')&&(key!='*'))
							{
								ProcessDataPasswordBuf[ProcessDataPasswordCount] = key;
								while(KeyPressedStatus == 1)	
							  	{
									key = GetKeyPressed();
							  	}
								ProcessDataPasswordCount++;
								lcd_gotoxy((ProcessDataPasswordCount+9),2);
						  		lcd_putc('*');
								lcd_gotoxy((ProcessDataPasswordCount+10),2);
						  		lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								
							}
						  }
						  lcd_gotoxy(10,2);
						  lcd_puts("      ");
						  if(strcmp(ProcessDataPasswordBuf,ProcessDataPassword_Set_Buf) == 0)
						  {
						  	USART0_Transmit_String("congrats correct password");
							lcd_gotoxy(10,2);
						  	lcd_puts("GRANTED");
							_delay_ms(1000);
							Process_Data_Page();
							lcd_clrscr();
							lcd_gotoxy(0,0);
							lcd_puts("   ENTER PASSWORD");
							lcd_gotoxy(0,2);
							lcd_puts("Process");
							lcd_gotoxy(0,3);
							lcd_puts("Calibrate");
							lcd_gotoxy(10,2);
							lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						  }
						  else
						  {
							lcd_gotoxy(10,2);
						  	lcd_puts("DENIED");
							_delay_ms(1000);
							lcd_gotoxy(10,2);
						  	lcd_puts("      ");
						  }
						  ProcessDataPasswordCount = 0;
					}
						
				}
				if(PasswordPageCursor == 2)
				{
					 
					//sprintf(buf,"%d", ProcessDataPasswordCount);
					//USART0_Transmit_String(buf);
					lcd_gotoxy(10,3);
					lcd_command(LCD_DISP_ON_CURSOR_BLINK);
					if((KeyPressedStatus == 1)&&(key != 'A')&&(key!='B')&&(key != 'C')&&(key!='D')
						&&(key!='#')&&(key!='*'))
					{
						  CalibrateDataPasswordBuf[CalibrateDataPasswordCount] = key;
						  while(KeyPressedStatus == 1)	
						  {
							key = GetKeyPressed();
						  }
						  
						  
						  CalibrateDataPasswordCount++;
						  lcd_gotoxy((CalibrateDataPasswordCount+9),3);
						  lcd_putc('*');
						  lcd_gotoxy((CalibrateDataPasswordCount+10),3);
						  lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						 // sprintf(buf,"%d", CalibrateDataPasswordCount);
						 // USART0_Transmit_String(buf);
						  USART0_Transmit_String(CalibrateDataPasswordBuf);
						  USART0_Transmit_String(CalibrateDataPassword_Set_Buf);
						  while(CalibrateDataPasswordCount < 4)
						  {
						  //CalibrateDataPasswordBuf[CalibrateDataPasswordCount] = key;
						  //sprintf(buf,"%d", CalibrateDataPasswordCount);
						  //USART0_Transmit_String(buf);
						  USART0_Transmit_String(CalibrateDataPasswordBuf);
						   
						  key = GetKeyPressed();
							if((KeyPressedStatus == 1)&&(key != 'A')&&(key!='B')&&(key != 'C')&&(key!='D')
								&&(key!='#')&&(key!='*'))
							{
								CalibrateDataPasswordBuf[CalibrateDataPasswordCount] = key;
								while(KeyPressedStatus == 1)	
							  	{
									key = GetKeyPressed();
							  	}
								CalibrateDataPasswordCount++;
								lcd_gotoxy((CalibrateDataPasswordCount+9),3);
						  		lcd_putc('*');
								lcd_gotoxy((CalibrateDataPasswordCount+10),3);
						  		lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								
							}
						  }
						  lcd_gotoxy(10,3);
						  lcd_puts("      ");
						  if(strcmp(CalibrateDataPasswordBuf,CalibrateDataPassword_Set_Buf) == 0)
						  {
						  	USART0_Transmit_String("congrats correct password");
							lcd_gotoxy(10,3);
						  	lcd_puts("GRANTED");
							_delay_ms(1000);
							Calibrate_Data_Page();
							lcd_clrscr();
							lcd_gotoxy(0,0);
							lcd_puts("   ENTER PASSWORD");
							lcd_gotoxy(0,2);
							lcd_puts("Process");
							lcd_gotoxy(0,3);
							lcd_puts("Calibrate");
							lcd_gotoxy(10,3);
							lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						  }
						  else
						  {
							lcd_gotoxy(10,3);
						  	lcd_puts("DENIED");
							_delay_ms(1000);
							lcd_gotoxy(10,3);
						  	lcd_puts("      ");
						  }
						  CalibrateDataPasswordCount = 0;
					}
					
						
				}
				if(key == '*')
				{
					PasswordFlag = 1;
				}
				/*switch (ProcessDataLineCursor)  // Main Menu Switch statement
					  {
						case 1: 
							   break;	
					  }*/




			}
			lcd_command(LCD_DISP_ON);
			lcd_clrscr();
		   
				 
}

void Calibrate_Data_Page(void)
{
char MI_Buf[10];
char ZO_Buf[10];
char SN_Buf[10];
char MA_Buf[10];
 
 

unsigned char CalibrateDataPageCursor = 1;
unsigned char CalibrateDataLineCursor = 1;	 
unsigned char CalibrateDataPage1_Print_Falg = 0,CalibrateDataPage2_Print_Falg = 0;

			MI = eeprom_read_float(&Epromadress_MI);
			ZO = eeprom_read_float(&Epromadress_ZO);
			SN = eeprom_read_float(&Epromadress_SN);
			MA = eeprom_read_float(&Epromadress_MA);
			 


 			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("CALIBRATE DATA....");
			lcd_gotoxy(0,1);
			lcd_puts("MI");
			lcd_gotoxy(0,2);
			lcd_puts("ZO");
			lcd_gotoxy(0,3);
			lcd_puts("SN");
			lcd_gotoxy(8,1);
			sprintf(MI_Buf,"%07.3f", W_Span);
			lcd_puts(MI_Buf);
			lcd_command(LCD_DISP_ON_CURSOR_BLINK);
			lcd_gotoxy(8,2);
			sprintf(ZO_Buf,"%07.3f", L_Offset);
			lcd_puts(ZO_Buf);
			lcd_gotoxy(8,3);
			sprintf(SN_Buf,"%07.3f", U_Load);
			lcd_puts(SN_Buf);
			
			
			while(key != '*')
			{
			    key = GetKeyPressed();
				sprintf(buf,"%d", CalibrateDataPageCursor);
				USART0_Transmit_String(buf);
				sprintf(buf,"%c", key);
				USART0_Transmit_String(buf);
				USART0_Transmit_Char(13);
				    if(key == 'A')
					{
					    _delay_ms(300);
						CalibrateDataPageCursor--;
					}
			 	    if(key == 'B')
					{
						_delay_ms(300); 
						CalibrateDataPageCursor++;
					}
					if(key == 'C')
					{
					    _delay_ms(300);
						CalibrateDataLineCursor--;
					}
			 	    if(key == 'D')
					{
						_delay_ms(300); 
						CalibrateDataLineCursor++;
					}
					if(	CalibrateDataPageCursor > 4)
					{
						
						CalibrateDataPageCursor = 4;
					}
					if(	CalibrateDataPageCursor < 1)
					{
							CalibrateDataPageCursor = 1;
					}
					if(	CalibrateDataLineCursor > 7)
					{
						
						CalibrateDataLineCursor = 7;
					}
					if(	CalibrateDataLineCursor < 1)
					{
							CalibrateDataLineCursor = 1;
					}

					if((CalibrateDataPageCursor <= 3)&&(CalibrateDataPage1_Print_Falg == 0))
					{
							lcd_clrscr();
							lcd_gotoxy(0,0);
							lcd_puts("CALIBRATE DATA....");
							lcd_gotoxy(0,1);
							lcd_puts("MI");
							lcd_gotoxy(0,2);
							lcd_puts("ZO");
							lcd_gotoxy(0,3);
							lcd_puts("SN");
							lcd_gotoxy(8,1);
							sprintf(MI_Buf,"%07.3f", MI);
							lcd_puts(MI_Buf);
							lcd_gotoxy(8,2);
							sprintf(ZO_Buf,"%07.3f", ZO);
							lcd_puts(ZO_Buf);
							lcd_gotoxy(8,3);
							sprintf(SN_Buf,"%07.3f", SN);
							lcd_puts(SN_Buf);
							CalibrateDataPage1_Print_Falg = 1;
							CalibrateDataPage2_Print_Falg = 0;
						 
					}
					//ProcessDataPage2_Print_Falg = 0;
					if((CalibrateDataPageCursor >= 4)&&(CalibrateDataPage2_Print_Falg == 0))
					{
						USART0_Transmit_String("page 2");
							lcd_clrscr();
							lcd_gotoxy(0,0);
							lcd_puts("CALIBRATE DATA....");
							lcd_gotoxy(0,1);
							lcd_puts("MA");
							lcd_gotoxy(8,1);
							sprintf(MA_Buf,"%07.3f", MA);
							lcd_puts(MA_Buf);
							 
							CalibrateDataPage2_Print_Falg = 1;
							CalibrateDataPage1_Print_Falg = 0;
						 
					}	
					 

					if(CalibrateDataPageCursor == 1)
					{
						   //lcd_gotoxy(8,1);
				           //lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						   //USART0_Transmit_String(W_Span_Buf);
						    switch (CalibrateDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  MI = atof(MI_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(MI_Buf,"%07.3f", MI);
										 lcd_puts(MI_Buf);
										 lcd_gotoxy(8,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MI_Buf[0] = '1';
														 
														 
								        				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MI_Buf[0] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MI_Buf[0] = '3';
														 
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MI_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MI_Buf[0] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MI_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MI_Buf[0] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MI_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MI_Buf[0] = '9';
														 
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MI_Buf[0] = '0';
														  
										 				 break;	
											 }	
																		
								         break;
								case 2:  MI = atof(MI_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(MI_Buf,"%07.3f", MI);
										 lcd_puts(MI_Buf); 
										 lcd_gotoxy(9,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MI_Buf[1] = '1';
														 MI = atof(MI_Buf);	 
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MI_Buf[1] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MI_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MI_Buf[1] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MI_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MI_Buf[1] = '6';
														 
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MI_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MI_Buf[1] = '8';
														 
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MI_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MI_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  MI = atof(MI_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(MI_Buf,"%07.3f", MI);
										 lcd_puts(MI_Buf);
										 lcd_gotoxy(10,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MI_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MI_Buf[2] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MI_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MI_Buf[2] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MI_Buf[2] = '5';
														 
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MI_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MI_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MI_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MI_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MI_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5:  MI = atof(MI_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(MI_Buf,"%07.3f", MI);
										 lcd_puts(MI_Buf);
										 lcd_gotoxy(12,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MI_Buf[4] = '1';
														 
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MI_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MI_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MI_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MI_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MI_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MI_Buf[4] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MI_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MI_Buf[4] = '9';
														 
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MI_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  MI = atof(MI_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(MI_Buf,"%07.3f", MI);
										 lcd_puts(MI_Buf);
										 lcd_gotoxy(13,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MI_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MI_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MI_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MI_Buf[5] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MI_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MI_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MI_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MI_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MI_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MI_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  MI = atof(MI_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(MI_Buf,"%07.3f", MI);
										 lcd_puts(MI_Buf);
										 lcd_gotoxy(14,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MI_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MI_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MI_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MI_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MI_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MI_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MI_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MI_Buf[6] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MI_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MI_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
		 
						    
					}
					if(CalibrateDataPageCursor == 2)
					{
							//lcd_gotoxy(8,2);
				          	//lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						   // USART0_Transmit_String(L_Offset_Buf);
						    switch (CalibrateDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  ZO = atof(ZO_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(ZO_Buf,"%07.3f", ZO);
										 lcd_puts(ZO_Buf);
										 lcd_gotoxy(8,2);
				          				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 ZO_Buf[0] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 ZO_Buf[0] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 ZO_Buf[0] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         ZO_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     ZO_Buf[0] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 ZO_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         ZO_Buf[0] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         ZO_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         ZO_Buf[0] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         ZO_Buf[0] = '0';
														  
										 				 break;	
											 }									
								         break;
								case 2:  ZO = atof(ZO_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(ZO_Buf,"%07.3f", ZO);
										 lcd_puts(ZO_Buf);
										 lcd_gotoxy(9,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 ZO_Buf[1] = '1';
														 
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 ZO_Buf[1] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 ZO_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         ZO_Buf[1] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     ZO_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 ZO_Buf[1] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         ZO_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         ZO_Buf[1] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         ZO_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         ZO_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  ZO = atof(ZO_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(ZO_Buf,"%07.3f", ZO);
										 lcd_puts(ZO_Buf);
										 lcd_gotoxy(10,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 ZO_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 ZO_Buf[2] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 ZO_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         ZO_Buf[2] = '4';
														 
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     ZO_Buf[2] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 ZO_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         ZO_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         ZO_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         ZO_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         ZO_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5: ZO = atof(ZO_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(ZO_Buf,"%07.3f", ZO);
										 lcd_puts(ZO_Buf);
										 lcd_gotoxy(12,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 ZO_Buf[4] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 ZO_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 ZO_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         ZO_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     ZO_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 ZO_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         ZO_Buf[4] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         ZO_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         ZO_Buf[4] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         ZO_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  ZO = atof(ZO_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(ZO_Buf,"%07.3f", ZO);
										 lcd_puts(ZO_Buf);
										 lcd_gotoxy(13,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 ZO_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 ZO_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 ZO_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         ZO_Buf[5] = '4';
														 
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     ZO_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 ZO_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         ZO_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         ZO_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         ZO_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         ZO_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  ZO = atof(ZO_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(ZO_Buf,"%07.3f", ZO);
										 lcd_puts(ZO_Buf);
										 lcd_gotoxy(14,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 ZO_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 ZO_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 ZO_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         ZO_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     ZO_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 ZO_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         ZO_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         ZO_Buf[6] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         ZO_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         ZO_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
						    
					}
					if(CalibrateDataPageCursor == 3)
					{
						    
						    switch (CalibrateDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  SN = atof(SN_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(SN_Buf,"%07.3f", SN);
										 lcd_puts(SN_Buf);
										 lcd_gotoxy(8,3);
				          				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 SN_Buf[0] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 SN_Buf[0] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 SN_Buf[0] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         SN_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     SN_Buf[0] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 SN_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         SN_Buf[0] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         SN_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         SN_Buf[0] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         SN_Buf[0] = '0';
														  
										 				 break;	
											 }									
								         break;
								case 2:  SN = atof(SN_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(SN_Buf,"%07.3f", SN);
										 lcd_puts(SN_Buf);
										 lcd_gotoxy(9,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 SN_Buf[1] = '1';
														 
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 SN_Buf[1] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 SN_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         SN_Buf[1] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     SN_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 SN_Buf[1] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         SN_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         SN_Buf[1] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         SN_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         SN_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  SN = atof(SN_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(SN_Buf,"%07.3f", SN);
										 lcd_puts(SN_Buf);
										 lcd_gotoxy(10,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 SN_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 SN_Buf[2] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 SN_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         SN_Buf[2] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     SN_Buf[2] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 SN_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         SN_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         SN_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         SN_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         SN_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5:  SN = atof(SN_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(SN_Buf,"%07.3f", SN);
										 lcd_puts(SN_Buf);
										 lcd_gotoxy(12,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 SN_Buf[4] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 SN_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 SN_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         SN_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     SN_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 SN_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         SN_Buf[4] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         SN_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         SN_Buf[4] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         SN_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  SN = atof(SN_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(SN_Buf,"%07.3f", SN);
										 lcd_puts(SN_Buf);
										 lcd_gotoxy(13,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 SN_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 SN_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 SN_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         SN_Buf[5] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     SN_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 SN_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         SN_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         SN_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         SN_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         SN_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  SN = atof(SN_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(SN_Buf,"%07.3f", SN);
										 lcd_puts(SN_Buf);
										 lcd_gotoxy(14,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 SN_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 SN_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 SN_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         SN_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     SN_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 SN_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         SN_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         SN_Buf[6] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         SN_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         SN_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
						    
					}
					if(CalibrateDataPageCursor == 4)
					{
						   lcd_gotoxy(8,1);
				           lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						    
						    switch (CalibrateDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  MA = atof(MA_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(MA_Buf,"%07.3f", MA);
										 lcd_puts(MA_Buf);
										 lcd_gotoxy(8,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MA_Buf[0] = '1';
														 
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MA_Buf[0] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MA_Buf[0] = '3';
														 
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MA_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MA_Buf[0] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MA_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MA_Buf[0] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MA_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MA_Buf[0] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MA_Buf[0] = '0';
														  
										 				 break;	
											 }									
								         break;
								case 2:  MA = atof(MA_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(MA_Buf,"%07.3f", MA);
										 lcd_puts(MA_Buf);
										 lcd_gotoxy(9,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MA_Buf[1] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MA_Buf[1] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MA_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MA_Buf[1] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MA_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MA_Buf[1] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MA_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MA_Buf[1] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MA_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MA_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  MA = atof(MA_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(MA_Buf,"%07.3f", MA);
										 lcd_puts(MA_Buf);
										 lcd_gotoxy(10,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MA_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MA_Buf[2] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MA_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MA_Buf[2] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MA_Buf[2] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MA_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MA_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MA_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MA_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MA_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5:  MA = atof(MA_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(MA_Buf,"%07.3f", MA);
										 lcd_puts(MA_Buf);
										 lcd_gotoxy(12,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MA_Buf[4] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MA_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MA_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MA_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MA_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MA_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MA_Buf[4] = '7';
														 
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MA_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MA_Buf[4] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MA_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  MA = atof(MA_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(MA_Buf,"%07.3f", MA);
										 lcd_puts(MA_Buf);
										 lcd_gotoxy(13,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MA_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MA_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MA_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MA_Buf[5] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MA_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MA_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MA_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MA_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MA_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MA_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  MA = atof(MA_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(MA_Buf,"%07.3f", MA);
										 lcd_puts(MA_Buf);
										 lcd_gotoxy(14,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 MA_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 MA_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 MA_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         MA_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     MA_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 MA_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         MA_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         MA_Buf[6] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         MA_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         MA_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
		 
						    
					}	
					 
			}
			while(KeyPressedStatus == 1)	
		  	{
				key = GetKeyPressed(); // wait for key release
		  	}
			eeprom_write_float(&Epromadress_MI,MI);
			eeprom_write_float(&Epromadress_ZO,ZO);
			eeprom_write_float(&Epromadress_SN,SN);
			eeprom_write_float(&Epromadress_MA,MA);
		
			lcd_command(LCD_DISP_ON);
			lcd_clrscr();		

}

void Process_Data_Page(void)
{
char W_Span_Buf[10];
char L_Offset_Buf[10];
char U_Load_Buf[10];
char O_Load_Buf[10];
char C_Factor_Buf[10];
char Speed_Buf[10];
 

unsigned char ProcessDataPageCursor = 1;
unsigned char ProcessDataLineCursor = 1;	 
unsigned char ProcessDataPage1_Print_Falg = 0,ProcessDataPage2_Print_Falg = 0;

			W_Span = eeprom_read_float(&Epromadress_W_Span);
			L_Offset = eeprom_read_float(&Epromadress_L_Offset);
			U_Load = eeprom_read_float(&Epromadress_U_Load);
			O_Load = eeprom_read_float(&Epromadress_O_Load);
			C_Factor = eeprom_read_float(&Epromadress_C_Factor);
			Speed = eeprom_read_float(&Epromadress_Speed);

 			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("PROCESS DATA....");
			lcd_gotoxy(0,1);
			lcd_puts("W Span");
			lcd_gotoxy(0,2);
			lcd_puts("L Ofst");
			lcd_gotoxy(0,3);
			lcd_puts("U Load");
			lcd_gotoxy(8,1);
			sprintf(W_Span_Buf,"%07.3f", W_Span);
			lcd_puts(W_Span_Buf);
			lcd_command(LCD_DISP_ON_CURSOR_BLINK);
			lcd_gotoxy(8,2);
			sprintf(L_Offset_Buf,"%07.3f", L_Offset);
			lcd_puts(L_Offset_Buf);
			lcd_gotoxy(8,3);
			sprintf(U_Load_Buf,"%07.3f", U_Load);
			lcd_puts(U_Load_Buf);
			
			
			while(key != '*')
			{
			    key = GetKeyPressed();
				sprintf(buf,"%d", ProcessDataPageCursor);
				USART0_Transmit_String(buf);
				sprintf(buf,"%c", key);
				USART0_Transmit_String(buf);
				USART0_Transmit_Char(13);
				    if(key == 'A')
					{
					    _delay_ms(300);
						ProcessDataPageCursor--;
					}
			 	    if(key == 'B')
					{
						_delay_ms(300); 
						ProcessDataPageCursor++;
					}
					if(key == 'C')
					{
					    _delay_ms(300);
						ProcessDataLineCursor--;
					}
			 	    if(key == 'D')
					{
						_delay_ms(300); 
						ProcessDataLineCursor++;
					}
					if(	ProcessDataPageCursor > 6)
					{
						
						ProcessDataPageCursor = 6;
					}
					if(	ProcessDataPageCursor < 1)
					{
							ProcessDataPageCursor = 1;
					}
					if(	ProcessDataLineCursor > 7)
					{
						
						ProcessDataLineCursor = 7;
					}
					if(	ProcessDataLineCursor < 1)
					{
							ProcessDataLineCursor = 1;
					}

					if((ProcessDataPageCursor <= 3)&&(ProcessDataPage1_Print_Falg == 0))
					{
							lcd_clrscr();
							lcd_gotoxy(0,0);
							lcd_puts("PROCESS DATA....");
							lcd_gotoxy(0,1);
							lcd_puts("W Span");
							lcd_gotoxy(0,2);
							lcd_puts("L Ofst");
							lcd_gotoxy(0,3);
							lcd_puts("U Load");
							lcd_gotoxy(8,1);
							sprintf(W_Span_Buf,"%07.3f", W_Span);
							lcd_puts(W_Span_Buf);
							lcd_gotoxy(8,2);
							sprintf(L_Offset_Buf,"%07.3f", L_Offset);
							lcd_puts(L_Offset_Buf);
							lcd_gotoxy(8,3);
							sprintf(U_Load_Buf,"%07.3f", U_Load);
							lcd_puts(U_Load_Buf);
							ProcessDataPage1_Print_Falg = 1;
							ProcessDataPage2_Print_Falg = 0;
						 
					}
					//ProcessDataPage2_Print_Falg = 0;
					if((ProcessDataPageCursor >= 4)&&(ProcessDataPage2_Print_Falg == 0))
					{
						USART0_Transmit_String("page 2");
							lcd_clrscr();
							lcd_gotoxy(0,0);
							lcd_puts("PROCESS DATA....");
							lcd_gotoxy(0,1);
							lcd_puts("O Load");
							lcd_gotoxy(0,2);
							lcd_puts("C Fact");
							lcd_gotoxy(0,3);
							lcd_puts("Speed");
							lcd_gotoxy(8,1);
							sprintf(O_Load_Buf,"%07.3f", O_Load);
							lcd_puts(O_Load_Buf);
							lcd_gotoxy(8,2);
							sprintf(C_Factor_Buf,"%07.3f", C_Factor);
							lcd_puts(C_Factor_Buf);
							lcd_gotoxy(8,3);
							sprintf(Speed_Buf,"%07.3f", Speed);
							lcd_puts(Speed_Buf);
							ProcessDataPage2_Print_Falg = 1;
							ProcessDataPage1_Print_Falg = 0;
						 
					}	
					 

					if(ProcessDataPageCursor == 1)
					{
						   //lcd_gotoxy(8,1);
				           //lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						   //USART0_Transmit_String(W_Span_Buf);
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  W_Span = atof(W_Span_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(W_Span_Buf,"%07.3f", W_Span);
										 lcd_puts(W_Span_Buf);
										 lcd_gotoxy(8,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[0] = '1';
														 
														 
								        				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[0] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[0] = '3';
														 
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[0] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '9';
														 
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '0';
														  
										 				 break;	
											 }	
																		
								         break;
								case 2:  W_Span = atof(W_Span_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(W_Span_Buf,"%07.3f", W_Span);
										 lcd_puts(W_Span_Buf); 
										 lcd_gotoxy(9,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[1] = '1';
														 W_Span = atof(W_Span_Buf);	 
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[1] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[1] = '6';
														 
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '8';
														 
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  W_Span = atof(W_Span_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(W_Span_Buf,"%07.3f", W_Span);
										 lcd_puts(W_Span_Buf);
										 lcd_gotoxy(10,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[2] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[2] = '5';
														 
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5:  W_Span = atof(W_Span_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(W_Span_Buf,"%07.3f", W_Span);
										 lcd_puts(W_Span_Buf);
										 lcd_gotoxy(12,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[4] = '1';
														 
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '9';
														 
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  W_Span = atof(W_Span_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(W_Span_Buf,"%07.3f", W_Span);
										 lcd_puts(W_Span_Buf);
										 lcd_gotoxy(13,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  W_Span = atof(W_Span_Buf);	 
										 lcd_gotoxy(8,1);
										 sprintf(W_Span_Buf,"%07.3f", W_Span);
										 lcd_puts(W_Span_Buf);
										 lcd_gotoxy(14,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
		 
						    
					}
					if(ProcessDataPageCursor == 2)
					{
							//lcd_gotoxy(8,2);
				          	//lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						   // USART0_Transmit_String(L_Offset_Buf);
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  L_Offset = atof(L_Offset_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
										 lcd_puts(L_Offset_Buf);
										 lcd_gotoxy(8,2);
				          				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[0] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[0] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[0] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[0] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[0] = '0';
														  
										 				 break;	
											 }									
								         break;
								case 2:  L_Offset = atof(L_Offset_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
										 lcd_puts(L_Offset_Buf);
										 lcd_gotoxy(9,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[1] = '1';
														 
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[1] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[1] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  L_Offset = atof(L_Offset_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
										 lcd_puts(L_Offset_Buf);
										 lcd_gotoxy(10,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[2] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '4';
														 
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[2] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5: L_Offset = atof(L_Offset_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
										 lcd_puts(L_Offset_Buf);
										 lcd_gotoxy(12,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[4] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  L_Offset = atof(L_Offset_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
										 lcd_puts(L_Offset_Buf);
										 lcd_gotoxy(13,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '4';
														 
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  L_Offset = atof(L_Offset_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(L_Offset_Buf,"%07.3f", L_Offset);
										 lcd_puts(L_Offset_Buf);
										 lcd_gotoxy(14,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     L_Offset_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 L_Offset_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         L_Offset_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
						    
					}
					if(ProcessDataPageCursor == 3)
					{
						    
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  U_Load = atof(U_Load_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
										 lcd_puts(U_Load_Buf);
										 lcd_gotoxy(8,3);
				          				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[0] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[0] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[0] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[0] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '0';
														  
										 				 break;	
											 }									
								         break;
								case 2:  U_Load = atof(U_Load_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
										 lcd_puts(U_Load_Buf);
										 lcd_gotoxy(9,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[1] = '1';
														 
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[1] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[1] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  U_Load = atof(U_Load_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
										 lcd_puts(U_Load_Buf);
										 lcd_gotoxy(10,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[2] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[2] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5:  U_Load = atof(U_Load_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
										 lcd_puts(U_Load_Buf);
										 lcd_gotoxy(12,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[4] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  U_Load = atof(U_Load_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
										 lcd_puts(U_Load_Buf);
										 lcd_gotoxy(13,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  U_Load = atof(U_Load_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
										 lcd_puts(U_Load_Buf);
										 lcd_gotoxy(14,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
						    
					}
					if(ProcessDataPageCursor == 4)
					{
						   lcd_gotoxy(8,1);
				           lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						    
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  O_Load = atof(O_Load_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
										 lcd_puts(O_Load_Buf);
										 lcd_gotoxy(8,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[0] = '1';
														 
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[0] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[0] = '3';
														 
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[0] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '0';
														  
										 				 break;	
											 }									
								         break;
								case 2:  O_Load = atof(O_Load_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
										 lcd_puts(O_Load_Buf);
										 lcd_gotoxy(9,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[1] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[1] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[1] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  O_Load = atof(O_Load_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
										 lcd_puts(O_Load_Buf);
										 lcd_gotoxy(10,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[2] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[2] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5:  O_Load = atof(O_Load_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
										 lcd_puts(O_Load_Buf);
										 lcd_gotoxy(12,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[4] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '7';
														 
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  O_Load = atof(O_Load_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
										 lcd_puts(O_Load_Buf);
										 lcd_gotoxy(13,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  O_Load = atof(O_Load_Buf);	 
										 lcd_gotoxy(8,1);
								  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
										 lcd_puts(O_Load_Buf);
										 lcd_gotoxy(14,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
		 
						    
					}	
					if(ProcessDataPageCursor == 5)
					{
						    
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  C_Factor = atof(C_Factor_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
										 lcd_puts(C_Factor_Buf);
										 lcd_gotoxy(8,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[0] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[0] = '2';
														 
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[0] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[0] = '5';
														 
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '7';
														 
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '0';
														  
										 				 break;	
											 }									
								         break;
								case 2:  C_Factor = atof(C_Factor_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
										 lcd_puts(C_Factor_Buf);
										 lcd_gotoxy(9,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[1] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[1] = '2';
														 
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '4';
														 
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[1] = '6';
														 
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  C_Factor = atof(C_Factor_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
										 lcd_puts(C_Factor_Buf);
										 lcd_gotoxy(10,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[2] = '2';
														 
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[2] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5:  C_Factor = atof(C_Factor_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
										 lcd_puts(C_Factor_Buf);
										 lcd_gotoxy(12,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[4] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  C_Factor = atof(C_Factor_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
										 lcd_puts(C_Factor_Buf);
										 lcd_gotoxy(13,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  C_Factor = atof(C_Factor_Buf);	 
										 lcd_gotoxy(8,2);
								  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
										 lcd_puts(C_Factor_Buf);
										 lcd_gotoxy(14,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '8';
														 
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
		 
						    
					}
					if(ProcessDataPageCursor == 6)
					{
						    
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  Speed = atof(Speed_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(Speed_Buf,"%07.3f", Speed);
										 lcd_puts(Speed_Buf);
										 lcd_gotoxy(8,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 Speed_Buf[0] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 Speed_Buf[0] = '2';
														 
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 Speed_Buf[0] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         Speed_Buf[0] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     Speed_Buf[0] = '5';
														 
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 Speed_Buf[0] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         Speed_Buf[0] = '7';
														 
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         Speed_Buf[0] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         Speed_Buf[0] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         Speed_Buf[0] = '0';
														  
										 				 break;	
											 }									
								         break;
								case 2:  Speed = atof(Speed_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(Speed_Buf,"%07.3f", Speed);
										 lcd_puts(Speed_Buf);
										 lcd_gotoxy(9,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 Speed_Buf[1] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 Speed_Buf[1] = '2';
														 
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 Speed_Buf[1] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         Speed_Buf[1] = '4';
														 
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     Speed_Buf[1] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 Speed_Buf[1] = '6';
														 
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         Speed_Buf[1] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         Speed_Buf[1] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         Speed_Buf[1] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         Speed_Buf[1] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 3:  Speed = atof(Speed_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(Speed_Buf,"%07.3f", Speed);
										 lcd_puts(Speed_Buf);
										 lcd_gotoxy(10,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 Speed_Buf[2] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 Speed_Buf[2] = '2';
														 
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 Speed_Buf[2] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         Speed_Buf[2] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     Speed_Buf[2] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 Speed_Buf[2] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         Speed_Buf[2] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         Speed_Buf[2] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         Speed_Buf[2] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         Speed_Buf[2] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5:  Speed = atof(Speed_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(Speed_Buf,"%07.3f", Speed);
										 lcd_puts(Speed_Buf);
										 lcd_gotoxy(12,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 Speed_Buf[4] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 Speed_Buf[4] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 Speed_Buf[4] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         Speed_Buf[4] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     Speed_Buf[4] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 Speed_Buf[4] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         Speed_Buf[4] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         Speed_Buf[4] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         Speed_Buf[4] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         Speed_Buf[4] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 6:  Speed = atof(Speed_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(Speed_Buf,"%07.3f", Speed);
										 lcd_puts(Speed_Buf);
										 lcd_gotoxy(13,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 Speed_Buf[5] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 Speed_Buf[5] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 Speed_Buf[5] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         Speed_Buf[5] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     Speed_Buf[5] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 Speed_Buf[5] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         Speed_Buf[5] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         Speed_Buf[5] = '8';
														  
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         Speed_Buf[5] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         Speed_Buf[5] = '0';
														  
										 				 break;	
										  }	
								         break;
								case 7:  Speed = atof(Speed_Buf);	 
										 lcd_gotoxy(8,3);
								  		 sprintf(Speed_Buf,"%07.3f", Speed);
										 lcd_puts(Speed_Buf);
										 lcd_gotoxy(14,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 Speed_Buf[6] = '1';
														  
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 Speed_Buf[6] = '2';
														  
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 Speed_Buf[6] = '3';
														  
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         Speed_Buf[6] = '4';
														  
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     Speed_Buf[6] = '5';
														  
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 Speed_Buf[6] = '6';
														  
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         Speed_Buf[6] = '7';
														  
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         Speed_Buf[6] = '8';
														 
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         Speed_Buf[6] = '9';
														  
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         Speed_Buf[6] = '0';
														  
										 				 break;	
										  }	
								         break;
					        } 
		 
						    
					}
			}
			while(KeyPressedStatus == 1)	
		  	{
				key = GetKeyPressed(); // wait for key release
		  	}
			eeprom_write_float(&Epromadress_W_Span,W_Span);
			eeprom_write_float(&Epromadress_L_Offset,L_Offset);
			eeprom_write_float(&Epromadress_U_Load,U_Load);
			eeprom_write_float(&Epromadress_O_Load,O_Load);
			eeprom_write_float(&Epromadress_C_Factor,C_Factor);
			eeprom_write_float(&Epromadress_Speed,Speed);
			lcd_command(LCD_DISP_ON);
			lcd_clrscr();		

}


int GetKeyPressed()
{

 KeyPressedStatus = 0;
 //		      76543210	
	DDRC  = 0b10000000; 
	_delay_us(50);
 	switch (PINC<<4)  // Main Menu Switch statement
	    {
			case 224: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('A');
						DDRC  = 0b10000000; 
						_delay_us(50);
					 	switch (PINC<<4)  // Main Menu Switch statement
						    {
							 
								         break;
								case 208: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('3');
										  }
											return('3');
								         break;
								case 176: while((PINC<<4)!= 240)
										  {
										  //	USART0_Transmit_Char('2');
										  }
											return('2');
								         break;
								case 112: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('1');
										  }
											return('1');
								         break;
			 


					        } 
		 
							_delay_us(1000);
					//		              76543210	
								DDRC  = 0b01000000; 
								_delay_us(50);
					 		switch (PINC<<4)  // Main Menu Switch statement
						    {
								case 224: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('B');
										  }
											return('P');
								         break;					 
								case 208: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('6');
										  }
											return('6');
								         break;					  
								case 176: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('5');
										  }
											return('5');
								         break;
								case 112: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('4');
										  }
											return('4');
								         break;
		 


					        }
							_delay_us(1000);
					//		              76543210	
								DDRC  = 0b00100000; 
								_delay_us(50);
					 		switch (PINC<<4)  // Main Menu Switch statement
						    {
								case 224: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('C');
										  }
										    return('C');	
								         break;
								case 208: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('9');
										  }
											return('9');
								         break;
								case 176: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('8');
										  }
											return('8');
								         break;
								case 112:while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('7');
										  }
											return('7');
								         break;
			 


					        }
	 
					//		              76543210	
							DDRC  = 0b00010000; 
							_delay_us(50);
					 		switch (PINC<<4)  // Main Menu Switch statement
						    {
								case 224: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('D');
										  }
										    return('D');	
								         break;
								case 208: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('#');
										  }
											return('#');
								         break;
								case 176: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('0');
										  }
											return('0');
								         break;
								case 112: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('*');
										  }
											return('*');
								         break;
			 


					       }
					  }
						KeyPressedStatus = 1;
					    return('A');	
			         break;
			case 208: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('3');
					  }
					  KeyPressedStatus = 1;
						return('3');
			         break;
			case 176: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('2');
					  }
					  KeyPressedStatus = 1;
						return('2');
			         break;
			case 112: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('1');
					  }
					  KeyPressedStatus = 1;
						return('1');
			         break;
			 


        } 
		 
		_delay_us(1000);
//		              76543210	
			DDRC  = 0b01000000; 
			_delay_us(50);
 switch (PINC<<4)  // Main Menu Switch statement
	    {
			case 224: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('B');
						DDRC  = 0b10000000; 
						_delay_us(50);
					 	switch (PINC<<4)  // Main Menu Switch statement
						    {
								case 224: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('A');
										  }
										    return('P');	
								         break;
								case 208: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('3');
										  }
											return('3');
								         break;
								case 176: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('2');
										  }
											return('2');
								         break;
								case 112: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('1');
										  }
											return('1');
								         break;
			 


					        } 
		 
							_delay_us(1000);
					//		              76543210	
								DDRC  = 0b01000000; 
								_delay_us(50);
					 	switch (PINC<<4)  // Main Menu Switch statement
						    {
								 
								         break;					 
								case 208: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('6');
										  }
											return('6');
								         break;					  
								case 176: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('5');
										  }
											return('5');
								         break;
								case 112: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('4');
										  }
											return('4');
								         break;
		 


					        }
							_delay_us(1000);
					//		              76543210	
								DDRC  = 0b00100000; 
								_delay_us(50);
					 	switch (PINC<<4)  // Main Menu Switch statement
						    {
								case 224: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('C');
										  }
										    return('C');	
								         break;
								case 208: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('9');
										  }
											return('9');
								         break;
								case 176: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('8');
										  }
											return('8');
								         break;
								case 112:while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('7');
										  }
											return('7');
								         break;
			 


					        }
	 
					//		              76543210	
								DDRC  = 0b00010000; 
								_delay_us(50);
					 	switch (PINC<<4)  // Main Menu Switch statement
						    {
								case 224: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('D');
										  }
										    return('D');	
								         break;
								case 208: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('#');
										  }
											return('#');
								         break;
								case 176: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('0');
										  }
											return('0');
								         break;
								case 112: while((PINC<<4)!= 240)
										  {
										  	//USART0_Transmit_Char('*');
										  }
											return('*');
								         break;
			 


					       }
					  }
					  KeyPressedStatus = 1;
						return('B');
			         break;					 
			case 208: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('6');
					  }
					  KeyPressedStatus = 1;
						return('6');
			         break;					  
			case 176: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('5');
					  }
					  KeyPressedStatus = 1;
						return('5');
			         break;
			case 112: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('4');
					  }
					  KeyPressedStatus = 1;
						return('4');
			         break;
		 


        }
		_delay_us(1000);
//		              76543210	
			DDRC  = 0b00100000; 
			_delay_us(50);
 switch (PINC<<4)  // Main Menu Switch statement
	    {
			case 224: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('C');
					  }
					  KeyPressedStatus = 1;
					    return('C');	
			         break;
			case 208: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('9');
					  }
					  KeyPressedStatus = 1;
						return('9');
			         break;
			case 176: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('8');
					  }
					  KeyPressedStatus = 1;
						return('8');
			         break;
			case 112:while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('7');
					  }
					  KeyPressedStatus = 1;
						return('7');
			         break;
			 


        }
	 
//		              76543210	
			DDRC  = 0b00010000; 
			_delay_us(50);
 switch (PINC<<4)  // Main Menu Switch statement
	    {
			case 224: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('D');
					  }
					  KeyPressedStatus = 1;
					    return('D');	
			         break;
			case 208: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('#');
					  }
					  KeyPressedStatus = 1;
						return('#');
			         break;
			case 176: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('0');
					  }
					  KeyPressedStatus = 1;
						return('0');
			         break;
			case 112: while((PINC<<4)!= 240)
					  {
					  	//USART0_Transmit_Char('*');
					  }
					  KeyPressedStatus = 1;
						return('*');
			         break;
			 


       }
//	sprintf(buf,"%d", (PINC<<4));
//	USART0_Transmit_String(buf);
//	USART0_Transmit_Char(13);  
}


/*
int GetKeyPressed()
{
 //		      76543210	
	DDRC  = 0b10000000; 
	_delay_us(50);
 switch (PINC<<4)  // Main Menu Switch statement
	    {
			case 224: //USART0_Transmit_Char('1');
					    return('A');	
			         break;
			case 208: //USART0_Transmit_Char('4');
						return('3');
			         break;
			case 176: //USART0_Transmit_Char('7');
						return('2');
			         break;
			case 112: //USART0_Transmit_Char('*');
						return('1');
			         break;
			 


        } 
		 
		_delay_us(1000);
//		              76543210	
			DDRC  = 0b01000000; 
			_delay_us(50);
 switch (PINC<<4)  // Main Menu Switch statement
	    {
			case 224: //USART0_Transmit_Char('2');
						return('B');
			         break;					 
			case 208: //USART0_Transmit_Char('5');
						return('6');
			         break;					  
			case 176: //USART0_Transmit_Char('8');
						return('5');
			         break;
			case 112: //USART0_Transmit_Char('0');
						return('4');
			         break;
		 


        }
		_delay_us(1000);
//		              76543210	
			DDRC  = 0b00100000; 
			_delay_us(50);
 switch (PINC<<4)  // Main Menu Switch statement
	    {
			case 224: //USART0_Transmit_Char('3');
					    return('C');	
			         break;
			case 208: //USART0_Transmit_Char('6');
						return('9');
			         break;
			case 176: //USART0_Transmit_Char('9');
						return('8');
			         break;
			case 112: //USART0_Transmit_Char('#');
						return('7');
			         break;
			 


        }
	 
//		              76543210	
			DDRC  = 0b00010000; 
			_delay_us(50);
 switch (PINC<<4)  // Main Menu Switch statement
	    {
			case 224: //USART0_Transmit_Char('A');
					    return('D');	
			         break;
			case 208: //USART0_Transmit_Char('B');
						return('#');
			         break;
			case 176: //USART0_Transmit_Char('C');
						return('0');
			         break;
			case 112: //USART0_Transmit_Char('D');
						return('*');
			         break;
			 


       }
	sprintf(buf,"%d", (PINC<<4));
	USART0_Transmit_String(buf);
	USART0_Transmit_Char(13);    
}

*/

void Home(void)
{
 
		_delay_ms(10);
        lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("BELT WEIGHING SYSTEM");
		lcd_gotoxy(0,1);
		lcd_puts(" ESSAE DIGITRONICS");
		lcd_gotoxy(0,2);
		lcd_puts("             V1.00 ");
		lcd_gotoxy(0,3);
		lcd_puts("   ....booting....");
	//	_delay_ms(2500);
}
 
