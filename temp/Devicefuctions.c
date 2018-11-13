
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



void Process_Data_Page(void)
{



unsigned char ProcessDataPageCursor = 1;
unsigned char ProcessDataLineCursor = 1;	 
unsigned char ProcessDataPage1_Print_Falg = 0,ProcessDataPage2_Print_Falg = 0;


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
					if(	ProcessDataPageCursor > 5)
					{
						
						ProcessDataPageCursor = 5;
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
							lcd_gotoxy(8,1);
							sprintf(O_Load_Buf,"%07.3f", O_Load);
							lcd_puts(O_Load_Buf);
							lcd_gotoxy(8,2);
							sprintf(C_Factor_Buf,"%07.3f", C_Factor);
							lcd_puts(C_Factor_Buf);
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
								case 1:  lcd_gotoxy(8,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[0] = '1';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[0] = '2';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[0] = '3';
														 W_Span = atof(W_Span_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '4';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[0] = '5';
														 W_Span = atof(W_Span_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[0] = '6';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '7';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '8';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '9';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[0] = '0';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
											 }									
								         break;
								case 2:  lcd_gotoxy(9,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[1] = '1';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[1] = '2';
														 W_Span = atof(W_Span_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[1] = '3';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '4';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[1] = '5';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[1] = '6';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '7';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '8';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '9';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[1] = '0';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
										  }	
								         break;
								case 3:  lcd_gotoxy(10,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[2] = '1';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[2] = '2';
														 W_Span = atof(W_Span_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[2] = '3';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '4';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[2] = '5';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[2] = '6';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '7';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '8';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '9';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[2] = '0';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
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
														 W_Span_Buf[4] = '1';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[4] = '2';
														 W_Span = atof(W_Span_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[4] = '3';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '4';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[4] = '5';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[4] = '6';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '7';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '8';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '9';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[4] = '0';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
										  }	
								         break;
								case 6: lcd_gotoxy(13,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[5] = '1';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[5] = '2';
														 W_Span = atof(W_Span_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[5] = '3';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '4';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[5] = '5';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[5] = '6';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '7';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '8';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '9';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[5] = '0';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
										  }	
								         break;
								case 7: lcd_gotoxy(14,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[6] = '1';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[6] = '2';
														 W_Span = atof(W_Span_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[6] = '3';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '4';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     W_Span_Buf[6] = '5';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 W_Span_Buf[6] = '6';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '7';
														 W_Span = atof(W_Span_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '8';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '9';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         W_Span_Buf[6] = '0';
														 W_Span = atof(W_Span_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(W_Span_Buf,"%07.3f", W_Span);
														 lcd_puts(W_Span_Buf);
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
								case 2:  lcd_gotoxy(9,2);
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
								case 3:  lcd_gotoxy(10,2);
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
								case 4:  lcd_gotoxy(11,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5: lcd_gotoxy(12,2);
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
														 lcd_gotoxy(8,2);
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
								case 6: lcd_gotoxy(13,2);
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
														 lcd_gotoxy(8,2);	 
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
								case 7: lcd_gotoxy(14,2);
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
						    
					}
					if(ProcessDataPageCursor == 3)
					{
						   lcd_gotoxy(8,3);
				           lcd_command(LCD_DISP_ON_CURSOR_BLINK);
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  lcd_gotoxy(8,3);
				          				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[0] = '1';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[0] = '2';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[0] = '3';
														 U_Load = atof(U_Load_Buf);	
														 lcd_gotoxy(8,3); 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '4';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[0] = '5';
														 U_Load = atof(U_Load_Buf);	
														 lcd_gotoxy(8,3); 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[0] = '6';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '7';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '8';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '9';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[0] = '0';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
											 }									
								         break;
								case 2:  lcd_gotoxy(9,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[1] = '1';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[1] = '2';
														 U_Load = atof(U_Load_Buf);	
														 lcd_gotoxy(8,3); 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[1] = '3';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '4';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[1] = '5';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[1] = '6';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '7';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '8';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '9';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[1] = '0';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
										  }	
								         break;
								case 3:  lcd_gotoxy(10,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[2] = '1';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[2] = '2';
														 U_Load = atof(U_Load_Buf);	
														 lcd_gotoxy(8,3); 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[2] = '3';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '4';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[2] = '5';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[2] = '6';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '7';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '8';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '9';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[2] = '0';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5: lcd_gotoxy(12,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[4] = '1';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[4] = '2';
														 U_Load = atof(U_Load_Buf);	
														 lcd_gotoxy(8,3); 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[4] = '3';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '4';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[4] = '5';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[4] = '6';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '7';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '8';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '9';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[4] = '0';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
										  }	
								         break;
								case 6: lcd_gotoxy(13,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[5] = '1';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[5] = '2';
														 U_Load = atof(U_Load_Buf);	
														 lcd_gotoxy(8,3); 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[5] = '3';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '4';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[5] = '5';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[5] = '6';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '7';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '8';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '9';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[5] = '0';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
										  }	
								         break;
								case 7: lcd_gotoxy(14,3);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[6] = '1';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[6] = '2';
														 U_Load = atof(U_Load_Buf);	
														 lcd_gotoxy(8,3); 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[6] = '3';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '4';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     U_Load_Buf[6] = '5';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 U_Load_Buf[6] = '6';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '7';
														 U_Load = atof(U_Load_Buf);
														 lcd_gotoxy(8,3);	 
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '8';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '9';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         U_Load_Buf[6] = '0';
														 U_Load = atof(U_Load_Buf);	 
														 lcd_gotoxy(8,3);
												  		 sprintf(U_Load_Buf,"%07.3f", U_Load);
														 lcd_puts(U_Load_Buf);
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
								case 1:  lcd_gotoxy(8,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[0] = '1';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[0] = '2';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[0] = '3';
														 O_Load = atof(O_Load_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '4';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[0] = '5';
														 O_Load = atof(O_Load_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[0] = '6';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '7';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '8';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '9';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[0] = '0';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
											 }									
								         break;
								case 2:  lcd_gotoxy(9,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[1] = '1';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[1] = '2';
														 O_Load = atof(O_Load_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[1] = '3';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '4';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[1] = '5';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[1] = '6';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '7';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '8';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '9';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[1] = '0';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
										  }	
								         break;
								case 3:  lcd_gotoxy(10,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[2] = '1';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[2] = '2';
														 O_Load = atof(O_Load_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[2] = '3';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '4';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[2] = '5';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[2] = '6';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '7';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '8';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '9';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[2] = '0';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
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
														 O_Load_Buf[4] = '1';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[4] = '2';
														 O_Load = atof(O_Load_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[4] = '3';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '4';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[4] = '5';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[4] = '6';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '7';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '8';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '9';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[4] = '0';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
										  }	
								         break;
								case 6: lcd_gotoxy(13,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[5] = '1';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[5] = '2';
														 O_Load = atof(O_Load_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[5] = '3';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '4';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[5] = '5';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[5] = '6';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '7';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '8';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '9';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[5] = '0';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
										  }	
								         break;
								case 7: lcd_gotoxy(14,1);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[6] = '1';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[6] = '2';
														 O_Load = atof(O_Load_Buf);	
														 lcd_gotoxy(8,1); 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[6] = '3';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '4';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     O_Load_Buf[6] = '5';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 O_Load_Buf[6] = '6';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '7';
														 O_Load = atof(O_Load_Buf);
														 lcd_gotoxy(8,1);	 
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '8';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '9';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         O_Load_Buf[6] = '0';
														 O_Load = atof(O_Load_Buf);	 
														 lcd_gotoxy(8,1);
												  		 sprintf(O_Load_Buf,"%07.3f", O_Load);
														 lcd_puts(O_Load_Buf);
										 				 break;	
										  }	
								         break;
					        } 
		 
						    
					}	
					if(ProcessDataPageCursor == 5)
					{
						    
						    switch (ProcessDataLineCursor)  // Main Menu Switch statement
						    {
								case 1:  lcd_gotoxy(8,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										  switch (key)  // Main Menu Switch statement
										    {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[0] = '1';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[0] = '2';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[0] = '3';
														 C_Factor = atof(C_Factor_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '4';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[0] = '5';
														 C_Factor = atof(C_Factor_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[0] = '6';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '7';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '8';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '9';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[0] = '0';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
											 }									
								         break;
								case 2:  lcd_gotoxy(9,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[1] = '1';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[1] = '2';
														 C_Factor = atof(C_Factor_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[1] = '3';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '4';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[1] = '5';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[1] = '6';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '7';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '8';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '9';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[1] = '0';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
										  }	
								         break;
								case 3:  lcd_gotoxy(10,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[2] = '1';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[2] = '2';
														 C_Factor = atof(C_Factor_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[2] = '3';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '4';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[2] = '5';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[2] = '6';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '7';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '8';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '9';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[2] = '0';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
										  }	
								         break;
								case 4:  lcd_gotoxy(11,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
								         break;
								case 5: lcd_gotoxy(12,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[4] = '1';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[4] = '2';
														 C_Factor = atof(C_Factor_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[4] = '3';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '4';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[4] = '5';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[4] = '6';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '7';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '8';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '9';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[4] = '0';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
										  }	
								         break;
								case 6: lcd_gotoxy(13,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[5] = '1';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[5] = '2';
														 C_Factor = atof(C_Factor_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[5] = '3';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '4';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[5] = '5';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[5] = '6';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '7';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '8';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '9';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[5] = '0';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
										  }	
								         break;
								case 7: lcd_gotoxy(14,2);
				           				 lcd_command(LCD_DISP_ON_CURSOR_BLINK);
										 switch (key)  // Main Menu Switch statement
										 {
											 
												case '1':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[6] = '1';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '2':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[6] = '2';
														 C_Factor = atof(C_Factor_Buf);	
														 lcd_gotoxy(8,2); 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '3':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[6] = '3';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '4':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '4';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '5':lcd_command(LCD_DISP_ON);
													     C_Factor_Buf[6] = '5';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '6':lcd_command(LCD_DISP_ON);
														 C_Factor_Buf[6] = '6';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '7':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '7';
														 C_Factor = atof(C_Factor_Buf);
														 lcd_gotoxy(8,2);	 
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '8':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '8';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '9':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '9';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
												case '0':lcd_command(LCD_DISP_ON);
												         C_Factor_Buf[6] = '0';
														 C_Factor = atof(C_Factor_Buf);	 
														 lcd_gotoxy(8,2);
												  		 sprintf(C_Factor_Buf,"%07.3f", C_Factor);
														 lcd_puts(C_Factor_Buf);
										 				 break;	
										  }	
								         break;
					        } 
		 
						    
					}
			}
			lcd_command(LCD_DISP_ON);
			lcd_clrscr();		

}
void PageOne(void)
{

int length,templength;


	    key = GetKeyPressed();
		sprintf(buf,"%c", key);
		USART0_Transmit_String(buf);
		HX711_init(128);
			 
		HX711_set_scale(1.f/*242300.88*/);
		HX711_set_gain(128);
    	//HX711_tare(10);
		Count_ChannelA = HX711_read();
	    
		weight = ((float)Count_ChannelA -8388656.0)/67.0; 
		sprintf(buf,"%lu", Count_ChannelA);
		USART0_Transmit_String(buf);
		sprintf(buf,"%.3f", weight);
		USART0_Transmit_String(buf);
		USART0_Transmit_Char(13);
		lcd_gotoxy(0,0);
 		lcd_puts("Weight");
		lcd_gotoxy(18,0);
 		lcd_puts("Kg");
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
		lcd_gotoxy(7,0);
		sprintf(buf,"%.3f", weight);
	 	 
 		
		length = strlen(buf);
		if(length < templength)
		{
			//lcd_clrscr();
			sprintf(buf,"%-8s", buf);
		 
		}
		lcd_puts(buf);
		templength =  length;
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
				

			}
		}
}


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
	   
}




void Home(void)
{
 
		_delay_ms(10);
        lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("*******TG TECH******");
		lcd_gotoxy(0,1);
		lcd_puts("   WEIGHT MACHINE");

}
 
