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

// void updateRealVel(){
//   shifted_yaw = (unshifted_yaw<0?unshifted_yaw+360:unshifted_yaw)*3.14/180; //changing reference from -180 to 180 to 0 to 360 & also changing it to radians
//   realVelLeft = (signedSetPointLeft<0)?((circumference*rpmLeft*-1)/60):((circumference*rpmLeft)/60);
//   realVelRight = (signedSetPointRight<0)?((circumference*rpmRight*-1)/60):((circumference*rpmRight)/60);
//   // Serial.print(shifted_yaw);
//   // Serial.print(" ");
//   // Serial.print(realVelLeft);
//   // Serial.print(" ");
//   // Serial.println(realVelRight);
// }
// void calc_x_y_theta(float x,float y,float theta,float vr,float vl,float l,float t){
//   if(vr == vl){
//     // float tic1 = millis();
//     odomVal.x_n = x + (vr*t*cos(theta));
//     odomVal.y_n = y + (vr*t*sin(theta));
    
//   }
//   else{
//      R = (l/2) * ((vr + vl) / (vr - vl));        
//      ICC_x = x - (R*sin(theta)); 
//      ICC_y =  y + (R*cos(theta));
    
//      omega = ((vr - vl) / l);
//      delta_Theta = (omega * t);
    
//     odomVal.x_n = ((x - ICC_x) * cos(delta_Theta)) - ((y - ICC_y) * sin(delta_Theta)) + ICC_x;
//     odomVal.y_n = ((x - ICC_x) * sin(delta_Theta)) + ((y - ICC_y) * cos(delta_Theta)) + ICC_y;
//     // x_n_test = ((x - ICC_x) * cos(delta_Theta)) - ((y - ICC_y) * sin(delta_Theta)) + ICC_x;
//     // y_n_test = ((x - ICC_x) * sin(delta_Theta)) + ((y - ICC_y) * cos(delta_Theta)) + ICC_y;    
//   }
 

// }

void odometry(){
  // calc_x_y_theta(odomVal.x_n,odomVal.y_n,shifted_yaw,realVelRight,realVelLeft,0.08,((float)interval/1000));
  // calc_x_y_theta(x_n_test,y_n_test,shifted_yaw,,,0.08,interval/1000);
  current_distance = ((float)curPosLeft+(float)curPosRight)/2;
  current_distance = (current_distance/60)*circumference;
  if (setPointLinear){
    
    if(setPointAngle == 0){
      
      if((current_distance-previous_distance)>cell_length){
         current_position_x++;
         previous_distance = current_distance;
         
        // Serial.print(current_position_x);
        // Serial.print(" ");
        // Serial.println(current_distance);
      }
    }
    if(setPointAngle == 180 || setPointAngle == -180){
      
      if((current_distance-previous_distance)>cell_length){
         current_position_x--;
         previous_distance = current_distance;
      }
    }
    if(setPointAngle == -90){
      
      if((current_distance-previous_distance)>cell_length){
         current_position_y--;
         previous_distance = current_distance;
      }
    }
    if(setPointAngle == 90){
      
      if((current_distance-previous_distance)>cell_length){
         current_position_y++;
         previous_distance = current_distance;
      }
    }


  }
  else{
    if(previous_distance)
    previous_distance = current_distance;
  }


}

void updateRpm(){
  updateEnc();
  // Serial.println(rpmRight);
  currentMillis = millis();
  if((currentMillis - previousMillis)>interval){
    previousMillis = currentMillis;
    rpmRight = calculateRPM(curPosRight,prevPosRight);
    prevPosRight = curPosRight;
    rpmLeft = calculateRPM(curPosLeft,prevPosLeft);
    prevPosLeft = curPosLeft;
    
    }
  // updateRealVel();

  odometry();
  if ((setPointLinear>0) && ((rpmRight == 0) && (rpmLeft == 0))){
    
    launchControlActive = 1;
  }
  // Serial.println(launchControlActive);
  setPointLinear = launchControl(setPointLinear);
  if(abs(yaw-headingAngle_input)>10){
    setPointLinear = 0;
  }
  
  signedSetPointLeft = setPointLinear+outputAngle;
  signedSetPointRight = setPointLinear-outputAngle;
  SetpointLeft=abs(setPointLinear+outputAngle);
  SetpointRight=abs(setPointLinear-outputAngle);
  
  
  
  

  InputLeft=rpmLeft;
  InputRight=rpmRight;
  // Serial.print(odomVal.x_n);
  // Serial.print(" ");
  // Serial.print(odomVal.y_n);
  // Serial.print(" ");
  // Serial.println(odomVal.theta_n);
  // Serial.print(realVelLeft);
  // Serial.print(" ");
  // Serial.print(realVelRight);
  // Serial.print(" ");
  // Serial.println(rpmLeft);
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
