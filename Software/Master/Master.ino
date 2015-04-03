#include "defines.h"
#include "Funciones.h"
#include <Wire.h>

char NumSensores;

void setup() 
{
  InitHw();
  Serial1.println("Selecciona la estrategia");
//  SeleccionarEstrategia();
  
  delay(500);  
  digitalWrite(LED1,HIGH);
  delay(500);
  digitalWrite(LED2,HIGH);
  delay(500);
  digitalWrite(LED3,HIGH);
  
  // Ya estamos preparados para arrancar con el mando  
  delay(500);
  Serial1.println("Iniciando!!!");
  PosicionOponente = NO_DETECTADO;
  NumSensores = 1;
  TIME = 200;
}




void EnviarDatosArecibir(char _numero)
{
  Wire.beginTransmission(2);
  Wire.write(_numero);
  Wire.endTransmission();
}

void LeerDatosI2C(char _numero)
{
  int contadorWire = 0;
  Wire.requestFrom(2,_numero);

  while(Wire.available() != _numero && contadorWire<2)
  {
    Serial1.println("Esperando datos...");
    if(Wire.available() == 0)
    {
      Serial1.println("Datos no disponibles.. Vuelvo a pedirlos");
      Wire.requestFrom(2,_numero);
    }
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
          Serial1.print("Pido 4 datos");
          NumSensores = 4;
          EnviarDatosArecibir(NumSensores);
          LeerDatosI2C(NumSensores);
          _contadorPID = 0;
	}
	else	// Sino, solo leo los sensores digitales y los CNY
	{	
            Serial1.print("Pido 1 datos");
            NumSensores = 1;
            EnviarDatosArecibir(NumSensores);
            LeerDatosI2C(NumSensores);
            Serial1.print(" - Leidos los siguientes datos: ");
            Serial1.print("    cnyDer= "); Serial1.print(cnyDer); 
            Serial1.print("    cnyIzq= "); Serial1.print(cnyIzq); 
            Serial1.print("    sDelDer= "); Serial1.print(sDelDer); 
            Serial1.print("    sDelIzq= "); Serial1.println(sDelIzq); 
            _contadorPID = 0;
	}

        m_comprobarCNY = ComprobarCNY();
        UseCnyData();
        
        delay(5);  
}





