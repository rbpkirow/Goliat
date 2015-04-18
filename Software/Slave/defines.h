#include <Wire.h>


// Para el LCD - En robolid 2015 no va conectado
//#include "DigoleSerial.h"
//#define _Digole_Serial_UART_  //To tell compiler compile the special communication only, 
//#define LCDCol 20
//#define LCDRow 4
//DigoleSerialDisp LCD(&Serial1, 9600);


#define SD_DelIzq   5  // 12v OmroUm
#define SD_DelDer   6  // 12v Omrom
#define SD_Del      4  // 5v 40cm.

#define SD_Izq      9  // 12v Omrom
#define SD_Der      8  // 12v Omrom
#define SD_Tras    10  // 5v 40cm.

#define SA_CNY_Izq A2  // CNY70
#define SA_CNY_Der A3  // CNY70

int UMBRAL;

uint8_t bufer[2];
char Enviar;
unsigned int valor_aux;
unsigned int CNY_I, CNY_D;
int ValorCNY_D, ValorCNY_I;

