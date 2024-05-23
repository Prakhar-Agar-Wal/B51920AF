// #include "variablesAndIncludes.h"

void displayPWMGraph()
{
  CurrentMillis = millis();
if ((CurrentMillis - LastMillis) > 40){
      Serial.print("InputLefte:");
      Serial.print(InputLeft);
      Serial.print(",");
      Serial.print("InputRight:");
      Serial.print(InputRight);
      Serial.print(",");
      Serial.print("OutputLeft:");
      Serial.print(OutputLeft);
      Serial.print(",");
      Serial.print("OutputRight:");
      Serial.print(OutputRight);
      Serial.print(",");
      Serial.print("MinValue:");
      Serial.print(0);
      Serial.print(",");
      Serial.print("MaxValue:");
      Serial.print(900);
      Serial.print(",");
      Serial.print("SetPointLeft:");
      Serial.print(SetpointLeft);
      Serial.print(",");
       Serial.print("SetpointRight:");
      Serial.print(SetpointRight);
      Serial.println(",");
      LastMillis = CurrentMillis;
    }
}

