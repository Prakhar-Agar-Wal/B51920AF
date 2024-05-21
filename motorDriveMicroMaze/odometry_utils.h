#include <math.h>
int calculateRPM(int currentEncoder, int previousEncoder)
{

        temp1 = currentEncoder-previousEncoder;
        temp2 = temp1*60000; // milliseconds to seconds and then senconds to minutes so 60*1000
        temp3 = PPR*interval;
        rot_speed = temp2/temp3;
        return(rot_speed);
}
void updateEnc(){
  currReadLeft = digitalRead(encLeft);
  currReadRight = digitalRead(encRight);
  if (currReadRight != previousStateRight){
    curPosRight++;
    previousStateRight = currReadRight;
  }
  if (currReadLeft != previousStateLeft){
    curPosLeft++;
    previousStateLeft = currReadLeft;
  }

}

void updateRpm(){
  updateEnc();
  if ((setPointLinear>0) && ((rpmRight == 0) && (rpmLeft == 0))){
    launchControlActive = 1;
  }
  // Serial.println(launchControlActive);
  setPointLinear = launchControl(setPointLinear);
  signedSetPointLeft = setPointLinear+outputAngle;
  signedSetPointRight = setPointLinear-outputAngle;
  SetpointLeft=abs(setPointLinear+outputAngle);
  SetpointRight=abs(setPointLinear-outputAngle);
  
  
  
  currentMillis = millis();
  if((currentMillis - previousMillis)>interval){
    previousMillis = currentMillis;
    rpmRight = calculateRPM(curPosRight,prevPosRight);
    prevPosRight = curPosRight;
    rpmLeft = calculateRPM(curPosLeft,prevPosLeft);
    prevPosLeft = curPosLeft;
    
    }
  InputLeft=rpmLeft;
  InputRight=rpmRight;
  // Serial.print(curPosRight);
  // Serial.print(" ");
  // Serial.print(rpmRight);
  // Serial.print(" ");
  // Serial.print(curPosLeft);
  // Serial.print(" ");
  // Serial.println(rpmLeft);
  myPIDLeft.Compute();
  myPIDRight.Compute();
  
}

int correctEulerYaw(int angle_to_convert){
  return (((headingAngle_input<=-135) || (headingAngle_input>=135))?(angle_to_convert<0)?360+angle_to_convert:angle_to_convert:angle_to_convert);
}

void anglePID1(int headingAngle){
  setPointAngle = headingAngle;
  inputAngle = round(yaw);
  anglePID.Compute();
  // Serial.println(outputAngle);

}
