// ESCLAVO.
// Recibe la peticion de datos por I2C.
// Envia por I2C los valores de todos los sensores

#include <Wire.h>

unsigned char resultSuma;
unsigned char resultResta;

void setup()
{
  Wire.begin(2);
  Wire.onRequest(RequetEvent);
}



void loop()
{
}

void RequetEvent()
{
  uint8_t bufer[6];
  bufer[0] = (digitalRead(3)<<7) + (digitalRead(4)<<6) + (digitalRead(5)<<5) + (digitalRead(6)<<4) + (digitalRead(7)<<3) + (digitalRead(8)<<2) + (digitalRead(9)<<1) + (digitalRead(10)<<0);
  bufer[1] = analogRead(A0);
  bufer[2] = analogRead(A1);
  bufer[3] = analogRead(A2);
  bufer[4] = analogRead(A3);
  bufer[5] = analogRead(A4);
  Wire.write(bufer,6);
}

