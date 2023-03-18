

/*When the pumpVolume is over 10mL the pump needs to pump several times. 
 * The volRemainder function takes the programmed volume and determines the remainder after the required number
 * of complete 10mL cycles. It then maps this volume to the calibration values of the pump for 0 and 10mL.
 * It returns the microsecond value to complete the dispensation after the required number of complete cycles.
 */
int volRemainder(float pumpV,int zeroM,int maxM) {  //returns remaining volume after cyclesPump in microseconds
  int x=pumpV*10;                           //creates an integer for the volume from the float volume
  x=x%100;                                     //calculates the remainder after dividing by 10ml times 10
  x=map(x,0,100,zeroM,maxM);    //maps the remainder to 10ml times 10 to the calibration points  
  return x;                                   //returns the remainder in microseconds after so many conplete 10mL cycles
}

void runPumps(char menuSelect,int cycleIndex[],int n,int remainder[],int m,int zeroMicro[],int o,int maxMicro[],int p,int fillRate[],int q, int dispRate[],int r){
  Serial.println("menuSelect");
  Serial.println(menuSelect);
  syringePump0.attach(9);
  syringePump1.attach(10);
  syringePump2.attach(11);
  syringePump0.write(zeroMicrosec[0],10);     //move all syringePumps to fill position or 0 mL
  syringePump0.wait();
  syringePump1.write(zeroMicrosec[1],10);
  syringePump1.wait();
  syringePump2.write(zeroMicrosec[2],10);
  syringePump2.wait();
  delay(1000);
  
  bool pumpDir0=true;
  bool pumpDir1=true;
  bool pumpDir2=true;
  int index0=0;
  int index1=0;
  int index2=0;
  int indexGrand=cycleIndex[0]+cycleIndex[1]+cycleIndex[2];
  int indexMark=0;

  //the index only applies to pumps that are running. All other pump indexes need to be set to zero
  if (menuSelect=='a' || menuSelect=='d' || menuSelect=='e' || menuSelect=='g') {
    index0=cycleIndex[0];
  }
  if (menuSelect=='b' || menuSelect=='d' || menuSelect=='f' || menuSelect=='g') {
    index1=cycleIndex[1];
  }
  if (menuSelect=='c' || menuSelect=='e' || menuSelect=='f' || menuSelect=='g') {
    index2=cycleIndex[2];
  }

  //indexMark changes whether 1, 2, or 3 pumps are running at the same time
  if (menuSelect=='a' || menuSelect=='b' || menuSelect=='c') {  
    indexMark=-1;
  }
  else if (menuSelect=='d' || menuSelect=='e' || menuSelect=='f') {
    indexMark=-2;
  }
  else if (menuSelect=='g') {
    indexMark=-3;
  }
  
  while (indexGrand>indexMark) {
    if (menuSelect=='a' || menuSelect=='d' || menuSelect=='e' || menuSelect=='g') {
      if (!syringePump0.isMoving() && index0>-1) {
        if (index0>=1) {
          if (pumpDir0==true) {
            syringePump0.write(maxMicro[0],fillRate[0]);
            pumpDir0=false;
          }  
          else if (pumpDir0==false) {
            syringePump0.write(zeroMicro[0],dispRate[0]);
            pumpDir0=true;
            index0=index0-1;
          }
        }
        else if (index0==0) {
            if (pumpDir0==true) {
              syringePump0.write(remainder[0],fillRate[0]);
              pumpDir0=false;
            }
            else if (pumpDir0==false) {
              syringePump0.write(zeroMicro[0],dispRate[0]);
              if (syringePump0.readMicroseconds()==zeroMicro[0]) {
                index0=index0-1;
                syringePump0.detach();
              }
            }
        }
        indexGrand=index0+index1+index2;
        Serial.println("Mark1");
        Serial.println("index0");
        Serial.println(index0);
        Serial.println("index1");
        Serial.println(index1);
        Serial.println("indexMark");
        Serial.println(indexMark);
        Serial.println("indexGrand");
        Serial.println(indexGrand);
      }
    }

    if (menuSelect=='b' || menuSelect=='d' || menuSelect=='f' || menuSelect=='g') {
      if (!syringePump1.isMoving() && index1>-1) {
        if (index1>=1) {
          if (pumpDir1==true) {
            syringePump1.write(maxMicro[1],fillRate[1]);
            pumpDir1=false;
          }  
          else if (pumpDir1==false) {
            syringePump1.write(zeroMicro[1],dispRate[1]);
            pumpDir1=true;
            index1=index1-1;
          }
        }
        else if (index1==0) {
            if (pumpDir1==true) {
              syringePump1.write(remainder[1],fillRate[1]);
              pumpDir1=false;
            }
            else if (pumpDir1==false) {
              syringePump1.write(zeroMicro[1],dispRate[1]);
              if (syringePump1.readMicroseconds()==zeroMicro[1]) {
                index1=index1-1;
                syringePump1.detach();
              }
            }
        }
        indexGrand=index0+index1+index2;
        Serial.println("Mark2");
        Serial.println("index0");
        Serial.println(index0);
        Serial.println("index1");
        Serial.println(index1);
        Serial.println("indexMark");
        Serial.println(indexMark);
        Serial.println("indexGrand");
        Serial.println(indexGrand);
      }
    }

    if (menuSelect=='c' || menuSelect=='e' || menuSelect=='f' || menuSelect=='g') {
      if (!syringePump2.isMoving() && index2>-1) {
        if (index2>=1) {
          if (pumpDir2==true) {
            syringePump2.write(maxMicro[2],fillRate[2]);
            pumpDir2=false;
          }  
          else if (pumpDir2==false) {
            syringePump2.write(zeroMicro[2],dispRate[2]);
            pumpDir2=true;
            index2=index2-1;
          }
        }
        else if (index2==0) {
            if (pumpDir2==true) {
              syringePump2.write(remainder[2],fillRate[2]);
              pumpDir2=false;
            }
            else if (pumpDir2==false) {
              syringePump2.write(zeroMicro[2],dispRate[2]);
              if (syringePump2.readMicroseconds()==zeroMicro[2]) {
                index2=index2-1;
                syringePump2.detach();
              }
            }
        }
        indexGrand=index0+index1+index2;
      }
    }
  } 
}
