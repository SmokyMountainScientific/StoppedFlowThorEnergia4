// pumpDrive tab in stoppedFlow-1DrivePump sketch


void pumpDrive(int dr, int vol){  // direction,  volume in microliters
//  int rounds;
//int dir = 0;

int minDelay = 600;                  // minimum delay time for kinetic run, was 400 
if(mode == 0){         // fill mode
  minDelay = 1500;
 // if (val == false){
 // setValve(0);}
 // else{setValve(1);}
 //setValve(valveMode);   // to reservoir
// set up pump direction 
  if (dr == 0){
  digitalWrite(dirPin,HIGH);  // set up direction  1 is inject, 0 withdraw.
} else {
  digitalWrite(dirPin,LOW);
}

} else {

//  setValve(1);    // to cell
  //  delay(500);
   digitalWrite(dirPin,LOW);  // set up direction 
}
  digitalWrite(enablePin, LOW);   // enable pump

 int stepsA = 38*vol/diam/diam;   // calibrate this

  int rounds = stepsA/10;   

  int stepsPerRound = stepsA/rounds;
 

for (int t = 0; t< rounds; t++){
  for (int u = 0; u <stepsPerRound; u++){
 digitalWrite(stepPin,HIGH);

 delayMicroseconds(minDelay); 
 digitalWrite(stepPin,LOW);
 delayMicroseconds(minDelay); 
  }
   } 
   digitalWrite(enablePin, HIGH);
   Serial.println("%");
  }

  


