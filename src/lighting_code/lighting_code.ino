#include <Encabulator.h>
#include <Wire.h>
// #include <I2C.h>   // NOTE: For reasons buried in the Encabulator.cpp file, you might want to download and use this library instead. 

// 9241082682

int loopCounter = 0;

int tempR = 0;
int tempG = 0;
int tempB = 0;

float tempX = 0.0;
float tempY = 0.0;
int score = 0;
unsigned long readSensorTimeOut;
int readSensorTimeDelay = 500; //number of ms delay of reading blocked condition before assuming card is in all the way, or of reading no card before resetting
byte finishedReading = false;
byte previousReading = false;
void setup() {               
  
  Encabulator.upUpDownDownLeftRightLeftRightBA();

  // enable some debugging on the serial port

  Encabulator.setVerbose(true);
  
  for (int i = 0 ; i < 5; i++) { 
  Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
  Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
  }
}

void loop() {

  for(int k = 1; k < 1000 ; k = k*2) {
    colorCycle(k);
  }
  if (readCard()){    
    winner(score);
  }
  
}

int readCard(){//returns true when a hole count is finished and stored in score
  if (readSensor()){//if true, means a hole or no card is detected
    if (readSensorTimeOut < millis() && previousReading){
      score = 0;
      finishedReading = false;

    }
    if (!previousReading && !finishedReading){//just detected something passing through the sensor
      score ++;
      readSensorTimeOut = millis() + readSensorTimeDelay;
      
    }
  }
  else {
    if (previousReading){
      readSensorTimeOut = millis() + readSensorTimeDelay;
    }
    if (readSensorTimeOut < millis()){
      finishedReading = true;
      return true;
    }
  }
  return false;
}
int readSensor(){
  
  
}
    
      
      

void colorCycle(int j) {
  for (int i = 1; i < 9 ; i++) { 
      if (i < 5) {
        Encabulator.stripBankB.jumpHeaderToRGB(4,0,0,0);
        Encabulator.stripBankA.jumpHeaderToRGB(i-1,0,0,0);
        Encabulator.stripBankA.jumpHeaderToRGB(i,255,0,0);
      }
      if (i >= 5) {
        Encabulator.stripBankA.jumpHeaderToRGB(4,0,0,0);
        Encabulator.stripBankB.jumpHeaderToRGB(i-5,0,0,0);
        Encabulator.stripBankB.jumpHeaderToRGB(i-4,255,0,0);
      } 
      delay(j);
  }
}

void winner (int m) {
  switch (m) {
    case 1:
    for (int i = 0 ; i < 5; i++) { 
      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
      }
    for (int i = 1; i < 10; i++) {
      Encabulator.stripBankA.jumpHeaderToRGB(1,255,0,0);
      delay(200);
      Encabulator.stripBankA.jumpHeaderToRGB(1,0,0,0);
      delay(200);
      }
    break;
    
    case 2:
    for (int i = 0 ; i < 5; i++) { 
      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
      }
    for (int i = 1; i < 10; i++) {
      Encabulator.stripBankA.jumpHeaderToRGB(2,255,0,0);
      delay(200);
      Encabulator.stripBankA.jumpHeaderToRGB(2,0,0,0);
      delay(200);
      }
    break;
    
    case 3:
    for (int i = 0 ; i < 5; i++) { 
      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
      }
    for (int i = 1; i < 10; i++) {
      Encabulator.stripBankA.jumpHeaderToRGB(3,255,0,0);
      delay(200);
      Encabulator.stripBankA.jumpHeaderToRGB(3,0,0,0);
      delay(200);
      }
    break;
    
 
 
    case 4:
    for (int i = 0 ; i < 5; i++) { 
      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
      }
    for (int i = 1; i < 10; i++) {
      Encabulator.stripBankA.jumpHeaderToRGB(4,255,0,0);
      delay(200);
      Encabulator.stripBankA.jumpHeaderToRGB(4,0,0,0);
      delay(200);
      }
    break;
    
    case 5:
    for (int i = 0 ; i < 5; i++) { 
      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
      }
    for (int i = 1; i < 10; i++) {
      Encabulator.stripBankB.jumpHeaderToRGB(1,255,0,0);
      delay(200);
      Encabulator.stripBankB.jumpHeaderToRGB(1,0,0,0);
      delay(200);
      }
    break;
    
    case 6:
    for (int i = 0 ; i < 5; i++) { 
      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
      }
    for (int i = 1; i < 10; i++) {
      Encabulator.stripBankB.jumpHeaderToRGB(2,255,0,0);
      delay(200);
      Encabulator.stripBankB.jumpHeaderToRGB(2,0,0,0);
      delay(200);
      }
    break;
    
    case 7:
    for (int i = 0 ; i < 5; i++) { 
      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
      }
    for (int i = 1; i < 10; i++) {
      Encabulator.stripBankB.jumpHeaderToRGB(3,255,0,0);
      delay(200);
      Encabulator.stripBankB.jumpHeaderToRGB(3,0,0,0);
      delay(200);
      }
    break;
    
    case 8:
    for (int i = 0 ; i < 5; i++) { 
      Encabulator.stripBankA.jumpHeaderToRGB(i,0,0,0); 
      Encabulator.stripBankB.jumpHeaderToRGB(i,0,0,0);
      }
    for (int i = 1; i < 10; i++) {
      Encabulator.stripBankB.jumpHeaderToRGB(4,255,0,0);
      delay(200);
      Encabulator.stripBankB.jumpHeaderToRGB(4,0,0,0);
      delay(200);
      }
    break;
  }
}
