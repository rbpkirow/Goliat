#include "defines.h"
#include "Funciones.h"
#include <Wire.h>



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
//      Serial1.println("P1_PULSADO");
//    }
//    if(abs(_botonAn - REF_P2) < 30)
//    {
//      Pulsador = P2_PULSADO;	// Indica cambio de estrategia inicial
//      Serial1.println("P2_PULSADO");
//      // Enviar por lcd la estrategia utilizada
//    }
//    if(abs(_botonAn - REF_P3) < 30)
//    {
//      Pulsador = P3_PULSADO;
//      Serial1.println("P3_PULSADO");
//    }
//  }while(Pulsador != P1_PULSADO);
//  
  // Ya estamos preparados para arrancar con el mando
  
  delay(500);
  Serial1.println("Iniciando!!!");
}


unsigned char sAux,cnyDer,cnyIzq,sTras,sDer,sIzq,sDelDer,sDelIzq;  // todos son digitales

void EnviarDatosArecibir(int _numero)
{
  Wire.beginTransmission(address);
  Wire.write(_numero);
  Wire.endTransmission();
}

void LeerDatosI2C(int _numero)
{
  int contadorWire = 0;
  Wire.requestFrom(address,_numero);
  while(Wire.available() != _numero && contadorWire<2)
  {
    if(Wire.available() == 0)
      Wire.requestFrom(address,_numero);
    contadorWire++;
  }

  // Leemos el primer dato  
  varios = Wire.read();
  sAux    = (varios & 0b00000001) >> 0;
  cnyDer  = (varios & 0b00000010) >> 1;
  cnyIzq  = (varios & 0b00000100) >> 2;
  sTras   = (varios & 0b00001000) >> 3;
  sDer    = (varios & 0b00010000) >> 4;
  sIzq    = (varios & 0b00100000) >> 5;
  sDelDer = (varios & 0b01000000) >> 6;
  sDelIzq = (varios & 0b10000000) >> 7;

  // Si son 4, leemos los otros 3 sensores
  if(_numero == 4)
  {
    
  }
  
}


void loop() 
{
        _contadorPID++;
	if(_contadorPID == 9)	// Si han pasado 45 msg, leo todos los sensores
	{
          EnviarDatosArecibir(4);
          LeerDatosI2C(4);
          _contadorPID = 0;
	}
	else	// Sino, solo leo los sensores digitales y los CNY
	{	
            EnviarDatosArecibir(1);
            LeerDatosI2C(1);
	}
        delay(5);
  
}


