volatile char buf[80];  
volatile float W_Span,L_Offset,U_Load,O_Load,C_Factor;
volatile char W_Span_Buf[10];
volatile char L_Offset_Buf[10];
volatile char U_Load_Buf[10];
volatile char O_Load_Buf[10];
volatile char C_Factor_Buf[10];
volatile char FrameBuf[35]; 
extern int key;
extern uint32_t Count_ChannelA,Temp_Count_ChannelA; 
extern float weight;
char LeftThighBuf[4];
char LeftKneeBuf[4];
char RightThighBuf[4];
char RightKneeBuf[4];
char BatteryBuf[4];
char ThighSpeedBuf[2];
char KneeSpeedBuf[2];
char LiftBuf[2];
char StrideBuf[2];
 

int GetKeyPressed();
void Home(void);
void PageOne(void); 
void Process_Data_Page(void);
