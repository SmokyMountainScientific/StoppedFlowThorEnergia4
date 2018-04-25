// readSerial tab, stoppedFlow-thor-Energia-3 sketch
// readSerial() subroutine



void readSerial() {

  int h;
  gotParams = false;
  boolean start = false;
  while (start == false) {
    while (Serial.available() <= 0) {
      ///////////////// read fill switch ///////////////
      if (flag) {
       // Serial.println("reading fill switch");
        readFillSwitch();
      }
    }
    if (Serial.available() > 0) {
      h = Serial.read();
    }
    if (h == '*') {  // indicates GUI seeking connection 
      Serial.println('&'); // response to gui
      h = 0;
    }

    ///////////////////////////////////////////////////////////
    if (h == '&') {  // GUI prepared to send command information
      start = true;
    }
  }  // end of while start is false loop

    Serial.flush();
    ////   Get mode /////////////
    Serial.println("mode (0; fill, 1; trigger, 2; run): ");
    while (Serial.available() <= 0) { }
    if (Serial.available() > 0) {
      h = Serial.parseInt();  // set mode
      Serial.print("mode: ");
      Serial.println(h);
    }
    mode = h;

    if (mode != 1) {     // when mode is 1, gui should not be contacting pumps
      Serial.println("Volume: ");
      while (Serial.available() <= 0) { }
      if (Serial.available() > 0) {
        h = Serial.parseInt();  // set volA
        Serial.print("microliters: ");
        Serial.println(h);
      }
      microliters = h;
    }
    if (mode == 2) {
      Serial.println("Number of spectra: ");
      while (Serial.available() <= 0) { }
      if (Serial.available() > 0) {
        h = Serial.parseInt();  // set spectra
        Serial.print("spectra: ");
        Serial.println(h);
      }

      spectra = h;
      for (int p = 0; p < spectra - 1; p++) {
        Serial.println("acquisition time ");

        while (Serial.available() <= 0) { }
        if (Serial.available() > 0) {
          h = Serial.parseInt();  // set total time
          Serial.print("entered time for acq ");
          Serial.print(p);
          Serial.print(": ");
          Serial.println(h);
        }
        timingDelay[p] = h;
      }
      setValve(1);
      dir = 1;
    } // end of mode is 2 loop
    
    if (mode == 0) {    // set pump direction
      Serial.println("direction (0; withdraw, 1; inject): ");
      while (Serial.available() <= 0) { }
      if (Serial.available() > 0) {
        h = Serial.parseInt();  // set direction
        Serial.println(h);
      }
      dir = h;

      //////////////////// set valve direction
      Serial.println("valve direction (0; reservoir, 1; cell): ");
      while (Serial.available() <= 0) { }
      if (Serial.available() > 0) {
        h = Serial.parseInt();  // set direction
        Serial.println(h);
        int shiznit = h;
        setValve(shiznit);
      }  // end of valve loop

    }  // end of mode = 0 loop
///////////////  initiate run   ////////////////
   Serial.println("enter '999' to initiate run");
  while (Serial.available() <= 0) {
  }
  if (Serial.available() > 0) {
    h = Serial.parseInt();
  }
  if (h == 999) {
    Serial.println("run started");
    if (mode == 2 || mode == 0) { // if it is inject or kinetic run
      pumpDrive(dir, microliters);
     }
  }

}  // end of readSerial loop




