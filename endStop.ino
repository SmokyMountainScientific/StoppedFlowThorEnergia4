// endStop tab
void  runEndStop(){

    endFlag = false;
//    Serial.println("End stop routine");
//  for (int p = 0; p<2; p++){
int p = 1;           // problem with p=0 pin
  int q = digitalRead(endStop[p]);
  if (q == HIGH){
    Serial.print("dir 1: ");
   Serial.println(dir);
    int newDir = (dir+1)%2;
            // run the stop routine on pump p
/*   Serial.println("End stop reached");
   Serial.print("dir 2: ");
   Serial.print(dir);
   Serial.print(", newDir: ");
   Serial.println(newDir); */
  while (q == HIGH){
    digitalWrite(dirPin,newDir); 

  for(int k = 0; k<50; k++){
   digitalWrite(stepPin,HIGH);
 delayMicroseconds(1500); 
 digitalWrite(stepPin,LOW);
 delayMicroseconds(1500); 
   }
  q = digitalRead(endStop[p]);
  }                                   // end of while q is high loop
  run = false; 
//  Serial.println("run stopped by endstop"); 
  } // end of if q high loop

 
 // }  // reinstate for p = 0 pin working
   
}

