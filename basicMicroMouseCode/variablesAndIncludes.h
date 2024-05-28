#include <stdint.h>
#include <PID_v2.h>
#include <cppQueue.h>
// #include <Encoder.h>

#define DEBUG_MODE 0



// Motor driver Pins 
const int in1Left  = A0;
const int in2Left  = 13;
const int in1Right  = 12;
const int in2Right  = 11;

const int pwmLeft = 10;  //PWMS
const int pwmRight = 9; //PWMS

//IR sensor Pins

const int iRLeftfront = A3;
const int iRLeftside = A2;
const int iRRightfront = 3;
const int iRRightside = 4;

//IR Variables
int irReadLF = 0;
int irReadLS = 0;
int irReadRF = 0;
int irReadRS = 0;

//Encoder pins and Initialization
// Encoder rightEnc(5);
// Encoder leftEnc(8);
const int encLeft = 8;
const int encRight = 5;
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
const int interval = 40;
const int PPR = 60;


// PID initialization

// double kp = 0.5;  
// double ki = 1;
// double kd = 0.007;
const PROGMEM double kp = 0.2;  
const PROGMEM double ki = .85;
const PROGMEM double kd = 0.001;
double SetpointLeft, SetpointRight, InputLeft, OutputLeft, InputRight, OutputRight;

PID myPIDLeft(&InputLeft, &OutputLeft, &SetpointLeft,kp,ki,kd, DIRECT);
PID myPIDRight(&InputRight, &OutputRight, &SetpointRight,kp,ki,kd, DIRECT);

//angle PID
const PROGMEM double kp_angle = 4;
const PROGMEM double ki_angle = 0;
const PROGMEM double kd_angle = 0.1;//0.08
double setPointAngle, inputAngle, outputAngle;
double signedSetPointLeft, signedSetPointRight;

PID anglePID(&inputAngle, &outputAngle, &setPointAngle,kp_angle, ki_angle, kd_angle, DIRECT);


//others

volatile int setPointLinear= 0;

long temp1;
long temp2;
long temp3;


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
//     int data;
// };
int current_position_x = 0;
int current_position_y = 0;

float cell_length = 0.18;

bool temp4=1;
bool achieved = 0;
bool achieved1 = 0;

bool achieved_back_to_square_0 = 0;

struct neighbors{
    unsigned visited:1;
    unsigned NorthN:1;
    unsigned EastN:1;
    unsigned SouthN:1;
    unsigned WestN:1;
    uint8_t data;
    unsigned int PosX:5;
    unsigned int PosY:5;
};

struct pair{
  int first;
  int second;
};
//main variables
pair xy;
cppQueue pathStack(sizeof(xy),50,LIFO); // do not increase this value, it is causing ram overwrite issues and garbage is getting printed
// Row of the maze
int m = 8;
// Column of the Maze
int n = 8;
pair startingCell={0};
pair nextCell={0};
pair currCell = {startingCell.first,startingCell.second};
pair endingCell = {m/2,n/2};
pair pathCell;

// endingCell.first=m/2;
// endingCell.second=n/2;


// currCell.first=startingCell.first;
// currCell.second=startingCell.second;

// nextCell.first=0;
// nextCell.second=0;

bool firstTime=true;

struct coordinates{
  bool northPresent;
  bool southPresent;
  bool eastPresent;
  bool westPresent;
};
short int currentCell_x = 0;
short int currentCell_y = 0;


static neighbors arr[8][8]={0};