// ESCLAVO.
// Recibe la peticion de datos por I2C.
// Envia por I2C los valores de todos los sensores
#include "defines.h"
#include <Wire.h>
#include "DigoleSerial.h"


char MyCont;

void setup()
{
  Wire.begin(2);
  Wire.onRequest(RequestEvent);
  Wire.onReceive(ReceiveEvent);
  
  Enviar = 0;
  CNY_I = 0;
  CNY_D = 0;
  valor_aux = 0;
  MyCont = 0;
  ResetDisplay();
}


//  Sensor digital delantero Izquierdo (5)
//  Sensor digital delantero Derecho (6)
//  Sensor digital Izquierdo (7)
//  Sensor digital derecho (8)
//  Sensor digital trasero (10)
//  CNY_I
//  CNY_D
//  Sensor auxiliar (4)

void loop()
{    
    delayMicroseconds(500);
}


void RequestEvent()
{
  
    if(analogRead(SA_CNY_Izq) > UMBRAL)  CNY_I = 1;
    else                                 CNY_I = 0;
      
    if(analogRead(SA_CNY_Der) > UMBRAL)  CNY_D = 1;  
    else                                 CNY_D = 0;
    bufer[0] =  (0<<7) + //(digitalRead(SD_DelIzq)<<7) + 
                (0<<6) + //(digitalRead(SD_DelDer)<<6) + 
                (0<<5) +   //(digitalRead(SD_Izq)<<5) + 
                (0<<4) + //(digitalRead(SD_Der)<<4) + 
                (0<<3) + //(digitalRead(SD_Tras)<<3) + 
                (CNY_I<<2) + 
                (CNY_D<<1) + 
                (0<<0);  //(digitalRead(SD_Aux)<<0);
   if(EnviarDatos == 1)
   {
       Wire.write(bufer,1);
   }  
  
    else
    {
      bufer[1] = analogRead(SA_TrasIzq);  // Sensor analogico trasero izquierda
      bufer[2] = analogRead(SA_TrasDer);  // Sensor analogico trasero derecha
      bufer[3] = analogRead(SA_Del);  // Sensor analogico delantero largo
    
      bufer[0] = 0 + (CNY_I<<2) + (CNY_D<<1);
      Wire.write(bufer,4);
    }
    MyCont++;
    if(MyCont >= 20)
    {
      MyCont = 0;
      char _Mensaje[25];
      ResetDisplay();
      itoa(analogRead(SA_CNY_Izq), _Mensaje, 10);
      LCD.drawStr(0, 0, _Mensaje);    
      itoa(analogRead(SA_CNY_Der), _Mensaje, 10);
      LCD.drawStr(0, 1, _Mensaje);    
    }
}



// Formato Lectura sensores: 1 solo byte. valor = 1 para leer solo los digitales. valor = 4 para leer todos los sensores
// Formato LCD: Fila - Columna - Mensaje
void ReceiveEvent(int howMany)
{
  char _Mensaje[25];
  char _Fila;
  char _Col;
  unsigned char index = 0;
  for(index = 0; index<25; index++)
    _Mensaje[index] = 0;
    
  index = 0;
    
  if(howMany == 1)
  {
      EnviarDatos = Wire.read();
  }  
  else
  {
      _Fila = Wire.read();
      _Col = Wire.read();
      while(Wire.available())
      {
        _Mensaje[index] = Wire.read();
        index++;
      }
      _Mensaje[index] = '\0';
      LCD.drawStr(_Fila, _Col, "                    ");
      LCD.drawStr(_Fila, _Col, _Mensaje);
  }
  
}



void resetpos(void)
{
    LCD.setPrintPos(0, 1);
    delay(2000); //delay 2 seconds
    LCD.setPrintPos(0, 1);
}


void ResetDisplay(void)
{
    LCD.begin();
    LCD.disableCursor(); //disable cursor, enable cursore use: enableCursor();
    LCD.clearScreen(); //CLear screen
}  

