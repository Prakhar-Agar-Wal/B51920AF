#include "Arduino.h"
#include "variablesAndIncludes.h"
void reverse(int pwmleft,int pwmright)
{
  digitalWrite(in1Left, LOW);
  digitalWrite(in2Left, HIGH);
  digitalWrite(in1Right, LOW);
  digitalWrite(in2Right, HIGH);

  analogWrite(pwmLeft, pwmleft);
  analogWrite(pwmRight, pwmright);

}
void Stop()
{
  digitalWrite(in1Left, HIGH);
  digitalWrite(in2Left, HIGH);
  digitalWrite(in1Right, HIGH);
  digitalWrite(in2Right, HIGH);
  // Serial.println("Stopp");
  analogWrite(pwmLeft, 0);
  analogWrite(pwmRight, 0);

}
void Brake()
{
  digitalWrite(in1Left, LOW);
  digitalWrite(in2Left, HIGH);
  digitalWrite(in1Right, LOW);
  digitalWrite(in2Right, HIGH);
  if (rpmLeft>=20 && rpmRight>=20){
    // Serial.println("brakinggggg");
    analogWrite(pwmLeft,rpmLeft*abs_multiplier);
    analogWrite(pwmRight,rpmRight*abs_multiplier);
    // analogWrite(pwmLeft,255);
    // analogWrite(pwmRight,255);
  }
  else Stop();
}
void turnright(int pwmleft,int pwmright){
  digitalWrite(in1Left, LOW);
  digitalWrite(in2Left, HIGH);
  digitalWrite(in1Right, HIGH);
  digitalWrite(in2Right, LOW);

  analogWrite(pwmLeft, pwmleft);
  analogWrite(pwmRight, pwmright);
}

void turnleft(int pwmleft,int pwmright){
  digitalWrite(in1Left, HIGH);
  digitalWrite(in2Left, LOW);
  digitalWrite(in1Right, LOW);
  digitalWrite(in2Right, HIGH);

  analogWrite(pwmLeft, pwmleft);
  analogWrite(pwmRight, pwmright);
}

void forward(int pwmleft,int pwmright)
{
    if(round(SetpointLeft)<=10.00 && round(SetpointRight)<=10.00){
    Stop();
  }
  else{
  if(signedSetPointLeft>=0 && signedSetPointRight>=0){
  digitalWrite(in1Left, HIGH);
  digitalWrite(in2Left, LOW);
  digitalWrite(in1Right, HIGH);
  digitalWrite(in2Right, LOW);

  analogWrite(pwmLeft, pwmleft);
  analogWrite(pwmRight, pwmright);
  }
  else if(signedSetPointLeft<0 && signedSetPointRight>=0){
    turnleft(pwmleft,pwmright);
  }
  else if(signedSetPointLeft>=0&&signedSetPointRight<0){
    turnright(pwmleft, pwmright);
  }
  else{
    reverse(pwmleft, pwmright);
  }

}
}

