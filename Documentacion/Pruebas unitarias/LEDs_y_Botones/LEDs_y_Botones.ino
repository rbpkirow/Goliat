#include <Wire.h>
#include <TimerOne.h>

int valor;
int i;

unsigned char varios;
unsigned char SA_TrasIzq;
unsigned char SA_TrasDer;
unsigned char SA_Del;

#define BOTON_PIN A6

#define LED1 14
#define LED2 15
#define LED3 16

#define PWM_I_1  5
#define PWM_I_2  6

#define PWM_D_1  9
#define PWM_D_2 10

#define NO_P_PULSADO 0
#define P1_PULSADO 1
#define P2_PULSADO 2
#define P3_PULSADO 3


#define REF_P1 584
#define REF_P2 767
#define REF_P3 877
#define REF_P0 1023


int _botonAn,_botonAn_tmp1,_botonAn_tmp2;
int Boton;
unsigned char _contadorPID;
char Pulsador;

void InitHw()
{
	Serial.begin(115200);
	Wire.begin();  // I2C como Maestro
	TCCR1B = TCCR1B & 0b000 | 0x02;  // 4KHz PWM-9-10
	TCCR3B = TCCR3B & 0b000 | 0x02;  // 4KHz PWM-5
	TCCR4B = TCCR4B & 0b000 | 0x04;  // 4KHz PWM-6
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(PWM_I_1,OUTPUT);
	pinMode(PWM_I_2,OUTPUT);
	pinMode(PWM_D_1,OUTPUT);
	pinMode(PWM_D_2,OUTPUT);
	pinMode(BOTON_PIN,INPUT);
}

void setup() 
{
  InitHw();
   
  _contadorPID = 0;
  
//  do
//  {
//    // Lectura de los pulsadores - Leo 2 veces para evitar rebotes y falsas lecturas
//    _botonAn_tmp1 = analogRead(BOTON_PIN);      delay(50);    _botonAn_tmp2 = analogRead(BOTON_PIN);
//    
//    if(abs(_botonAn_tmp1 - _botonAn_tmp2) < 10)  // Si el valor es el mismo, es que el boton esta pulsado
//      _botonAn = _botonAn_tmp1;
//    else
//      _botonAn = REF_P0;  // Sino, es que ha pillado un cambio y no se cual es el boton pulsado
//    
//    if(abs(_botonAn - REF_P1) < 30)
//    {
//      Pulsador = P1_PULSADO;	// Indica arranque del robot
//      Serial.println("P1_PULSADO");
//    }
//    if(abs(_botonAn - REF_P2) < 30)
//    {
//      Pulsador = P2_PULSADO;	// Indica cambio de estrategia inicial
//      Serial.println("P2_PULSADO");
//      // Enviar por lcd la estrategia utilizada
//    }
//    if(abs(_botonAn - REF_P3) < 30)
//    {
//      Pulsador = P3_PULSADO;
//      Serial.println("P3_PULSADO");
//    }
//  }while(Pulsador != P1_PULSADO);
//  
  // Ya estamos preparados para arrancar con el mando
  delay(5000);
}



void loop() 
{
        _contadorPID++;
	if(_contadorPID == 9)	// Si han pasado 45 msg, leo todos los sensores
	{
                Wire.beginTransmission(2);
                Wire.write(4);
                Wire.endTransmission();
		Wire.requestFrom(2,4);
		while(Wire.available() != 4);
		varios = Wire.read();
		SA_TrasIzq = Wire.read();
		SA_TrasDer = Wire.read();
		SA_Del = Wire.read();
                _contadorPID = 0;
                Serial.println("Leidos 4 datos");
	}
	else	// Sino, solo leo los sensores digitales y los CNY
	{	
                Wire.beginTransmission(2);
                Wire.write(1);
                Wire.endTransmission();
  		Wire.requestFrom(2,1);
		while(Wire.available() != 1);
		varios = Wire.read();
                Serial.println("Leido 1 dato");
                
                ponmo
                
	}
        delay(1);
  
}






void PID()
{
	// Interrupcion cada 5 msg para el PID
	
}




