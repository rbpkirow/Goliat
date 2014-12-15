// ESCLAVO.
// Recibe la peticion de datos por I2C.
// Envia por I2C los valores de todos los sensores

#include <Wire.h>

#define UMBRAL  512

uint8_t bufer[4];
char Enviar;
unsigned int CNY_1, CNY_2, valor_aux;

void setup()
{
  Wire.begin(2);
  Wire.onRequest(RequetEvent);
  Enviar = 0;
  CNY_1 = 0;
  CNY_2 = 0;
  valor_aux = 0;
}


//  Sensor digital delantero Izquierdo (5)
//  Sensor digital delantero Derecho (6)
//  Sensor digital Izquierdo (7)
//  Sensor digital derecho (8)
//  Sensor digital trasero (10)
//  CNY_1
//  CNY_2
//  Sensor auxiliar (4)

void loop()
{
  
}

void RequetEvent()
{
  valor_aux = analogRead(2);  // CNY analogico delantero izquierda
  CNY_1 = 0;
  if(valor_aux > UMBRAL)
    CNY_1 = 1;
  valor_aux = analogRead(3);  // CNY analogico delantero derecha
  CNY_2 = 0;
  if(valor_aux > UMBRAL)
    CNY_2 = 1;
    
  bufer[0] = (digitalRead(5)<<7) + (digitalRead(6)<<6) + (digitalRead(7)<<5) + (digitalRead(8)<<4) + (digitalRead(10)<<3) + (CNY_1<<2) + (CNY_2<<1) + (digitalRead(4)<<0);
  
  bufer[1] = analogRead(0);  // Sensor analogico trasero izquierda
  bufer[2] = analogRead(1);  // Sensor analogico trasero derecha
  bufer[3] = analogRead(9);  // Sensor analogico delantero largo
  
  bufer[0] = 11;
  bufer[1] = 22;
  bufer[2] = 33;
  bufer[3] = 44;
  Wire.write(bufer,4);
  Serial.println("Enviado");
}

