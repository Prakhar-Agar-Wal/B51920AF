#include <PID_v2.h>
#include <Encoder.h>



// Motor driver Pins 
int in1Left = A0;
int in2Left = 13;
int in1Right = 12;
int in2Right = 11;

int pwmLeft = 10;  //PWMS
int pwmRight = 9; //PWMS

//IR sensor Pins

int iRLeftfront = A3;
int iRLeftside = A2;
int iRRightfront = 3;
int iRRightside = 4;

//IR Variables
int irReadLF = 0;
int irReadLS = 0;
int irReadRF = 0;
int irReadRS = 0;

//Encoder pins and Initialization

Encoder rightEnc(6,5);
Encoder leftEnc(7,8);
//int encLeft1 = 6;
//int encLeft2 = 5;
//int encRight1 = 8;
//int encRight2 = 7;

long curPosRight =0;
long curPosLeft =0;
long prevPosLeft =0;
long prevPosRight =0;
volatile int rpmRight = 0;
volatile int rpmLeft = 0;
volatile int rot_speed;
long previousMillis = 0;
long currentMillis = 0;
int interval = 40;
const int PPR = 116;


// PID initialization

// double kp = 0.5;  
// double ki = 1;
// double kd = 0.007;
double kp = 0.2;  
double ki = .85;
double kd = 0.001;
double SetpointLeft, SetpointRight, InputLeft, OutputLeft, InputRight, OutputRight;

PID myPIDLeft(&InputLeft, &OutputLeft, &SetpointLeft,kp,ki,kd, DIRECT);
PID myPIDRight(&InputRight, &OutputRight, &SetpointRight,kp,ki,kd, DIRECT);

//angle PID
double kp_angle = 4;
double ki_angle = 0;
double kd_angle = 0.1;//0.08
double setPointAngle, inputAngle, outputAngle;
double signedSetPointLeft, signedSetPointRight;

PID anglePID(&inputAngle, &outputAngle, &setPointAngle,kp_angle, ki_angle, kd_angle, DIRECT);


//others

volatile int incomingByte= 0;

long temp1;
long temp2;
long temp3;

 int receivedFrame[4];
int strCounterForFrames =0;
int frameReceivedFlag=0;

long CurrentMillis = 0;
long LastMillis = 0;
long LastMillis1 = 0;
bool stopFlag = 0;

float abs_multiplier = 0.5;
float yaw = 0.0;
int headingAngle_input;
