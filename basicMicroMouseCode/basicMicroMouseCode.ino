// #include <NeoHWSerial.h>
// #include <NeoHWSerial_private.h>

#include "movementControl.h"
#include "displayStuff.h"
#include "imu_driver.h"
#include "setup.h"
#include "odometry_utils.h"
#include "floodFill.h"

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
void uTurn(){
  if(setPointAngle == 0){
    setPointAngle = -180;
    currentCell_x -=1;
  }
  else if(setPointAngle == -180 || setPointAngle == 180){
    setPointAngle = 0;
    currentCell_x +=1;
  }
  else if(setPointAngle == 90){
    setPointAngle = -90;
    currentCell_y-=1;
  }
  else if(setPointAngle == -90){
    setPointAngle = 90;
    currentCell_y+=1;
  }
}
void setup() {
// Serial Begin
  // NeoSerial.attachInterrupt(inputs);
  _imu_setup();
  Serial.begin(115200);
// Motor Driver
 _main_setup();

 init_flood();
 

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

void stateMachineRunSwitch(){
  int casee = 0;
  if(achieved) {casee++; achieved = 0;}

  if(casee == 0 && !achieved){
    achieved = moveToCell(15,0);
  }
  else if(casee == 1 && !achieved){
    achieved = moveToCell(-4,4);
  }
  else if(casee == 2 && !achieved){
    achieved = moveToCell(-4,1);
  }
  else{
    setPointLinear = 0;
  }
}



void turnRight(){
  if(setPointAngle == 0){
    setPointAngle = 90;
    currentCell_y +=1;
  }
  else if(setPointAngle == -180 || setPointAngle == 180){
    setPointAngle = -90;
    currentCell_y -=1;
  }
  else if(setPointAngle == 90){
    setPointAngle = -180;
    currentCell_x -= 1;
  }
  else if(setPointAngle == -90){
    setPointAngle = 0;
    currentCell_x+=1;
  }

}

void turnLeft(){
   if(setPointAngle == 0){
    setPointAngle = -90;
    currentCell_y -=1;
  }
  else if(setPointAngle == -180 || setPointAngle == 180){
    setPointAngle = 90;
    currentCell_y +=1;
  }
  else if(setPointAngle == 90){
    setPointAngle = 0;
    currentCell_x += 1;
  }
  else if(setPointAngle == -90){
    setPointAngle = -180;
    currentCell_x-=1;
  }
}

void forward__(){
  if(setPointAngle == 0){
    currentCell_x +=1;
  }
  else if(setPointAngle == -180 || setPointAngle == 180){
    currentCell_x -=1;
  }
  else if(setPointAngle == 90){
    currentCell_y += 1;
  }
  else if(setPointAngle == -90){
    currentCell_y -=1;
  }
}

void checkAndMove(){
  bool irReadFront = irReadLF || irReadRF;
  if(irReadFront && irReadLS && irReadRS){
    uTurn();
  }
  else if(!irReadRS){
    turnRight();
  }
  else if(!irReadLS){
    turnLeft();
  }
  else{
    forward__();
  }
  moveToCell(currentCell_x, currentCell_y);
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

  setPointLinear = 100;

  // stateMachineRunSwitch();
  
  // if ((irReadLF == 0 ) || (irReadLS == 0 ) || (irReadRF == 0 ) || (irReadRS == 0 ))
  // simulation();
  // if(CurrentMillis>10000){
  // Serial.print(currCell.first);
  // Serial.print(" ");
  // Serial.println(currCell.second);
// #####################
  // if(achieved && !achieved_back_to_square_0){
  //   // delay(500);
  //   irReadLF = digitalRead(iRLeftfront);
  //   irReadLS = digitalRead(iRLeftside);
  //   irReadRF = digitalRead(iRRightfront);
  //   irReadRS = digitalRead(iRRightside);
  //   #if (DEBUG_MODE == 1)
  //   Serial.print("Current cell");
  //   Serial.print(" ");
  //   Serial.print(currCell.first);
  //   Serial.print(" ");
  //   Serial.println(currCell.second);
  //   #endif
  //   currCell = main_flood(currCell);
  //   #if (DEBUG_MODE == 1)
  //   Serial.print("Next cell");
  //   Serial.print(" ");
  //   Serial.print(currCell.first);
  //   Serial.print(" ");
  //   Serial.println(currCell.second);
  //   #endif
  //   achieved = 0;
  // }
// ###########################
  // if(currentMillis>10000){
  //   if(!achieved && !achieved1){
  //     achieved = moveToCell(15, 0);
  //   }
  //   if(achieved && !achieved1){
  //     achieved1 = moveToCell(15,3);
  //   }
  // }
  
  // currCell = main_flood(currCell);
  // #########################################
  // if(!achieved_back_to_square_0)
  // achieved = moveToCell(currCell.first,currCell.second);
  // else setPointLinear = 0;
  // ####################################
  // if(achieved){
  //   setPointLinear = 0;
  //   delay(500);
  //   checkAndMove();
  //   achieved = moveToCell(current_position_x, current_position_y);
  // }
  // else if(!achieved && (irReadLF||irReadRF)){
  //   setPointLinear = 0;
  //   achieved = 1;
  // }
  // else{
  //   achieved = moveToCell(current_position_x, current_position_y);
  // }
  // Serial.print(achieved);
  // Serial.print(" ");
  // Serial.print(currCell.first);
  // Serial.print(" ");
  // Serial.println(currCell.second);
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
  // displayPWMGraph();
  }


  
  // Serial.println((yaw));
  // Serial.print(" ");

  
  // displayVelocityOdom();

// }
