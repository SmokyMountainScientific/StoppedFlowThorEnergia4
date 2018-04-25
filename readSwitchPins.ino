/*  readSwitch Pins tab
 *   switch runs pump in manually
 */
 
void readFillSwitch(){       
 for(int a = 0; a<2; a++){
  switchVal[a] = digitalRead(switchPin[a]);  // reading the state of the fill switch 
  if(switchVal[a] == LOW ){
    flag = LOW;
    run = false;
    swReset[a] = true;
  }
 
   if (switchVal[a] == HIGH && swReset[a] == true) { 
    run = true; 
    swReset[a] = false; 
    setValve(0);
    digitalWrite(enablePin,LOW);   // power turned on to motor
 //   runState = true; 
    if(a ==0){   // withdraw direction
    dir = 1;
    } else {
   dir = 0;
    }
     digitalWrite(dirPin,dir);

    }
  while (switchVal[a] == HIGH && run == true) {
       swRotate(150);
       switchVal[a] = digitalRead(switchPin[a]);
       runEndStop();  // cut here? JSS
     }
     flag = LOW;
   }  // end of the "a" loop
 
  if(run == false){
    digitalWrite(enablePin,HIGH);   // stepper power turned off 
// Serial.println("reached end of readSitchPins tab");
  
  }
// flag = LOW;
} 
 
///////////////////////////////////////////////////////

/* void ISR()
  {
    flag=HIGH;
 //   Serial.print("ISR flag tripped, runState: ");
   // Serial.println(runState);
  }*/

  void swRotate(int j){
 for (int k = 0; k<j; k++){
      digitalWrite(stepPin, HIGH); 
   //   delay(1);
    delayMicroseconds(1500); 
    digitalWrite(stepPin, LOW); 
 delayMicroseconds(1500);
//delay(1);
  }
  }


