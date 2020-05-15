#include <SPI.h>
#include "RF24.h"
RF24 radio(7,8);
//const uint64_t pipe2 = 0xE8E8F0F0E1LL;
const uint64_t pipe1 = 0xE8E8F0F0E2LL;
int msg1[3]= {0, 0, 0};
int msg2[2]= {0, 0};
int sizeofBuff1 = sizeof(msg1); 
int sizeofBuff2 = sizeof(msg2); 


int joyX = A4;
int joyY = A5;
int SW = 6;

int joyVal;


void setup()
{
  pinMode(joyX,INPUT);
  pinMode(joyY,INPUT);
  pinMode(SW,INPUT_PULLUP);
 Serial.begin(115200);
radio.begin();
radio.openWritingPipe(pipe1);
//radio.openReadingPipe(1,pipe2);
radio.startListening();
}

void loop() {
  radio.stopListening();
  
 joyVal = analogRead(joyX);
 joyVal = map (joyVal, 0, 1023, -255, 255);
 msg1[0] = joyVal;
 
 joyVal = analogRead(joyY);
 joyVal = map (joyVal, 0, 1023, -255, 255);
 msg1[1] = joyVal;
 
 joyVal = digitalRead(SW);
 msg1[2] = joyVal; 
  
  radio.write(msg1, sizeofBuff1);
  delay(50);
/*radio.startListening();
  if (radio.available()) {
radio.read(msg2, sizeofBuff2);
}
Serial.print(msg1[0]);
Serial.print("  ");
Serial.println(msg1[1]);
Serial.print(msg2[0]);
Serial.print("  ");
Serial.println(msg2[1]);
Serial.println("  ");
delay(50);*/
}


