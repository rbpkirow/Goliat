// ESCLAVO.
// Recibe la peticion de datos por I2C.
// Envia por I2C los valores de todos los sensores

#include <Wire.h>
#include "DigoleSerial.h"

#define _Digole_Serial_UART_  //To tell compiler compile the special communication only, 

#define LCDCol 20
#define LCDRow 4
//DigoleSerialDisp mydisp(&Serial1, 9600);


#define SD_DelIzq   5
#define SD_DelDer   6
#define SD_Izq      7
#define SD_Der      8
#define SD_Aux      4
#define SA_Aux     A6
#define SA_Del     A9
#define SD_Tras    10
#define SA_TrasIzq A0
#define SA_TrasDer A1
#define SA_CNY_Izq A2
#define SA_CNY_Der A3


#define UMBRAL  512

uint8_t bufer[4];
char Enviar;
unsigned int CNY_I, CNY_D, valor_aux;
int EnviarDatos;

void setup()
{
  Serial.begin(115200);
  Wire.begin(2);
  Wire.onRequest(RequestEvent);
  Wire.onReceive(ReceiveEvent);
  Enviar = 0;
  CNY_I = 0;
  CNY_D = 0;
  valor_aux = 0;
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

}


void RequestEvent()
{
    valor_aux = analogRead(SA_CNY_Izq);  // CNY analogico delantero izquierda
    CNY_I = 0;
    if(valor_aux > UMBRAL)
      CNY_I = 1;
    valor_aux = analogRead(SA_CNY_Der);  // CNY analogico delantero derecha
    CNY_D = 0;
    if(valor_aux > UMBRAL)
      CNY_D = 1;
    
    bufer[0] =  (digitalRead(SD_DelIzq)<<7) + 
                (digitalRead(SD_DelDer)<<6) + 
                (digitalRead(SD_Izq)<<5) + 
                (digitalRead(SD_Der)<<4) + 
                (digitalRead(SD_Tras)<<3) + 
                (CNY_I<<2) + (CNY_D<<1) + 
                (digitalRead(SD_Aux)<<0);
   if(EnviarDatos == 1)
   {
       Wire.write(bufer,1);
       Serial.println("Enviado 1 datos");
   }  
  
    else
    {
  
      bufer[1] = analogRead(SA_TrasIzq);  // Sensor analogico trasero izquierda
      bufer[2] = analogRead(SA_TrasDer);  // Sensor analogico trasero derecha
      bufer[3] = analogRead(SA_Del);  // Sensor analogico delantero largo
    
      bufer[0] = 0 + (CNY_I<<2) + (CNY_D<<1);
      Wire.write(bufer,4);
      Serial.println("Enviado 4 datos");
    }
//  mydisp.drawStr(1, 0, "Config de Goliath"); //display string at: x=4, y=0
}



void ReceiveEvent(int howMany)
{
  char c;
  while(Wire.available())
  {
    c = Wire.read();
    Serial.print(c,DEC);
    if(howMany == 1)
    {
      EnviarDatos = c;
    }
  }
  Serial.println();
}



void resetpos(void)
{
//    mydisp.setPrintPos(0, 1);
    delay(2000); //delay 2 seconds
//    mydisp.println("                "); //display space, use to clear the demo line
//    mydisp.setPrintPos(0, 1);
}


void ResetDisplay(void)
{
   // mydisp.begin();
//    mydisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
//    mydisp.clearScreen(); //CLear screen
}  

