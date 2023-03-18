void mainMenu() {
                               //Menu for setting pump parameters
  Serial.print("\t\t");
  Serial.println ("Pump Parameters Menu");
  Serial.println("");
  
  Serial.println("Pump 0");                     //Pump1 parameters
  Serial.print(paraPump0[0]);
  Serial.print(rateFill[0]);
  Serial.print("\t\t");
  Serial.print(paraPump0[1]);
  Serial.print(rateDispense[0]);
  Serial.print("\t\t");
  Serial.print(paraPump0[2]);
  Serial.println(pumpVolume[0],1);
  Serial.println("");
  
  Serial.println("Pump 1");                     //Pump2 parameters
  Serial.print(paraPump1[0]);
  Serial.print(rateFill[1]);
  Serial.print("\t\t");
  Serial.print(paraPump1[1]);
  Serial.print(rateDispense[1]);
  Serial.print("\t\t");
  Serial.print(paraPump1[2]);
  Serial.println(pumpVolume[1],1);
  Serial.println("");
  
  Serial.println("Pump 2");                     //Pump3 parameters
  Serial.print(paraPump2[0]);
  Serial.print(rateFill[2]);
  Serial.print("\t\t");
  Serial.print(paraPump2[1]);
  Serial.print(rateDispense[2]);
  Serial.print("\t\t");
  Serial.print(paraPump2[2]);
  Serial.println(pumpVolume[2],1);
  Serial.println("");
}
