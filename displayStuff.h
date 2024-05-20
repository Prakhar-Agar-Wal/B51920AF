// #include "variablesAndIncludes.h"

void displayPWMGraph()
{
  CurrentMillis = millis();
if ((CurrentMillis - LastMillis) > 40){
      Serial.print("InputAngle:");
      Serial.print(inputAngle);
      Serial.print(",");
      // Serial.print("InputRight:");
      // Serial.print(InputRight);
      // Serial.print(",");
      Serial.print("OutputAngle:");
      Serial.print(outputAngle);
      Serial.print(",");
      // Serial.print("OutputRight:");
      // Serial.print(OutputRight);
      // Serial.print(",");
      Serial.print("MinValue:");
      Serial.print(-100);
      Serial.print(",");
      Serial.print("MaxValue:");
      Serial.print(100);
      Serial.print(",");
      Serial.print("OriginalSetPoint:");
      Serial.print(headingAngle_input);
      Serial.print(",");
       Serial.print("Setpoint:");
      Serial.print(setPointAngle);
      Serial.println(",");
      LastMillis = CurrentMillis;
    }
}
