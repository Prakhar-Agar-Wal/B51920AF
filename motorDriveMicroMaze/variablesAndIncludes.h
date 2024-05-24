#include <PID_v2.h>
#include "floodFill.h"
// #include <Encoder.h>



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
// Encoder rightEnc(5);
// Encoder leftEnc(8);
const short int encLeft = 8;
const short int encRight = 5;
bool previousStateLeft = 0;
bool previousStateRight = 0;
bool currReadLeft = 0;
bool currReadRight = 0;

// Encoder rightEnc(5,6);
// Encoder leftEnc(8,7);
//int encLeft1 = 6;
//int encLeft2 = 5;
//int encRight1 = 8;
//int encRight2 = 7;

volatile long int curPosRight =42;
volatile long int curPosLeft =42;
volatile long int prevPosLeft =42;
volatile long int prevPosRight =42;
volatile int rpmRight = 0;
volatile int rpmLeft = 0;
volatile int rot_speed;
long previousMillis = 0;
long currentMillis = 0;
int interval = 40;
const int PPR = 60;


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

volatile int setPointLinear= 0;

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

bool launchControlActive = 0;

int previous_launch_control = 1;
int previous_previous_launch_control = 1;

// odometry
// float realVelRight= 0;
// float realVelLeft = 0;
float circumference = 0.034*3.14;
// struct odomVals_struct{
//   float x_n;
//   float y_n;
//   float theta_n;
// }odomVal={0};

// float x_n_test=0;
// float y_n_test=0;
// float theta_n_test=0;
// float R ;
// float ICC_x;
// float ICC_y;
    
// float omega;
// float delta_Theta;

// odometry
float previous_distance = 0;
float current_distance = 0.13;
// struct neighbors{
//     bool visited,NorthN,EastN,SouthN,WestN;
//     short int data;
// };
short int current_position_x = 0;
short int current_position_y = 0;

float cell_length = 0.18;

bool temp4=1;
bool achieved = 0;
bool achieved1 = 0;


