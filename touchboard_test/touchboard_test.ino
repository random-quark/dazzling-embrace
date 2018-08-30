// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// the electrode to monitor for proximity
#define PROX_ELECTRODE 0


void setup() {
  Serial.begin(57600);
  Serial.println("Tree hugging test");

  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  // slow down some of the MPR121 baseline filtering to avoid 
  // filtering out slow hand movements
  MPR121.setRegister(MPR121_NHDF, 0x01); //noise half delta (falling)
  MPR121.setRegister(MPR121_FDLF, 0x3F); //filter delay limit (falling)   

}

void loop() {
  readTouchInputs();
}

void readTouchInputs(){
    
  MPR121.updateAll();

//  for (int i=1; i < 4; i++) {
//    int touchReading = MPR121.digitalRead(i);
//    Serial.print("Touch data for: ");
//    Serial.print(i);
//    Serial.print(" ");
//    Serial.print(touchReading)
//  };
//
//  for (int i=1; i < 12; i++){  // Check which electrodes were pressed
//    if(MPR121.isNewTouch(i)){
//        //pin i was just touched
//        Serial.print("pin ");
//        Serial.print(i);
//        Serial.println(" was just touched");        
//    }else{
//      if(MPR121.isNewRelease(i)){
//        Serial.print("pin ");
//        Serial.print(i);
//        Serial.println(" is no longer being touched");
//        digitalWrite(LED_BUILTIN, LOW);
//     } 
//    }
//  }

  Serial.print("Proximity readings: ");
  for (int i=0; i<4; i++) {
    // read the difference between the measured baseline and the measured continuous data
    int reading = MPR121.getBaselineData(i)-MPR121.getFilteredData(i);
    Serial.print(reading);     
    Serial.print(" ");
  };
  Serial.println();
//
//  // constrain the reading between our low and high mapping values
//  unsigned int prox = constrain(reading, LOW_DIFF, HIGH_DIFF);
//  
//  // implement a simple (IIR lowpass) smoothing filter
//  lastProx = (filterWeight*lastProx) + ((1-filterWeight)*(float)prox);
//
//  // map the LOW_DIFF..HIGH_DIFF range to 0..254 (max range for MP3player.setVolume())
//  uint8_t thisOutput = (uint8_t)map(lastProx,LOW_DIFF,HIGH_DIFF,0,254);
}
