// MASTER.
// Envia la peticion para recibir los sensores
// Direccion del esclavo: 2

#include <Wire.h>

char valor1;
unsigned char valor2;
unsigned char valor3;
unsigned char valor4;
unsigned char valor5;
unsigned char valor6;


void setup()
{
  // Modificacion de la frecuencia de PWM --> 4 KHz de PWM
  TCCR4B = TCCR4B & 0b000 | 0x04;  // PWM-6
  TCCR3B = TCCR3B & 0b000 | 0x02;  // PWM-5
  TCCR1B = TCCR1B & 0b000 | 0x02;  // PWM-9-10
  TCCR0B = TCCR0B & 0b000 | 0x03;  // PWM-3 --> AFECTA A DELAY. Valor por defecto = 0x03
  
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  
  Wire.begin();  // I2C como Maestro
  Serial.begin(115200);
  
  analogWrite(5,10);
  analogWrite(6,20);
  analogWrite(9,30);
  analogWrite(10,40);
}



void loop()
{
  Wire.requestFrom(2,4);
  // Pido 8 bits de los 8 sensores digitales
  // y 3 sensores analogicos
  // En total, 4 valores
  
  while(Wire.available())
  {
    valor1 = Wire.read();
    valor2 = Wire.read();
    valor3 = Wire.read();
    valor4 = Wire.read();
    Serial.print("valor1 = ");
    Serial.print(valor1,BIN);
    Serial.print(" valor2 = ");
    Serial.print(valor2,DEC);
    Serial.print(" valor3 = ");
    Serial.print(valor3,DEC);
    Serial.print(" valor4 = ");
    Serial.println(valor4,DEC);
  }
  delay(500);
}

