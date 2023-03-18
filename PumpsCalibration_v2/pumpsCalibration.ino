/*This function runs routines for zeroing the syringe pump plungers for each pump
 * by incrementing the microseconds of the servos to match the end of the syringe.
 * It also sets the position of the plunger for 10 mL for each pump
 *by incrementing the microseconds of the servos to match the 10 mL line.
*/
void pumpsCalibration() {
  Serial.parseInt();
  for(int x=0;x<50;x++){                     //page feed 
    Serial.println();
    }
//                          Header and Menu
  Serial.println("\nPumps Calibration");
  Serial.println("1 - Syringe Pump 1");
  Serial.println("2 - Syringe Pump 2");
  Serial.println("3 - Syringe Pump 3");
  Serial.println("Any key - Exit");
  Serial.println();
  Serial.println ("Enter the number of the Item to Calibrate.");
    while (!Serial.available());
    delay(50);
    int menuSelection = Serial.parseInt();    //reads serial data for menu selection
    if (menuSelection==1){
      servoCalibration(menuSelection);        //if menuselection ==1 calibrate pump 1
    }
    else if (menuSelection==2) {
      servoCalibration(menuSelection);        //if menuselection ==2 calibrate pump 2
    }
    else if (menuSelection==3) {
      servoCalibration(menuSelection);        //if menuselection ==3 calibrate pump 3
    }
  menuSelection=0;
}
//                            Function to move servos to 0 and 10 mL
void servoCalibration(int pump){          //pump calibration function with pump number parameter
    int y;
    int servoIncrement=2275;                   //variable to initiate position of servo to start calibration
    bool z=true;
    for(int x=0;x<50;x++){                //page feed 
      Serial.println();    }
//                    Menu to move servo to position 0 mL   
    Serial.print("Pump ");
    Serial.print(pump);
    Serial.println(" Zero");
    Serial.println("1 - Plunger forward 10 usec");
    Serial.println("2 - Plunger back 10 usec");
    Serial.println("3 - Finish");
    Serial.parseInt();                    //clears serial
//                              zero calibrate pump 1
      if (pump==1) {
        syringePump1.attach(9);             
        syringePump1.write(servoIncrement,10);  //moves servo 1 to position servoIncrement at a rate of 10
        syringePump1.wait();
        while (z) {
          while(!Serial.available());            //waits for input to serial buffer
          y=Serial.parseInt();
          if (y==1) {    // if serial input equals 1 it increases the servo postion by 10 microsec
            servoIncrement=servoIncrement+10;
            syringePump1.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==2) {  //if serial input equals 2 it decreases servo position by 10 usec.
            servoIncrement=servoIncrement-10;
            syringePump1.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==3) {
            z=false;
            Serial.parseInt();              //Sets z false to Finish While loop.
          }
          Serial.parseInt();
       }
//                          Option to store 0 mL calibration for pump1                           
        Serial.println("1 - Accept");         //prompt to accept or decline changes to zeroCalibration for Pump 1
            Serial.println(servoIncrement);
            Serial.println("Any other key - Abort");
            Serial.parseInt();
            while (!Serial.available());
            if (Serial.parseInt()==1) {
                zeroMicrosec[0]=servoIncrement;
                EEPROM.put(0,zeroMicrosec[0]);        //if Accept assigns milliseconds for positition 0mL
           }
           Serial.parseInt();                             
         tenmLCalibration(pump);                  //run 10mL Calibration at 750 microsec
         syringePump1.write(zeroMicrosec[0],10);
         syringePump1.wait();
         syringePump1.detach();
         Serial.parseInt();
      }
//                              zero calibrate pump 2
      else if (pump==2) {
        syringePump2.attach(10);             
        syringePump2.write(servoIncrement,10);  //moves servo 2 to position servoIncrement at a rate of 10
        syringePump2.wait();
        while (z) {
          while(!Serial.available());                  //waits for input to serial buffer
          y=Serial.parseInt();
          if (y==1) {    // if serial input equals 1 it increases the servo postion by 10 microsec
            servoIncrement=servoIncrement+10;
            syringePump2.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==2) {  //if serial input equals 2 it decreases servo position by 10 usec.
            servoIncrement=servoIncrement-10;
            syringePump2.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==3) {
            z=false;
            Serial.parseInt();
          }
        }                                   
//                     Option to save 0 mL calibration for pump2
            Serial.println("1 - Accept");         //prompt to accept or decline changes to zeroCalibration for Pump 1
            Serial.println(servoIncrement);
            Serial.println("Any other key - Abort");
            Serial.parseInt();
            while (!Serial.available());
            if (Serial.parseInt()==1) {
                zeroMicrosec[1]=servoIncrement;
                EEPROM.put(4,zeroMicrosec[1]);        //if Accept assigns milliseconds for positition 0mL
             }
            Serial.parseInt();                             
           tenmLCalibration(pump);                  //run 10mL Calibration at 750 microsec         
         syringePump2.write(zeroMicrosec[1],10);
         syringePump2.wait();
         syringePump2.detach();
         Serial.parseInt();
      }
//                              zero calibrate pump 3
      else if (pump==3) {
        syringePump3.attach(11);             
        syringePump3.write(servoIncrement,10);  //moves servo 2 to position servoIncrement at a rate of 10
        syringePump3.wait();
        while (z) {
          while(!Serial.available());                  //waits for input to serial buffer
          y=Serial.parseInt();
          if (y==1) {    // if serial input equals 1 it increments the servo postion by 10 microsec
            servoIncrement=servoIncrement+10;
            syringePump3.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==2) {  //if serial input equals 2 increments servo position back 10 usec.
            servoIncrement=servoIncrement-10;
            syringePump3.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==3) {
            z=false;
            Serial.parseInt();
          }
        }
//                          Option to store 0 mL calibration for pump3   
            Serial.println("1 - Accept");         //prompt to accept or decline changes to zeroCalibration for Pump 1
            Serial.println(servoIncrement);
            Serial.println("Any other key - Abort");
            Serial.parseInt();
            while (!Serial.available());
            if (Serial.parseInt()==1) {
                zeroMicrosec[2]=servoIncrement;
                EEPROM.put(8,zeroMicrosec[2]);        //if Accept assigns milliseconds for positition 0mL
             }
             Serial.parseInt();                             
           tenmLCalibration(pump);                  //run 10mL Calibration at 750 microsec        
         syringePump3.write(zeroMicrosec[2],10);
         syringePump3.wait();
         syringePump3.detach();
         Serial.parseInt(); 
       }
}
//                       10 mL calibration
void tenmLCalibration(int pumpNumber) {
  int y;
  int servoIncrement=750;                   //variable to initiate position of servo to start calibration
  bool z=true;
  for(int x=0;x<50;x++){                     //page feed 
    Serial.println();    }
//                        Menu for 10 mL pump calibration
  Serial.print("Pump ");
  Serial.print(pumpNumber);
  Serial.println(" 10 mL");
  Serial.println("1 - Plunger forward 10 usec");
  Serial.println("2 - Plunger back 10 usec");
  Serial.println("3 - Finish");
//                              10 mL calibrate pump 1
    if (pumpNumber==1) {
      syringePump1.attach(9);             
      syringePump1.write(servoIncrement,10);  //moves servo 1 to position servoIncrement at a rate of 10
      syringePump1.wait();
      while (z) {
        while(!Serial.available());                  //waits for input to serial buffer
        y=Serial.parseInt();
        if (y==1) {    // if serial input equals 1 it increases the servo postion by 10 microsec
          servoIncrement=servoIncrement+10;
          syringePump1.write(servoIncrement,10);
          Serial.println(servoIncrement);
          Serial.parseInt();                    //clears serial
          }
        else if (y==2) {  //if serial input equals 2 it decreases servo position by 10 usec.
          servoIncrement=servoIncrement-10;
          syringePump1.write(servoIncrement,10);
          Serial.println(servoIncrement);
          Serial.parseInt();                    //clears serial
        }
        else if (y==3) {
            z=false;
            Serial.parseInt();
          }
        Serial.parseInt();
      }
//                          Option to store 10 mL calibration for pump1                                     
          Serial.println("1 - Accept");         //prompt to accept or decline changes to zeroCalibration for Pump 1
          Serial.println(servoIncrement);
          Serial.println("Any other key - Abort");
          Serial.parseInt();
          while (!Serial.available());
          if (Serial.parseInt()==1) {
            maxMicrosec[0]=servoIncrement;
            EEPROM.put(2,maxMicrosec[0]);        //if Accept assigns milliseconds for positition 10mL
         }                             
      }
//                              10mL calibrate pump 2
      else if (pumpNumber==2) {
        syringePump2.attach(10);             
        syringePump2.write(servoIncrement,10);  //moves servo 2 to position servoIncrement at a rate of 10
        while (z) {
          while(!Serial.available());                  //waits for input to serial buffer
          y=Serial.parseInt();
          if (y==1) {    // if serial input equals 1 it increments the servo postion by 10 microsec
            servoIncrement=servoIncrement+10;
            syringePump2.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==2) {  //if serial input equals 2 increments servo position back 10 usec.
            servoIncrement=servoIncrement-10;
            syringePump2.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==3) {
            z=false;
            Serial.parseInt();
          }
          Serial.parseInt();
      }
//                          Option to store 10 mL calibration for pump2                                    
            Serial.println("1 - Accept");         //prompt to accept or decline changes to zeroCalibration for Pump 1
            Serial.println(servoIncrement);
            Serial.println("Any other key - Abort");
            Serial.parseInt();
            while (!Serial.available());
            if (Serial.parseInt()==1) {
                maxMicrosec[1]=servoIncrement;
                EEPROM.put(6,maxMicrosec[1]);        //if Accept assigns milliseconds for positition 10mL
             }
             Serial.parseInt();                             
      }
//                              10mL calibrate pump 3
      else if (pumpNumber==3) {
        syringePump3.attach(11);             
        syringePump3.write(servoIncrement,10);  //moves servo 3 to position servoIncrement at a rate of 10
        syringePump3.wait();
        while (z) {
          while(!Serial.available());                  //waits for input to serial buffer
          y=Serial.parseInt();
          if (y==1) {    // if serial input equals 1 it increases the servo postion by 10 microsec
            servoIncrement=servoIncrement+10;
            syringePump3.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==2) {  //if serial input equals 2 it decreases servo position back 10 usec.
            servoIncrement=servoIncrement-10;
            syringePump3.write(servoIncrement,10);
            Serial.println(servoIncrement);
            Serial.parseInt();                    //clears serial
          }
          else if (y==3) {
            z=false;
            Serial.parseInt();
          }
          Serial.parseInt();
      }
//                          Option to store 10 mL calibration for pump3                                    
            Serial.println("1 - Accept");         //prompt to accept or decline changes to zeroCalibration for Pump 1
            Serial.println(servoIncrement);
            Serial.println("Any other key - Abort");
            Serial.parseInt();
            while (!Serial.available());
            if (Serial.parseInt()==1) {
                maxMicrosec[2]=servoIncrement;
                EEPROM.put(10,maxMicrosec[2]);        //if Accept assigns milliseconds for positition 10mL
             }
             Serial.parseInt();                             
         }
}
