/*This function allows the user to run simple functions on individual pumps.
 *Enter only volumes less than or equal to 10.0 mL. 
*/
 void pumpsTest(){
 int menuSelection=0;
   for(int x=0;x<50;x++){                     //page feed 
   Serial.println();
   }
   Serial.println("\nPumps Test");        //menu for calibration of 3 pumps
   Serial.println("1 - Syringe Pump 1");
   Serial.println("2 - Syringe Pump 2");
   Serial.println("3 - Syringe Pump 3");
   Serial.println("4 - Exit");
   Serial.println();
   Serial.println ("Enter the number of the Item to Test.");
   Serial.parseInt();                    //clears serial
   while(!Serial.available());                  //waits for input to serial buffer
   menuSelection = Serial.parseInt();        //reads serial data for menu selection
     if (menuSelection==1){
      goPump(menuSelection);        //if menuselection ==1 test pump 1
     }
     else if (menuSelection==2) {
      goPump(menuSelection);        //if menuselection ==2 test pump 2
     }
     else if (menuSelection==3) {
      goPump(menuSelection);        //if menuselection ==3 test pump 3
     }
     else if (menuSelection==4) {
      Serial.parseInt();
      return;        //if menuselection ==4 return to main menu
     }
   Serial.parseInt();                    //clears serial
}
//                             Test a Pump
void goPump(int pumpNumber) {
  for(int n=0;n<=2;n++){                             //Gets pump calibration data
    EEPROM.get(pumpAddress,zeroMicrosec[n]);
    pumpAddress=pumpAddress+2;
    EEPROM.get(pumpAddress,maxMicrosec[n]);
    pumpAddress=pumpAddress+2;                       
  }
  for(int x=0;x<50;x++){                     //page feed 
    Serial.println();
  }
  Serial.parseInt();
  if (pumpNumber==1) pump1();                  // runs pump 1 function
  else if (pumpNumber==2) pump2();             // runs pump 2 function
  else if (pumpNumber==3) pump3();             // runs pump 3 function
}
void pump1() {
  syringePump1.attach(9);    //Attach servos to pwm pins.
  Serial.println("Pump 1: Enter Volume (0.0-10.0mL): ");
  while(!Serial.available());                  //waits for input to serial buffer
  int pumpVolume=Serial.parseFloat()*10;       //Creates an integer from a decimal variable in order to use the map() function below.
  if (pumpVolume>1000) return;
  pumpVolume=map(pumpVolume,0,100,zeroMicrosec[0],maxMicrosec[0]); //The pumpVolume is mapped to microseconds
  syringePump1.write(zeroMicrosec[0],10);     //Pump1 is sent to the 0mL position at a speed of 10
  syringePump1.wait();
  delay(100);
  syringePump1.write(pumpVolume,5);           //Pump1 draws in the input volume
  syringePump1.wait();
  delay(1000);
  syringePump1.write(zeroMicrosec[0],5);     //Pump1 dispenses the input volume
  syringePump1.wait();
  delay(100);
  syringePump1.detach();
}
void pump2() {
  syringePump2.attach(10);
  Serial.println("Pump 2: Enter Volume (0.0-10.0mL): ");
  while(!Serial.available());                  //waits for input to serial buffer
  int pumpVolume=Serial.parseFloat()*10;       //Creates an integer from a decimal variable in order to use the map() function below.
  if (pumpVolume>1000) return;
  pumpVolume=map(pumpVolume,0,100,zeroMicrosec[1],maxMicrosec[1]); //The pumpVolume is mapped to microseconds
  syringePump2.write(zeroMicrosec[1],10);     //Pump2 is sent to the 0mL position at a speed of 10
  syringePump2.wait();
  delay(100);
  syringePump2.write(pumpVolume,5);           //Pump2 draws in the input volume at a rate of 5
  syringePump2.wait();
  delay(1000);
  syringePump2.write(zeroMicrosec[1],5);     //Pump2 dispenses the input volume at a rate of 5
  syringePump2.wait();
  delay(100);
  syringePump2.detach();
}
void pump3() {
  syringePump3.attach(11); 
  Serial.println("Pump 3: Enter Volume (0.0-10.0mL): ");
  while(!Serial.available());                  //waits for input to serial buffer
  int pumpVolume=Serial.parseFloat()*10;       //Creates an integer from a decimal variable in order to use the map() function below.
  if (pumpVolume>1000) return;
  pumpVolume=map(pumpVolume,0,100,zeroMicrosec[2],maxMicrosec[2]); //The pumpVolume is mapped to microseconds
  syringePump3.write(zeroMicrosec[2],10);     //Pump3 is sent to the 0mL position at a speed of 10
  syringePump3.wait();
  delay(100);
  syringePump3.write(pumpVolume,5);           //Pump3 draws in the input volume at a rate of 5
  syringePump3.wait();
  delay(1000);
  syringePump3.write(zeroMicrosec[2],5);     //Pump3 dispenses the input volume at a rate of 5
  syringePump3.wait();
  delay(100);
  syringePump3.detach();
}
    
