// MASTER.
// Envia la peticion para recibir los sensores
// Direccion del esclavo: 0xF5

#include <Wire.h>

char valor1;
unsigned char valor2;
unsigned char valor3;
unsigned char valor4;
unsigned char valor5;
unsigned char valor6;


void setup()
{
  Wire.begin();  // I2C como Maestro
  Serial.begin(9600);
}



void loop()
{
  Wire.requestFrom(2,6);
  // Pido 8 bits de los 8 sensores digitales
  // y 5 sensores analogicos
  // En total, 6 valores
  
  while(Wire.available())
  {
    valor1 = Wire.read();
    valor2 = Wire.read();
    valor3 = Wire.read();
    valor4 = Wire.read();
    valor5 = Wire.read();
    valor6 = Wire.read();
    Serial.print("valor1 = ");
    Serial.print(valor1,BIN);
    Serial.print(" valor2 = ");
    Serial.print(valor2,DEC);
    Serial.print(" valor3 = ");
    Serial.print(valor3,DEC);
    Serial.print(" valor4 = ");
    Serial.print(valor4,DEC);
    Serial.print(" valor5 = ");
    Serial.print(valor5,DEC);
    Serial.print(" valor6 = ");
    Serial.println(valor6,DEC);
  }
  delay(500);
}

