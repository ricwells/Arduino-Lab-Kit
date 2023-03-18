
 /* Pumps Calibration Program
  *  This program allows you to calibrate 3 servo driven 10 mL syringe pumps by recording 
  *  their microseconds at 0 mL and 10 mL. The values are stored in EEPROM. The syringe pumps
  *  are designed from 3D printed parts (linear pump v8.stl). Standard 20 Kg 270 degree servos
  *  are used to drive BD 10 mL syringes. The program is used on the Arduino Uno platform.

   The Core Unit uses digital pins 6-13 and analog pins A4 and A5 on the Arduion Uno. 
   7(dout)(red)&8(sck)(brown)=balance & VDD(purple); 9=pump1; 10=pump2; 11=pump 3; 12=DallasTemperature sensor; 
   6=MOSFET for heater; A4 (SDA)(orange) & A5 (CL)(yellow) balance display; 13=balance tare button (green). 
   The calibration constants for the syringe pumps and balance are stored in EEPROM
   as SHORT variables.pump1=0-3;pump4-7, pump3=8-11. The calibration coeficient for 
   the balance is stored in EEPROM 12.
   All the remaining pins (2-5 and A0-A3) are available for the Experiemnt Modules. 
 */

#include <EEPROM.h>
#include <VarSpeedServo.h>
VarSpeedServo syringePump1;
VarSpeedServo syringePump2;
VarSpeedServo syringePump3;

short zeroMicrosec[3];            //variables for 0 mL in mS for position of servos (called from EEPROM)
short maxMicrosec[3];              //variables for 10 mL in mS for position of servos (called from EEPROM)
  
int menuSelection = 0;       //initializes menu selection
int pumpAddress=0;           //EEPROM pump address

void setup() {
  Serial.begin(9600);           //Activates Serial port
/*
Serial.println("1 - Clear EEPROM");        //Routine to Clear EEPROM and all calibration constants - uncomment to activate
 while (Serial.available() > 0) {          //clears buffer
    Serial.read();
    }
while(!Serial.available());                //waits for input to serial buffer
     delay(100);
  menuSelection = Serial.parseInt();       //reads serial buffer
  if (menuSelection == 1) {                //runs EEPROM Clear function
    clearEEPROM();
    }
    */
//                                 Setup pumps
  for(int n=0;n<=2;n++){                          //Initialize servos if there is no previous calibration.
    EEPROM.get(pumpAddress,zeroMicrosec[n]);               //read EEPROM zeroMicrosec1 at address 0 and assigns to zeroMicrosec(n)
    if(zeroMicrosec[n]<=1500) {
      zeroMicrosec[n]=2400;                                 
      EEPROM.put(pumpAddress,zeroMicrosec[n]);            //sets 0mL factor to default (2400) if nothing in EEPROM
    }
    else (zeroMicrosec[n]=EEPROM.get(pumpAddress,zeroMicrosec[n])); //sets 0mL factor to stored value
    pumpAddress=pumpAddress+2;                           // increments pump calibration factor by two bytes
    EEPROM.get(pumpAddress,maxMicrosec[n]);                //read EEPROM maxMicrosec1 at address 2
    if(maxMicrosec[n]<=500) {
      maxMicrosec[n]=550;
      EEPROM.put(pumpAddress,maxMicrosec[n]);              //sets 10mL pump factor to default 550 if nothing in EEPROM
    }
    else (maxMicrosec[n]=EEPROM.get(pumpAddress,maxMicrosec[n]));  // sets 10mL factor to stored value
    pumpAddress=pumpAddress+2;                          // increments pump calibration address by two bytes
  }
  
    syringePump1.attach(9);    //Attach servos to pwm pins.
    syringePump2.attach(10);
    syringePump3.attach(11);

    syringePump1.write(zeroMicrosec[0],10);     //move all syringePumps to fill position
    syringePump2.write(zeroMicrosec[1],10);
    syringePump3.write(zeroMicrosec[2],10);
    
    syringePump1.wait();
    syringePump2.wait();
    syringePump3.wait();
      
    syringePump1.detach();         //deenergize pumps
    syringePump2.detach();
    syringePump3.detach();
} 
void loop() {
  
    for(int x=0;x<50;x++){                     //page feed 
    Serial.println();
    }
  //                              Header and Menu       
  Serial.println("Pumps Calibration and Test");        
  Serial.println("1 - Pumps Calibrations");
  for(int n=0;n<=2;n++) {
  Serial.print("\tPump ");
  Serial.print(n+1);
  Serial.print(" zeroMicrosec = ");
  Serial.println(zeroMicrosec[n]);              //Prints mS values for 0mL for each pump 
  Serial.print("\tPump ");
  Serial.print(n+1);
  Serial.print(" maxMicrosec = ");
  Serial.println(maxMicrosec[n]);              //Prints mS values for 10mL for each pump
  }
  Serial.println("2 - Pumps Tests");
  Serial.println ("Enter the number of the program to run.");
  pumpAddress=0;
  Serial.parseInt();
  while (!Serial.available());                    //Test for data in the serial buffer.
     delay(100);
  menuSelection = Serial.parseInt();           //reads serial buffer
  if (menuSelection == 1) {                    //runs Pumps Calibration function
     pumpsCalibration();
    }
    else if (menuSelection==2) {             //run pumps tests
      pumpsTest();
    }
    while (Serial.available() > 0) {           //clears buffer
    Serial.read();}
}

/*
void clearEEPROM() {                          //Function to clear EEPROM and calibration constants.Deactivated above.                                             
                                              //Needs to be activated in void setup.
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    if(EEPROM.read(i) != 0)                   //skip already "empty" addresses
    {
      EEPROM.write(i, 0);                       //write 0 to address i
    }
  }
  Serial.println("EEPROM erased");
}
*/
