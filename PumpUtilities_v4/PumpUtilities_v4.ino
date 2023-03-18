/* PumpUtilities is a basic pump sketch that allows you program all 3 syringe pumps. It
    retrieves the pump calibration values from EEPROM. Each pump can be programmed for
    fill and dispense rate of a programmed volume. The pumps can be run individually or
    all at once. Volumes greater than 10mL require multiple cycles.

  The Core Unit uses digital pins 6-13 and analog pins A4 and A5 on the Arduion Uno.
  balance: 7(dout)(red)& 8(sck)(brown) & VDD(purple) & VCC(white) & grd(black;
  all pumps: 7v external power supply; red(+), black(-)
  9=pump1: 9(control)(middle); pump2: 10(control)(middle); pump3: 11(control)(middle);
  DallasTemperature sensor: 12(control);    MOSFET control pin for heater: 6(control);
  heater: 7v external power supply through MOSFET
  balance display: A4 (SDA)(orange) & A5 (CL)(yellow) & VCC(red) & grd(black);
  balance = 13 tare button (green) & grd(black).
  The calibration constants for the syringe pumps and balance are stored in EEPROM
  as SHORT variables.pump1=0-3;pump4-7, pump3=8-11. The calibration coeficient for
  the balance is stored in EEPROM 12.
  All the remaining pins (2-5 and A0-A3) are available for the Experiemnt Modules.
*/

#include <EEPROM.h>                  //EEPROM library
#include <VarSpeedServo.h>           //servo library
#define DEFAULT_PULSE_WIDTH     // default pulse width when servo is attached
void mainMenu(void);
void mainMenuSelection(char*);
VarSpeedServo syringePump0;
VarSpeedServo syringePump1;
VarSpeedServo syringePump2;

int zeroMicrosec[3];            //variables for 0 mL in mS for position of servos (called from EEPROM)
int maxMicrosec[3];              //variables for 10 mL in mS for position of servos (called from EEPROM)

int pumpAddress = 0;
int rateDispense[3] = {5, 5, 5}; //default dispense rate
int rateFill[3] = {5, 5, 5}; //default fill rate
float pumpVolume[3] = {0.0, 0.0, 0.0}; //default pump volume
int cyclesPump[3] = {0, 0, 0}; //initialize cycle index
int remainder[3] = {0, 0, 0}; //exess remainder over full stroke of 10mL pump
char* paraPump0[3] {"a-Pump0 fill rate: ", "b-Pump0 dispense rate: ", "c-Pump0 volume: "};
char* paraPump1[3] {"d-Pump2 fill rate: ", "e-Pump1 dispense rate: ", "f-Pump1 volume: "};
char* paraPump2[3] {"g-Pump3 fill rate: ", "h-Pump2 dispense rate: ", "i-Pump2 volume: "};
char* menuSelection;           //key to select item in determining parameters for all pumps
char* cont;                   //key for determining which pumps to run
int pumpValue;              //parameter value to be updated

void pageFeed() {
  for (int xx = 0; xx < 50; xx++) {             //serial I/O page feed
    Serial.println();
  }
}
void setup() {
  Serial.begin(9600);           //Activates Serial port

  for (int n = 0; n <= 2; n++) { //Gets pump calibration values from EEPROM for all 3 servo pumps
    EEPROM.get(pumpAddress, zeroMicrosec[n]);              //read EEPROM zeroMicrosec[n] at address n
    (zeroMicrosec[n] = EEPROM.get(pumpAddress, zeroMicrosec[n])); //assigns to zeroMicrosec[n] to stored uS value for 0 mL
    pumpAddress = pumpAddress + 2;                       // increments pump calibration factor by two bytes for maxMicrosec[n]
    EEPROM.get(pumpAddress, maxMicrosec[n]);               //read EEPROM maxMicrosec[n] at new address
    (maxMicrosec[n] = EEPROM.get(pumpAddress, maxMicrosec[n])); // assigns to maxMicrosec(n) to stored uS value for 10 mL
    pumpAddress = pumpAddress + 2;                      // increments pump calibration address by two bytes for next servo pump
  }

  Serial.println("WARNING!  Pumps are about to reset and may experience rapid movement.");
  Serial.println("Remove all tubes from any solutions and put in waste.");
  Serial.println("Enter any key to continue.");
  while (!Serial.available());                //waits for input from Serial port

  syringePump0.attach(9);    //Attach servos to pwm pins.
  syringePump1.attach(10);
  syringePump2.attach(11);
  syringePump0.write(zeroMicrosec[0], 10);    //move all syringePumps to fill position or 0 mL
  syringePump0.wait();
  syringePump1.write(zeroMicrosec[1], 10);
  syringePump1.wait();
  syringePump2.write(zeroMicrosec[2], 10);
  syringePump2.wait();
  syringePump0.detach();
  syringePump1.detach();
  syringePump2.detach();
}

void loop() {
  pageFeed();
  mainMenu();

  Serial.println ("Enter the parameter letter to edit or Enter z to enter the Run menu");
  Serial.parseInt();
  while (!Serial.available());                //waits for input from Serial port
  menuSelection = Serial.read();
  Serial.parseInt();
  if (menuSelection == 'a') {                   //pump 0 fill rate
    pumpValue = rateFill[0] * 10;             //needed for passing volume (float variable) to pumpsPara method
    pumpValue = pumpsUpdate("Pump1 fill rate: ", pumpValue);
    rateFill[0] = pumpValue * 0.1;
  }
  if (menuSelection == 'b') {                   //pump 0 dispense rate
    pumpValue = rateDispense[0] * 10;         //needed for passing volume (float variable) to pumpsPara method
    pumpValue = pumpsUpdate("Pump1 dispense rate: ", pumpValue);
    rateDispense[0] = pumpValue * 0.1;        //converts variable back to integer variable
  }
  if (menuSelection == 'c') {                   //pump 0 volume
    pumpValue = pumpVolume[0] * 10;   //converts volume (float variable) to integer variable to pass to pumpsPara method
    pumpValue = pumpsUpdate("Pump1 volume(mL): ", pumpValue);
    pumpVolume[0] = pumpValue * 0.1;          //converts integer back to float
  }
  if (menuSelection == 'd') {                   //pump 2 fill rate
    pumpValue = rateFill[1] * 10;
    pumpValue = pumpsUpdate("Pump2 fill rate: ", pumpValue);
    rateFill[1] = pumpValue * 0.1;
  }
  if (menuSelection == 'e') {                   //pump 2 dispense rate
    pumpValue = rateDispense[1] * 10;
    pumpValue = pumpsUpdate("Pump2 dispense rate: ", pumpValue);
    rateDispense[1] = pumpValue * 0.1;
  }
  if (menuSelection == 'f') {                   //pump 2 volume
    pumpValue = pumpVolume[1] * 10;
    pumpValue = pumpsUpdate("Pump2 volume(mL): ", pumpValue);
    pumpVolume[1] = pumpValue * 0.1;
  }
  if (menuSelection == 'g') {                   //pump 3 fill rate
    pumpValue = rateFill[2] * 10;
    pumpValue = pumpsUpdate("Pump3 fill rate: ", pumpValue);
    rateFill[2] = pumpValue * 0.1;
  }
  if (menuSelection == 'h') {                   //pump 3 dispense rate
    pumpValue = rateDispense[2] * 10;
    pumpValue = pumpsUpdate("Pump3 dispense rate: ", pumpValue);
    rateDispense[2] = pumpValue * 0.1;
  }
  if (menuSelection == 'i') {                   //pump 3 volume
    pumpValue = pumpVolume[2] * 10;
    pumpValue = pumpsUpdate("Pump3 volume(mL): ", pumpValue);
    pumpVolume[2] = pumpValue * 0.1;
  }
  if (menuSelection == 'z') {   //initialize the running of all the pumps
    pageFeed();

    Serial.println();
    Serial.println("a - Run pump1");
    Serial.println("b - Run pump2");
    Serial.println("c - Run pump3");
    Serial.println("d - Run pumps 1 & 2");
    Serial.println("e - Run pumps 1 & 3");
    Serial.println("f - Run pumps 2 & 3");
    Serial.println("g - Run all pumps");
    Serial.println("z - Abort");

    while (Serial.available() > 0) {    //clear Serial buffer
      Serial.read();
    }
    while (Serial.available() == 0);   //wait for something from the Serial buffer
    char cont = Serial.read();         //read the first byte from the serial buffer

    //Takes the pump volume for each pump and creates a variable for the number of complete 10mL cycles
    //and a variable for a volume in excess of a complete 10mL cycle
    for (int x = 0; x <= 2; x++) {
      cyclesPump[x] = pumpVolume[x] * 0.1; //function to convert float pumpvolume to an integer that represents the number of cycles
      remainder[x] = volRemainder(pumpVolume[x], zeroMicrosec[x], maxMicrosec[x]); // function returns remaining volume after cyclesPump in microseconds
    }

    if (cont == 'z') {                 //abort run
    }
//The following statements call the runPumps function with the given parameters
    if (cont == 'a') {                 //run pump0 only
      runPumps(cont, cyclesPump, 3, remainder, 3, zeroMicrosec, 3, maxMicrosec, 3, rateFill, 3, rateDispense, 3);
    }

    if (cont == 'b') {                 //run pump1 only
      runPumps(cont, cyclesPump, 3, remainder, 3, zeroMicrosec, 3, maxMicrosec, 3, rateFill, 3, rateDispense, 3);
    }

    if (cont == 'c') {                 //run pump2 only
      runPumps(cont, cyclesPump, 3, remainder, 3, zeroMicrosec, 3, maxMicrosec, 3, rateFill, 3, rateDispense, 3);
    }

    if (cont == 'd') {                 //run pump0 and pump1 only
      runPumps(cont, cyclesPump, 3, remainder, 3, zeroMicrosec, 3, maxMicrosec, 3, rateFill, 3, rateDispense, 3);
    }

    if (cont == 'e') {                 //run pump0 and pump2 only
      runPumps(cont, cyclesPump, 3, remainder, 3, zeroMicrosec, 3, maxMicrosec, 3, rateFill, 3, rateDispense, 3);
    }

    if (cont == 'f') {                 //run pump1 and pump2 only
      runPumps(cont, cyclesPump, 3, remainder, 3, zeroMicrosec, 3, maxMicrosec, 3, rateFill, 3, rateDispense, 3);
    }

    if (cont == 'g') {                 //run all pumps
      runPumps(cont, cyclesPump, 3, remainder, 3, zeroMicrosec, 3, maxMicrosec, 3, rateFill, 3, rateDispense, 3);
    }
    syringePump0.detach();
    syringePump1.detach();
    syringePump2.detach();
  }
}
