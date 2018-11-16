// **************************************************************
// ***  CONTROLLER MODULES HEADER FILE ******** 		
// **************************************************************

//************* BAUDRATE CALCULATION FOR USART ******************

//====== BAUD RATE USART0 =======//
//#define F_CPU 16000000UL
#define USART0_BAUDRATE 9600
#define BAUD0_PRESCALE (((F_CPU / (USART0_BAUDRATE * 16UL))) - 1)

//====== BAUD RATE USART1 =======//
//#define F_CPU 16000000UL
#define USART1_BAUDRATE 9600
#define BAUD1_PRESCALE (((F_CPU / (USART1_BAUDRATE * 16UL))) - 1)


#define ADC_REFERENCE 4.83
#define RXC0_INT_DISABLE (UCSR0B &= (1 << RXEN0) | (1 << TXEN0)|(0<<RXCIE0));
#define RXC0_INT_ENABLE (UCSR0B |= (1 << RXEN0) | (1 << TXEN0)|(1<<RXCIE0));


//*************  PORT INITIALISATION FUNCTION****************
	void Port_Init();

//*************  USART 0 RELATED FUNCTIONS  *********************
	void USART0_INIT();
	void USART0_Transmit_Char(uint8_t);
	unsigned char USART0_Recieve_Char();
	unsigned char USART0_TimeFRee_Recieve_Char();	
	void USART0_Transmit_String(char*);
	void ISR_USART0_Transmit_Char(uint8_t CHARDATA);
	void ISR_USART0_Transmit_String(char sendbuf[80]);	

//*************  USART 0 RELATED FUNCTIONS  *********************
	void USART1_INIT();
	void USART1_Transmit_Char(uint8_t);
	void USART1_ISR_Transmit_Char(uint8_t);
	void USART1_ISR_Transmit_String(char*);
	unsigned char USART1_Recieve_Char();
	void USART1_Transmit_String(char*);
	

//******************  ADC FUNCTION DECLARATION  *****************
	void ADC_Init(void);
	int ADC_Start( int channel);
	float AverageADC(int channel,int AverageCount);

//******************** I2C FUNCTION DECLARATION  *****************
	void twi_init(void);
//*****************  TIMMERS FUNTION DECLARATION  ****************
  void TIMER0_INIT(void);
  void TIMER1_INIT(void);
  void TIMER2_INIT(void);
  void TIMER3_INIT(void);




extern volatile char INT0_Recieved;  //
extern volatile char INT1_Recieved;
extern volatile char FrameBuf[35];
extern volatile char CrutchInteruptFlag;
volatile char audiobuf[5];
extern volatile unsigned long int Joystick_Interrupt_Counter;
volatile char Emergency_stop_Flag;
volatile char buf[80];
volatile unsigned int Time_counter;
volatile int TCNTCOUNT;
