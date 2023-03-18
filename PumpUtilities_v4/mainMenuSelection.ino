/* This function organizes all the options for editing the parameters of the mainMenu
 *  
 */
 /*
void mainMenuSelection(char* menuSelection) {
  if (menuSelection == 'a') {                   //mixer pump 0 fill rate
    pumpValue = rateFill[0] * 10;             //needed for passing volume (float variable) to pumpsPara method
    pumpValue = pumpsUpdate("Mixer 0 fill rate: ", pumpValue);
    rateFill[0] = pumpValue * 0.1;
  }
  if (menuSelection == 'b') {                   //mixer pump 0 dispense rate
    pumpValue = rateDispense[0] * 10;         //needed for passing volume (float variable) to pumpsPara method
    pumpValue = pumpsUpdate("Mixer 0 dispense rate: ", pumpValue);
    rateDispense[0] = pumpValue * 0.1;        //converts variable back to integer variable
  }
  if (menuSelection == 'c') {                   //sample pump1 volume
    pumpValue = pumpVolume[0] * 10;   //converts volume (float variable) to integer variable to pass to pumpsPara method
    pumpValue = pumpsUpdate("Mixer 0 volume(mL): ", pumpValue);
    pumpVolume[0] = pumpValue * 0.1;          //converts integer back to float
  }
  if (menuSelection == 'd') {                   //mixer pump 0 cycles
    pumpValue = cyclesPump[0] * 10;
    pumpValue = pumpsUpdate("Mixer 0 cycles: ", pumpValue);
    cyclesPump[0] = pumpValue * 0.1;
  }
  if (menuSelection == 'e') {                   //pump 1 fill rate
    pumpValue = rateFill[1] * 10;
    pumpValue = pumpsUpdate("Pump 1 fill rate: ", pumpValue);
    rateFill[1] = pumpValue * 0.1;
  }
  if (menuSelection == 'f') {                   //pump 1 dispense rate
    pumpValue = rateDispense[1] * 10;
    pumpValue = pumpsUpdate("Pump 1 dispense rate: ", pumpValue);
    rateDispense[1] = pumpValue * 0.1;
  }
  if (menuSelection == 'g') {                   //pump 1 pump volume
    pumpValue = pumpVolume[1] * 10;
    pumpValue = pumpsUpdate("Pump 1 volume(mL): ", pumpValue);
    pumpVolume[1] = pumpValue * 0.1;
  }
  if (menuSelection == 'h') {                   //pump 3 fill rate
    pumpValue = rateFill[2] * 10;
    pumpValue = pumpsUpdate("Pump 2 fill rate: ", pumpValue);
    rateFill[2] = pumpValue * 0.1;
  }
  if (menuSelection == 'i') {                   //pump 3 dispense rate
    pumpValue = rateDispense[2] * 10;
    pumpValue = pumpsUpdate("Pump 2 dispense rate: ", pumpValue);
    rateDispense[2] = pumpValue * 0.1;
  }
  if (menuSelection == 'j') {                   //pump 3 volume
    pumpValue = pumpVolume[2] * 10;
    pumpValue = pumpsUpdate("Pump 2 volume(mL): ", pumpValue);
    pumpVolume[2] = pumpValue * 0.1;
  }
  if (menuSelection == 'l') {
    pumpValue = setPoint * 10;
    pumpValue = pumpsUpdate("Setpoint in degrees C: ", pumpValue);
    setPoint = pumpValue * 0.1;
  }
}
*/
