// Motor driver Pins 
const int in1Left  = A0;
const int in2Left  = 13;
const int in1Right  = 12;
const int in2Right  = 11;

const int pwmLeft = 10;  //PWMS
const int pwmRight = 9; //PWMS

const int encLeft = 8;
const int encRight = 5;


void setup() {
  // put your setup code here, to run once:
  pinMode(encLeft,INPUT_PULLUP);
  pinMode(encRight,INPUT_PULLUP);
}
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(in1Left, HIGH);
  digitalWrite(in2Left, LOW);
  digitalWrite(in1Right, HIGH);
  digitalWrite(in2Right, LOW);
  currReadLeft = digitalRead(encLeft);
  currReadRight = digitalRead(encRight);

  Serial.print(currReadLeft);
  Serial.print(" ");
  Serial.println(currReadRight);

  analogWrite(pwmLeft, 50);
  analogWrite(pwmRight, 50);

}
