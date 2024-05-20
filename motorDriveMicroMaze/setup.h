void _main_setup(){
  pinMode(in1Left, OUTPUT);
  pinMode(in2Left, OUTPUT);
  pinMode(in1Right, OUTPUT);
  pinMode(in2Right, OUTPUT);
  pinMode(pwmLeft, OUTPUT);
  pinMode(pwmRight, OUTPUT);
  digitalWrite(pwmLeft, LOW);
  digitalWrite(pwmRight, LOW);

//PID 
 myPIDLeft.SetMode(AUTOMATIC);
  myPIDRight.SetMode(AUTOMATIC);
  anglePID.SetMode(AUTOMATIC);
  myPIDLeft.SetSampleTime(10);
  myPIDRight.SetSampleTime(10);
  anglePID.SetSampleTime(10);
  anglePID.SetMode(AUTOMATIC);
  anglePID.SetOutputLimits(-200,200);

  // pinMode(encLeft1, INPUT_PULLUP);
  // pinMode(encLeft2, INPUT_PULLUP);
  // pinMode(encRight1, INPUT_PULLUP);
  // pinMode(encRight2, INPUT_PULLUP);

  pinMode(iRLeftfront, INPUT);
  pinMode(iRLeftside, INPUT);
  pinMode(iRRightfront, INPUT);
  pinMode(iRRightside, INPUT);
}

