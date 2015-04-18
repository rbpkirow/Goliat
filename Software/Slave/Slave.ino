// ESCLAVO.


// Recibe la peticion de datos por I2C.
// Envia por I2C los valores de todos los sensores

// Formato de envio:
//    _________________________________________________________________________________________________
//    |   bit 7   |   bit 6   |   bit 5   |   bit 4   |   bit 3   |   bit 2   |   bit 1   |   bit 0   |
//    |___________|___________|___________|___________|___________|___________|___________|___________|
//    | SD_DelIzq | SD_DelDer |   SD_Del  |   SD_Izq  |   SD_Der  |   SD_Tras |   CNY_I   |   CNY_D   |
//    |___________|___________|___________|___________|___________|___________|___________|___________|






#include "defines.h"
#include <Wire.h>
//#include "DigoleSerial.h"

void setup()
{

  Wire.begin(2);
  Wire.onRequest(RequestEvent);
  Wire.onReceive(ReceiveEvent);
  UMBRAL = 600;
}


//  Sensor digital delantero (4)
//  Sensor digital delantero Izquierdo (5)
//  Sensor digital delantero Derecho (6)
//  Sensor digital Izquierdo (7)
//  Sensor digital derecho (8)
//  Sensor digital trasero (10)
//  Sensor CNY izquierdo (A2)
//  Sensor CNY derecho (A3)


void loop()
{    
    delayMicroseconds(10);
}


void RequestEvent()
{
    ValorCNY_D = analogRead(SA_CNY_Der);  
    ValorCNY_I = analogRead(SA_CNY_Izq);
    
    if(ValorCNY_D > UMBRAL)  CNY_D = 1;  
    else                     CNY_D = 0;

    if(ValorCNY_I > UMBRAL)  CNY_I = 1;  
    else                     CNY_I = 0;
    
    bufer[0] =  (digitalRead(SD_DelIzq)<<7) + 
                (digitalRead(SD_DelDer)<<6) + 
                (digitalRead(SD_Del)<<5) +
                (digitalRead(SD_Izq)<<4) + 
                (digitalRead(SD_Der)<<3) + 
                (digitalRead(SD_Tras)<<2) +
                (CNY_I<<1) + 
                (CNY_D<<0);
    Wire.write(bufer,1);
}


void ReceiveEvent(int howMany)
{
  char c;
  while(Wire.available())
  {
    c = Wire.read();
    if(howMany == 1)
    {
      UMBRAL = c*4;
    }
  }
}

