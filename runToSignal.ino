// RunToSignal tab
// used with "to signal" mode
void runToSignal(){   // working on 3/18/14
  /*
        float addVol = 200*Area[pump]/160/pitch;    // determine volume added or withdrawn
     while(runState == true) {       //fill syringe until stop signal
         rotate(200); 
        ////// calculate uL added ///////

        readP();                                 // read sensor value
        Serial.print(addVol);
        Serial.print(",");
        Serial.print(sensorValue);
        Serial.print(",");
        Serial.println("0");  // command indicates mid-run  
        status2();
  //   HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;   
}
}

////////// runToVol

// RunToVolume tab
// used when run mode is "to volume"

void runToVol(){

  int jogs = steps/200; 

  float addVol = 200*Area[pump]/160/pitch;    // determine volume added or withdrawn
 

boolean runState;
    while(runState == true) {
    for (int k = 0; k<jogs; k++) {
      rotate(200);
      readP();                                 // read sensor value
      Serial.print(addVol);
      Serial.print(",");
      Serial.print(sensorValue);
      if (k == jogs-1) {       // last rotation
        Serial.println(",1"); // 1 command indicates end of volume
        runState = false;
        Serial.println("99999,0,0"); 
        }
      else {
        Serial.println(",0"); // 0 command indicates middle of injection
        }
    }
  }
}


 /////////////////////

 // reset_status tab

void status(){
   int endQ = digitalRead(endStop);          // read limit switch
   if (endQ == HIGH){
  run = false; 
//    runState = false;
    //   HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ; 
    Serial.println("99999,0,2");       // end signal added 10/22/14
  }
}

void status2(){
  boolean rsStatus;
  if(Serial.available()>0) {
    rsStatus = Serial.find("%");            // search for stop signal  %
  }
  int endQ = digitalRead(endStop);          // read limit switch
  if (rsStatus == true){
  run = false;
//    runState = false;
    //   HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ; 
    Serial.println("99999,0,2");       // end signal added 10/22/14
  }
  */
}

/////////////////


 
