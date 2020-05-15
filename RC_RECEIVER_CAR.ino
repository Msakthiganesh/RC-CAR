#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

int msg1[3]= {0, 0, 0};
int msg2[2]= {0, 0};
int sizeofBuff1 = sizeof(msg1); 
int sizeofBuff2 = sizeof(msg2); 
//const uint64_t pipe1 = 0xE8E8F0F0E1LL;
const uint64_t pipe2 = 0xE8E8F0F0E2LL;

int M1a = 5,M1b = 6,M2a = 9,M2b = 10;
int X,Y;
void setup() 
{  
  pinMode(M1a ,OUTPUT);
  pinMode(M1b ,OUTPUT);
  pinMode(M2a ,OUTPUT);
  pinMode(M1a ,OUTPUT);
  Serial.begin(115200);
  radio.begin();
  //radio.openWritingPipe(pipe1);
  radio.openReadingPipe(1,pipe2);
  radio.startListening();
}

void loop() 
{ 
  radio.startListening();
  if (radio.available()) 
  { radio.read(msg1, sizeofBuff1); }

  
  Y=msg1[1];
  Y = map (Y, -255, 255, -100, 100);
 
  X=msg1[0];
  X = map (X, -255, 255, -100, 100);

  Serial.print(X);
  Serial.print("   ");
  Serial.println(Y);
  
  if (Y>30)
  FWD();
  
  else if (Y<-30) 
  BWD();
  
  else if (X<-30)
  LEFT();
  
  else if (X>30)
  RIGHT();
 else
  BOT_STOP();
  delay(50);
  
}
void FWD()
{
  analogWrite(M1a ,Y);
  analogWrite(M1b ,0);
  analogWrite(M2a ,Y);
  analogWrite(M2b ,0);
  }
void BWD()
{
  analogWrite(M1a ,0);
  analogWrite(M1b ,Y);
  analogWrite(M2a ,0);
  analogWrite(M2b ,Y);
  }

void LEFT()
{
  analogWrite(M1a ,X);
  analogWrite(M1b ,0);
  analogWrite(M2a ,0);
  analogWrite(M2b ,X);
  }

  
void RIGHT()
{
  analogWrite(M1a ,0);
  analogWrite(M1b ,X);
  analogWrite(M2a ,X);
  analogWrite(M2b ,0);
  }

void BOT_STOP()
{
  analogWrite(M1a ,0);
  analogWrite(M1b ,0);
  analogWrite(M2a ,0);
  analogWrite(M2b ,0);
  }

