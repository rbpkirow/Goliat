#include <TimerOne.h>
#include "DigoleSerial.h"

#define _Digole_Serial_UART_  //To tell compiler compile the special communication only, 

#define LCDCol 20
#define LCDRow 4

#define LED 13


DigoleSerialDisp mydisp(&Serial1, 9600);


void setup() 
{
  ResetDisplay();

  mydisp.drawStr(1, 0, "Config de Goliath"); //display string at: x=4, y=0
}

void loop() 
{
  delay(1000);
  ResetDisplay();
  delay(1000);
  mydisp.drawStr(1, 0, "Config de Goliath"); //display string at: x=4, y=0
}

