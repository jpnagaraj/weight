volatile char buf[80];  
volatile float W_Span,L_Offset,U_Load,O_Load,C_Factor,Speed;
float weight,B_Load,F_Rate,Frate_Totalizer;
volatile float MI,ZO,SN,MA;
float Epromadress_W_Span,Epromadress_L_Offset,Epromadress_U_Load,Epromadress_O_Load,Epromadress_C_Factor;
float Epromadress_Speed;
float Epromadress_MI,Epromadress_ZO,Epromadress_SN,Epromadress_MA;
char KeyPressedStatus;


volatile char FrameBuf[35]; 
extern int key;
extern volatile uint32_t Count_ChannelA,Temp_Count_ChannelA; 
extern float weight;
 
int GetKeyPressed();
void Home(void);
void PageOne(void); 
void Process_Data_Page(void);
void Calibrate_Data_Page(void);
void Passward_Verification(void);
