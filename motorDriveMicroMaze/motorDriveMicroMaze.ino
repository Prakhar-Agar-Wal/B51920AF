// #include <NeoHWSerial.h>
// #include <NeoHWSerial_private.h>

#include "movementControl.h"
#include "displayStuff.h"
#include "imu_driver.h"
#include "setup.h"
#include "odometry_utils.h"

// static void inputs(uint8_t c){
//   if(c != 10){
//     receivedFrame[strCounterForFrames] = c;
//     strCounterForFrames++;
//     if(strCounterForFrames > 3){
//       strCounterForFrames = 0;
//     }
//   }
//   else{
//     frameReceivedFlag = 1;
//     strCounterForFrames=0;
//   }
// }

void setup() {
// Serial Begin
  // NeoSerial.attachInterrupt(inputs);
  _imu_setup();
  Serial.begin(115200);
// Motor Driver
 _main_setup();

}

void simulation(){
  if ((CurrentMillis-LastMillis1)<10000)
  // if ((irReadLF == 0 ) || (irReadLS == 0 ) || (irReadRF == 0 ) || (irReadRS == 0 ))
  {
    setPointLinear=0;
    headingAngle_input = 0;
  }
  else if((CurrentMillis-LastMillis1)<13000){
    //do nothing
    setPointLinear=300;
    headingAngle_input = 0;
  }
  else if ((CurrentMillis-LastMillis1)<14000)
  // if ((irReadLF == 0 ) || (irReadLS == 0 ) || (irReadRF == 0 ) || (irReadRS == 0 ))
  {
    // Brake();
    // stopFlag = 1;
    headingAngle_input = 0;
    setPointLinear=0;
  }

  else if((CurrentMillis-LastMillis1)<11500){
    setPointLinear = 0;
    headingAngle_input=0;
  }
  // else if((CurrentMillis-LastMillis1)<12000){
  //   headingAngle_input=90;
  //   setPointLinear = 0;
  // }
  // else if((CurrentMillis-LastMillis1)<13000){
  //   headingAngle_input=0;
  //   setPointLinear = 0;
  // }
  // //  else if((CurrentMillis-LastMillis1)<19000){
  // //   headingAngle_input=0;
  // //   setPointLinear = 300;
  // // }
  // else if((CurrentMillis-LastMillis1)<14000){
  //   headingAngle_input=180;
  //   setPointLinear = 0;
  // }
  // else if((CurrentMillis-LastMillis1)<15000){
  //   headingAngle_input=180;
  //   setPointLinear = 300;
  // }
  // if((CurrentMillis-LastMillis1)>2000){
  //   headingAngle_input = random(-180,180);
  //   LastMillis1 = CurrentMillis;
  // }

  else
  {
    setPointLinear = 0; //set pwm here
  }

  // headingAngle_input = 0;
  // setPointLinear =0;

}

void loop() {
  yaw = correctEulerYaw(get_yaw());
  anglePID1(correctEulerYaw(headingAngle_input));
  updateRpm();

  forward(OutputLeft,OutputRight);
  irReadLF = digitalRead(iRLeftfront);
  irReadLS = digitalRead(iRLeftside);
  irReadRF = digitalRead(iRRightfront);
  irReadRS = digitalRead(iRRightside);
  CurrentMillis = millis();
  // if ((irReadLF == 0 ) || (irReadLS == 0 ) || (irReadRF == 0 ) || (irReadRS == 0 ))
  // simulation();
  if(CurrentMillis>10000){
  if(!achieved1 && !achieved){
    achieved = moveToCell(15,0);
  }
  
  if(achieved){
    achieved1 = moveToCell(15,3);
  }
  // achieved1 = moveToCell(0,3);
  // Serial.print(current_position_x);
  // Serial.print(" ");
  // Serial.print(current_position_y);
  // Serial.print(" ");
  // Serial.print(setPointLinear);
  // Serial.print(" ");
  // Serial.print(yaw);
  // Serial.print(" ");
  // Serial.println(current_distance);
  }


  
  // Serial.println((yaw));
  // Serial.print(" ");

  // displayPWMGraph();
  // displayVelocityOdom();

}
