//**************************************************************
//    ******** FUNCTIONS FOR CONTROLLER MODULES  *******
//**************************************************************
//Controller:	ATmega128 (Crystal: 16Mhz)
//Compiler:		winAVR (AVR-GCC)
//Author:		STM VeeraBahu Chennai (India)
 
//********************************************************

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
//#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "ControllerModule.h"
#include "Devicefunctions.h" 
#include "HX711.h"
//************************************************************
// *************  FUNCTION DECLARATION PART ******************
//************************************************************ 

//****************************************  PORT INITIALISATION    ***********************************
//
//*****************************************************************************************************


void Port_Init()
{	
	//*****  PORT A  *******
	//		  76543210	
	DDRA  = 0b11111111;
	//		  76543210
	//PORTA = 0b00000000;

	//*****  PORT B  *******
	//		  76543210	
	DDRB  = 0b00000000;
	//		  76543210
	PORTB = 0b00000000;

	//*****  PORT C  *******

	//		  76543210	
	DDRC  = 0b00000000;
	//		  76543210
	//PORTC = 0b00000000;

	//*****  PORT D  *******
	//		  76543210	
	DDRD  = 0b11111000;
	//		  76543210
	//PORTD = 0b00000000;

	//*****  PORT E  *******
	//		  76543210	
	DDRE  = 0b11111111;
	//		  76543210
	//PORTE = 0b00000000;

	//*****  PORT F  *******
	//		  76543210	
	DDRF  = 0b00000000;
	//		  76543210
	//PORTF = 0b00000000;

	//*****  PORT G  *******
	//		  43210	
	DDRG  = 0b11111;
	//		  43210
	//PORTG = 0b00000;

}


//*******************************************************************************************
/*======================================= USART 0 ===========================================*/
//*******************************************************************************************

//---------- USART0 INITIALIZATION --------
void USART0_INIT()
{   
	UBRR0H = (BAUD0_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
   	UBRR0L = BAUD0_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

   	UCSR0B |= (1 << RXEN0) | (1 << TXEN0)|(1<<RXCIE0);   // Turn on the transmission and reception circuitry and RX Intrupt enabled.
   	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes
}

//---------- USART0 TRANSMITING CHARACTER DATA --------
void USART0_Transmit_Char(uint8_t CHARDATA)
{
	while ((UCSR0A & (1 << UDRE0)) == 0) {};
	UDR0 = CHARDATA;
	/*//naga code
	while( !(UCSR0A&(1<<UDRE0)) );
	UDR0 = u8Data;
	*/
}

void ISR_USART0_Transmit_Char(uint8_t CHARDATA)
{
	while ((UCSR0A & (1 << UDRE0)) == 0) {};
	UDR0 = CHARDATA;
	/*//naga code
	while( !(UCSR0A&(1<<UDRE0)) );
	UDR0 = u8Data;
	*/
}
//---------- USART0 RECIEVING CHARECTER DATA --------
unsigned char USART0_Recieve_Char()
{
int recievebreakcounter;
   //Wait untill a data is available
   recievebreakcounter = 0;	
   while(!(UCSR0A & (1<<RXC0)))
   {
   		//ISR_USART0_Transmit_Char('A');
    	recievebreakcounter++;
		if(recievebreakcounter>2000)
		{
		 break;
		}
   }
   while(!(UCSR0A & (1<<RXC0)))
   {
   }


   return UDR0;
}
unsigned char USART0_TimeFRee_Recieve_Char()
{
   //Wait untill a data is available
   
   while(!(UCSR0A & (1<<RXC0)))
   {
   }


   return UDR0;
}


//---------- USART0 INTERRUPT SUBROUTINE --------
/*
ISR(USART0_RX_vect)
{
  //cli();
  RXC0_INT_DISABLE
  int index;
    INT0_Recieved =  UDR0;// Fetch the received byte value into the variable "ByteReceived"
	//_delay_us(20);

	//USART0_Transmit_String("\r\n");
	
	//USART1_ISR_Transmit_Char(INT0_Recieved);
	 //USART1_ISR_Transmit_Char( 'A');
	
	if(INT0_Recieved == 'S')
	{
	//USART1_ISR_Transmit_Char('A');
	    CrutchInteruptFlag = 1;
		for(index=0;index<7;index++)
		  {
		   FrameBuf[index]= USART0_Recieve_Char();
           //USART1_ISR_Transmit_Char(FrameBuf[index]);
			//loop++;
		  }
		  INT0_Recieved=0;
		   
	
		  //USART1_ISR_Transmit_String(FrameBuf);
		 // USART1_ISR_Transmit_String("\r");
	}
	else
	{
		
	}

	
	//USART1_ISR_Transmit_Char(INT0_Recieved);
    //UDR0 = INT0_Recieved;
	
    UDR0 = 0;
	RXC0_INT_ENABLE
//	sei();

}

*/


ISR(USART0_RX_vect)
{
  //cli();
  RXC0_INT_DISABLE
  int index;
    INT0_Recieved =  UDR0;// Fetch the received byte value into the variable "ByteReceived"
	//_delay_us(20);

	//USART0_Transmit_String("\r\n");
	 
	//ISR_USART0_Transmit_Char(INT0_Recieved);
	 //USART1_ISR_Transmit_Char( 'A');
		 
	if(INT0_Recieved == '$')
	{
	//ISR_USART0_Transmit_Char('a');
	//Joystick_Interrupt_Counter++;
	    //CrutchInteruptFlag = 1;
	
		for(index=0;index<33;index++)
		  {
		   FrameBuf[index]= USART0_Recieve_Char();
           //USART1_ISR_Transmit_Char(FrameBuf[index]);
		    //ISR_USART0_Transmit_Char(FrameBuf[index]);
			//loop++;
		  }
		  INT0_Recieved=0;
		   
	
		  //USART1_ISR_Transmit_String(FrameBuf);
		 // USART1_ISR_Transmit_String("\r");
	}
	else
	{
		
	}
	/*if((CrutchInteruptFlag == 1)&&(FrameBuf[33]==13)&&(FrameBuf[0]=='B'))
	{
       Emergency_stop_Flag = 1;
	}*/

	
	//USART1_ISR_Transmit_Char(INT0_Recieved);
    //UDR0 = INT0_Recieved;
	
   // UDR0 = 0;
	RXC0_INT_ENABLE
//	sei();

}
//---------- USART0 TRANSMITING STRING  --------																					//
void USART0_Transmit_String(char sendbuf[80])										//		//
{																					//
	auto int StringLen,loop;													    //
	StringLen = strlen(sendbuf);													//
															                        //
																			    	//
	for(loop=0;loop<StringLen;loop++)												//
	{																				//
		USART0_Transmit_Char(sendbuf[loop]);
		_delay_us(1500);												//
	}																				//
	USART0_Transmit_Char(' ');																//
}

void ISR_USART0_Transmit_String(char sendbuf[80])										//		//
{																					//
	auto int StringLen,loop;													    //
	StringLen = strlen(sendbuf);													//
															                        //
																			    	//
	for(loop=0;loop<StringLen;loop++)												//
	{																				//
		ISR_USART0_Transmit_Char(sendbuf[loop]);
		_delay_us(1500);												//
	}																				//
	USART0_Transmit_Char(' ');																//
}




//*******************************************************************************************
/*======================================= USART 1 ===========================================*/
//*******************************************************************************************


//---------- USART1 INITIALIZATION --------
void USART1_INIT()
{   
	UBRR1H = (BAUD1_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
   	UBRR1L = BAUD1_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

   	UCSR1B |= (1 << RXEN1) | (1 << TXEN1)|(1<<RXCIE1);   // Turn on the transmission and reception circuitry and RX Intrupt disabled.
   	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11); // Use 8-bit character sizes
}

//---------- USART1 TRANSMITING CHARACTER DATA --------
void USART1_Transmit_Char(uint8_t CHARDATA)
{
	while ((UCSR1A & (1 << UDRE1)) == 0) {};
	UDR1 = CHARDATA;
	/*//naga code
	while( !(UCSR0A&(1<<UDRE0)) )4 
	UDR0 = u8Data;
	*/
}
void USART1_ISR_Transmit_Char(uint8_t CHARDATA)
{
	while ((UCSR1A & (1 << UDRE1)) == 0) {};
	UDR1 = CHARDATA;
	/*//naga code
	while( !(UCSR0A&(1<<UDRE0)) );
	UDR0 = u8Data;
	*/
}
//---------- USART1 RECIEVING CHARECTER DATA --------
unsigned char USART1_Recieve_Char()
{
   //Wait untill a data is available

   while(!(UCSR1A & (1<<RXC1)));


   return UDR1;
}

//---------- USART1 INTERRUPT SUBROUTINE --------
ISR(USART1_RX_vect)
{
 
    INT1_Recieved =  UDR1;// Fetch the received byte value into the variable "ByteReceived"
	if(INT1_Recieved != 'K')
	{
		 USART1_ISR_Transmit_String(audiobuf);
	}

 
   //UDR1 = INT1_Recieved; // Echo back the received byte back to the computer
    UDR1 = 0;
}


//---------- USART1 TRANSMITING STRING  --------																					//
void USART1_Transmit_String(char sendbuf[80])										//		//
{																					//
	auto int StringLen,loop;													    //
	StringLen = strlen(sendbuf);													//
															                        //
																				    //
	for(loop=0;loop<StringLen;loop++)												//
	{																				//
		USART1_Transmit_Char(sendbuf[loop]);	
		_delay_us(300);											//
	}																				//
//	USART1_Transmit_Char(' ');																//
}

void USART1_ISR_Transmit_String(char sendbuf[80])										//		//
{		
	 																			//
	auto int StringLen,loop;													    //
	StringLen = strlen(sendbuf);													//
															                        //
																				    //
	for(loop=0;loop<StringLen;loop++)												//
	{																				//
		USART1_Transmit_Char(sendbuf[loop]);
		_delay_ms(1);												//
	}																				//
//	USART1_Transmit_Char(' ');																//
}



/*==================================EO USART====================================*/
/********************************************************************************/
/*==============================================================================*/




//**********************************************************************************//
//																					//
//  ADC module initialization 														//
//																					//
//**********************************************************************************//
void ADC_Init(void)																	//
{																					//
	//select reference voltage														//
	//AVCC with external capacitor at AREF pin										//
	ADMUX|=(0<<REFS1)|(0<<REFS0);//01												//
	//set prescaller and enable ADC													//
	ADCSRA|=(1<<ADEN)|(0<<ADIE);//enable ADC with dummy conversion					//
	//set sleep mode for ADC noise reduction conversion								//
	//set_sleep_mode(SLEEP_MODE_ADC);												//
}																					//
																					//
int ADC_Start( int channel)															//
{																					//
	//int ch;																		//
	//ch=channel;																	//
	//PORTB=0XFF;																	//
	int adcvalue_temp;																//
	ADMUX=(ADMUX&0xF0)|channel;   //30												//
	ADCSRA |= (1<<ADSC)|(0<<ADIE)|(1<<ADEN)|(1<<ADPS1);										//
	//ADCSRA |= (0<<ADIF);															//
	//while(!(ADCSRA & (1<<ADIF)));													//
	while(bit_is_set(ADCSRA,ADSC));													//
	adcvalue_temp = ADCL;  															//
	//shift from low level to high level ADC, from 8bit to 10bit					//
	adcvalue_temp += (ADCH<<8);														//
	//ADCSRA |= (1<<ADIF);															//
  	//_delay_ms(150);																//
   //PORTB=0X00;																	//
   return(adcvalue_temp);															//
}																					//
																					//
float AverageADC(int channel,int AverageCount)										//
{																					//
	int loop,adc;																	//
	unsigned long total;															//
	float Volt;																		//
	float avg;																		//
	//unsigned long avg;															//
	total=0;																		//
	ADC_Start(channel);																//
	for	(loop=0;loop<AverageCount;loop++)											//
		{																			//
																						//
			adc = ADC_Start(channel);
																//
			total=total+adc;														//
		}																			//
	avg = total/AverageCount;														//
	Volt=(ADC_REFERENCE * avg)/1024.0;	//5.066													//
	return (Volt);																	//
}																					//
//****************************EO ADC Module*****************************************//



//****************************************  TIMMER RELATED FUNCTION   *********************************
//
//*****************************************************************************************************

void TIMER0_INIT(void)
{

	// normal mode
        TCCR0 |= (0<<WGM01)|(0<<WGM00);
   // prescaler 64
        TCCR0 |= (1<<CS02)|(1<<CS01)|(1<<CS00); //prescalar 1024
       // OCR0=255;
        TCNT0=0;
   // activate interrupt
        TIMSK |= (1<<TOIE0)|(0<<OCIE0);
}


void TIMER1_INIT(void)
{

		// normal mode
		TCCR1A = (0<<WGM12)|(0<<WGM11)|(0<<WGM10);
		//presclalar
		TCCR1B = (1<<CS12)|(0<<CS11)|(1<<CS10); // presclar 1024
		TCNT1H = 255;
		TCNT1L = 240;
		//activate interrupt
		TIMSK |=  (1<<TOIE1);
}



void TIMER2_INIT(void)
{


	// normal mode
        TCCR2 |= (0<<WGM21)|(0<<WGM20);
   // prescaler 
        TCCR2 |= (1<<CS22)|(0<<CS21)|(1<<CS20);  //prescalar 1024
        //OCR2=255;
        TCNT2=0;
   // activate interrupt
        TIMSK |= (1<<TOIE2)|(0<<OCIE2);
}



void TIMER3_INIT(void)
{

		// normal mode
		TCCR3A = (0<<WGM32)|(0<<WGM31)|(0<<WGM30);
		//presclalar
		TCCR3B = (1<<CS32)|(0<<CS31)|(1<<CS30); // presclar 1024
		TCNT3H = 255;
		TCNT3L = 0;
		//activate interrupt
		ETIMSK |=  (1<<TOIE3);

}



//***************************** I2C INITIALISATION  ****************//
//																	//
//																	//
//******************************************************************//

void twi_init(void)
{
//#if F_CPU == 8000000UL
 TWCR= 0X00; //disable twi
 TWBR= 0x12; //set bit rate12
 TWSR= 0x00; //set prescale
 TWCR= 0x44; //enable twi
//#endif
/*#if F_CPU == 16000000UL
 TWCR= 0X00; //disable twi
 TWBR= 0x2C; //set bit rate12
 TWSR= 0x00; //set prescale
 TWCR= 0x44; //enable twi
#endif*/

}



ISR(TIMER0_OVF_vect)//TIMER0_OVF_vect ,TIMER0_COMP_vect
{

    Time_counter++;
	//ISR_USART0_Transmit_Char('A');
	
 
		  
	TCNT0=TCNTCOUNT;
	//sei();
}


