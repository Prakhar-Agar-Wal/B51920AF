#include <math.h>
int calculateRPM(int currentEncoder, int previousEncoder)
{

        temp1 = currentEncoder-previousEncoder;
        temp2 = temp1*60000; // milliseconds to seconds and then senconds to minutes so 60*1000
        temp3 = PPR*interval;
        rot_speed = temp2/temp3;
        return(rot_speed);
}

void updateRpm(){
  signedSetPointLeft = incomingByte+outputAngle;
  signedSetPointRight = incomingByte-outputAngle;
  SetpointLeft=abs(incomingByte+outputAngle);
  SetpointRight=abs(incomingByte-outputAngle);
  
  curPosRight = rightEnc.read();
  curPosLeft = leftEnc.read();
  
  
  currentMillis = millis();
  if((currentMillis - previousMillis)>interval){
    previousMillis = currentMillis;
    rpmRight = calculateRPM(curPosRight,prevPosRight);
    prevPosRight = curPosRight;
    rpmLeft = calculateRPM(curPosLeft,prevPosLeft);
    prevPosLeft = curPosLeft;
    
    }
  InputLeft=abs(rpmLeft);
  InputRight=abs(rpmRight);
  // Serial.print(curPosRight);
  // Serial.print(" ");
  // Serial.print(InputRight);
  // Serial.print(" ");
  // Serial.print(curPosLeft);
  // Serial.print(" ");
  // Serial.println(InputLeft);
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
