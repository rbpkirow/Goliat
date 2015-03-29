#include <Wire.h>
#include "DigoleSerial.h"


#define _Digole_Serial_UART_  //To tell compiler compile the special communication only, 

#define LCDCol 20
#define LCDRow 4
DigoleSerialDisp LCD(&Serial1, 9600);


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
