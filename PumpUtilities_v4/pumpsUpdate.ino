/*The pumpsUpdate source file returns a new value for a pump parameter when there is a call
 * for an edit from mainMenu.ino.
 */

int pumpsUpdate(char* paraDescription,int pumpValue){
  float x=pumpValue*0.1;                     //creates float variable which is needed for the volume
  Serial.println("");
  Serial.print(paraDescription);
  Serial.println(x,1);
  Serial.print("Enter new value: ");
  Serial.parseInt();
  while (!Serial.available());                //waits for input from Serial port
  float pumpValueFloat = Serial.parseFloat();
  int pumpFloatInt=pumpValueFloat*10;
  return (pumpFloatInt);  
}
