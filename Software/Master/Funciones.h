#include <Wire.h>
#include "arduino.h"

void bluePrintln(char *cadena);
void bluePrint(char *cadena);
void LeerSensores();


void checkDeteccion(int tiempo)
{
    for(i=0; i<tiempo/5; i++)
    { 
        delay(5); 
        LeerSensores(); 
        if((sDelIzq * sDelDer * sDel == DETECTADO) &&  sCnyD != BLANCO && sCnyI != BLANCO) 
           return;
    }
}

void ponMotores(int _MotIzq, int _MotDer)
{
  
    if(_MotIzq >= 0)
    {
        if(_MotIzq > V_MAXIMA)
            _MotIzq = V_MAXIMA;
        analogWrite(PWM_I_1, 0 );
        analogWrite(PWM_I_2,_MotIzq);
    }
    else
    {
        if(_MotIzq < -V_MAXIMA)
            _MotIzq = -V_MAXIMA;
        analogWrite(PWM_I_1, (-_MotIzq) );
        analogWrite(PWM_I_2,  0);
    }

    if(_MotDer >= 0)
    {
        if(_MotDer > V_MAXIMA)
            _MotDer = V_MAXIMA;
        analogWrite(PWM_D_1,_MotDer);
        analogWrite(PWM_D_2,0);    
    }
    else
    {
        if(_MotDer < -V_MAXIMA)
            _MotDer = -V_MAXIMA;
        analogWrite(PWM_D_1,0);
        analogWrite(PWM_D_2, -(_MotDer) );    
    }
}



void InitHw()
{
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
	pinMode(CNY_D,INPUT);
	pinMode(CNY_I,INPUT);

      // Variables
        PosicionOponente = NO_DETECTADO;
        EnviarDatos = 0;
        contador_V_BASE = 0;
        V_BASE_INICIAL = 80;
        V_BASE = V_BASE_INICIAL;
        TIME = 200;
}


#define BOTON_P1_PULSADO   (abs(_botonAn - REF_P1) < 30)
#define BOTON_P2_PULSADO   (abs(_botonAn - REF_P2) < 30)
#define BOTON_P3_PULSADO   (abs(_botonAn - REF_P3) < 30)

void SeleccionarEstrategia()
{
  do    
  {
    // Lectura de los pulsadores - Leo 2 veces para evitar rebotes y falsas lecturas
    _botonAn_tmp1 = analogRead(BOTON_PIN);      delay(50);    _botonAn_tmp2 = analogRead(BOTON_PIN);
    
    if(abs(_botonAn_tmp1 - _botonAn_tmp2) < 10)  // Si el valor es el mismo, es que el boton esta pulsado
      _botonAn = _botonAn_tmp1;
    else
      _botonAn = REF_P0;  // Sino, es que ha pillado un cambio y no se cual es el boton pulsado
    
    if(BOTON_P1_PULSADO)
    {
      Pulsador = P1_PULSADO;	// Indica arranque del robot      
      bluePrintln("P1_PULSADO");
    }
    if(BOTON_P2_PULSADO)
    {
      Pulsador = P2_PULSADO;	// Indica cambio de estrategia inicial
      bluePrintln("P2_PULSADO");
      // Enviar por lcd la estrategia utilizada
    }
    if(BOTON_P3_PULSADO)
    {
      Pulsador = P3_PULSADO;
      bluePrintln("P3_PULSADO");
    }
  }while(Pulsador != P1_PULSADO);
}



void LeerSensores()
{
  int contadorWire = 0;
  
  // Lectura de datos
  Wire.requestFrom(SLAVE_ADD, 1);  // Pedimos al esclavo 1 byte con el formato correcto
  while(Wire.available() != 1 && contadorWire<2)
  {
    if(Wire.available() == 0)
    {
      Wire.requestFrom(SLAVE_ADD,1);
    }
    contadorWire++;
  }

  // Leemos el primer dato  
  varios = Wire.read();

// Formato de envio:
//    _________________________________________________________________________________________________
//    |   bit 7   |   bit 6   |   bit 5   |   bit 4   |   bit 3   |   bit 2   |   bit 1   |   bit 0   |
//    |___________|___________|___________|___________|___________|___________|___________|___________|
//    | SD_DelIzq | SD_DelDer |   SD_Del  |   SD_Izq  |   SD_Der  |   SD_Tras |   CNY_I   |   CNY_D   |
//    |___________|___________|___________|___________|___________|___________|___________|___________|

  //Serial1.print("V= ");
  //Serial1.println(varios,BIN);
  sCnyD   = (varios & 0b00000001) >> 0;
  sCnyI   = (varios & 0b00000010) >> 1;
  sTras   = (varios & 0b00000100) >> 2;
  sDer    = (varios & 0b00001000) >> 3;
  sIzq    = (varios & 0b00010000) >> 4;
  sDel    = (varios & 0b00100000) >> 5;
  sDelDer = (varios & 0b01000000) >> 6;
  sDelIzq = (varios & 0b10000000) >> 7;
}




char ComprobarCNY(void)
{
    
    if(sCnyD == BLANCO || sCnyI == BLANCO)
    {
        if(sCnyD == BLANCO && sCnyI == BLANCO)
	{
	  return LEIDO_CNY_BOTH;
	}
	else
        {
	  if(sCnyD == BLANCO)
	  {
	    return LEIDO_CNY_D;
	  }
	  else    // sCnyI == BLANCO
	  {
	    return LEIDO_CNY_I;
	  }
	}
    }
    return LEIDO_CNY_NONE;
}





void UseCnyData()
{
  switch(m_comprobarCNY)
  {
      case LEIDO_CNY_BOTH:
            contadorCNY_D = 0;
            contadorCNY_I = 0;
            V_BASE = V_BASE_INICIAL;
            contador_V_BASE = 0;            
            contadorCNY_Ambos++;
            if(contadorCNY_Ambos >= NUM_LECTURAS_CNY)
            {
              contadorCNY_Ambos = 0;
            
              switch(PosicionOponente)
              {
                  case NO_DETECTADO:
                      ponMotores(-10, -10);   delay(10);
                      ponMotores(-10, -150);  checkDeteccion(600);
                      break;
                  case DETECTADO_ADELANTE:	// Si detecto adelante, no hago caso a los cny, simplemente empujo.
                      ponMotores(-10, -10);      delay(10);
                      ponMotores(-100, -100);    delay(50);
                      break;
                  case DETECTADO_DERECHA:		// Si detecto a la derecha y se activa el cny derecho, es casi imposible. No lo contemplo
                  case DETECTADO_IZQUIERDA:	// Si detecto a la izquierda y se activa el cny derecho, es que me esta empujando. Intento salir dando marcha atras.
                      ponMotores(-10, -10);	  delay(10);
                      ponMotores(-250, -250);     delay(50);
                      break;
                  case DETECTADO_ATRAS:
                      break;
                  default:
                      break;
              } // switch(PosicionOponente)
            }   // if(contadorCNY_Ambos >= NUM_LECTURAS_CNY)
            break;

            case LEIDO_CNY_D:
              contadorCNY_Ambos = 0;
              contadorCNY_I = 0;
              V_BASE = V_BASE_INICIAL;
              contador_V_BASE = 0;
              contadorCNY_D++;

              if(contadorCNY_D >= NUM_LECTURAS_CNY)
              {
                  contadorCNY_D = 0;
                  switch(PosicionOponente)
                  {
                      case NO_DETECTADO:
                          ponMotores(-10, -10);   delay(10);
                          ponMotores(-10, -150);  checkDeteccion(600);
                          break;
                      case DETECTADO_ADELANTE:	// Si detecto adelante, no hago caso a los cny, simplemente empujo.
                          ponMotores(-10, -10);      delay(10);
                          ponMotores(-80, -100);     delay(5);
                          break;
                      case DETECTADO_DERECHA:		// Si detecto a la derecha y se activa el cny derecho, es casi imposible. No lo contemplo
                          break;
                      case DETECTADO_IZQUIERDA:	// Si detecto a la izquierda y se activa el cny derecho, es que me esta empujando. Intento salir dando marcha atras.
                          ponMotores(-10, -10);	    delay(10);
                          ponMotores(-130, -200);   delay(20);
                          break;
                      case DETECTADO_ATRAS:
                          break;
                      default:
                          break;
                  } // switch(PosicionOponente)
              } // if(contadorCNY_D >= NUM_LECTURAS_CNY)
              break;
          case LEIDO_CNY_I:
              contadorCNY_Ambos = 0;
              contadorCNY_D = 0;
              V_BASE = V_BASE_INICIAL;
              contador_V_BASE = 0;
              contadorCNY_I++;
              if(contadorCNY_I >= NUM_LECTURAS_CNY)
              {
                  contadorCNY_I = 0;
                  switch(PosicionOponente)
                  {
                      case NO_DETECTADO:
                          ponMotores(-10, -10);   delay(10);
                          ponMotores(-150, -10);  checkDeteccion(600);
                          break;
                      case DETECTADO_ADELANTE:	// Si detecto adelante, no hago caso a los cny, simplemente empujo.
                          ponMotores(-10, -10);      delay(10);
                          ponMotores(-100, -80);     delay(5);
                          break;
                      case DETECTADO_DERECHA:		// Si detecto a la derecha y se activa el cny izquierdo, es que me esta empujando. Intento salir dando marcha atras.
                          ponMotores(-100, -10);  delay(10);
                          break;
                      case DETECTADO_IZQUIERDA:	// Si detecto a la izquierda y se activa el cny izquierdo, es casi imposible. No lo contemplo
                          break;
                      case DETECTADO_ATRAS:
                          ponMotores(-100, -100);  delay(10);
                          break;
                      default:
                          break;
                  }   // switch(PosicionOponente)
              }   // if(contadorCNY_I >= NUM_LECTURAS_CNY)
              break;


      default:
         break;
  }
}



void bluePrint(char *cadena)
{
#ifdef DEBUG
  Serial1.print(cadena); 
#endif
}

void bluePrintln(char *cadena)
{
#ifdef DEBUG
  Serial1.println(cadena); 
#endif
}


void FijarUmbral(int _valor)
{
  Wire.beginTransmission(2);
  Wire.write(_valor/4);
  Wire.endTransmission();
}





void UseCnyData2()
{
  char aux;
  switch(m_comprobarCNY)
  {
      case LEIDO_CNY_BOTH:
            contadorCNY_D = 0;
            contadorCNY_I = 0;
            V_BASE = V_BASE_INICIAL;
            contador_V_BASE = 0;            
            contadorCNY_Ambos++;
            if(contadorCNY_Ambos >= NUM_LECTURAS_CNY)
            {
              contadorCNY_Ambos = 0;
              ponMotores(-100, -100);
              if(PosicionOponente == NO_DETECTADO)
                  checkDeteccion(600);
              else
              {
                do{
                    LeerSensores();
                    aux = ComprobarCNY();
                    
                }while(aux != LEIDO_CNY_NONE);
              }
            
            }   // if(contadorCNY_Ambos >= NUM_LECTURAS_CNY)
            break;

            case LEIDO_CNY_D:
              contadorCNY_Ambos = 0;
              contadorCNY_I = 0;
              V_BASE = V_BASE_INICIAL;
              contador_V_BASE = 0;
              contadorCNY_D++;

              if(contadorCNY_D >= NUM_LECTURAS_CNY)
              {
                  contadorCNY_D = 0;
                  ponMotores(-10, -150);
                  if(PosicionOponente == NO_DETECTADO)
                      checkDeteccion(600);
                  else
                  {
                    do{
                        LeerSensores();
                        aux = ComprobarCNY();
                        
                    }while(aux != LEIDO_CNY_NONE);
                  }
              } // if(contadorCNY_D >= NUM_LECTURAS_CNY)
              break;
          case LEIDO_CNY_I:
              contadorCNY_Ambos = 0;
              contadorCNY_D = 0;
              V_BASE = V_BASE_INICIAL;
              contador_V_BASE = 0;
              contadorCNY_I++;
              if(contadorCNY_I >= NUM_LECTURAS_CNY)
              {
                  contadorCNY_I = 0;
                  ponMotores(-150, -10);
                  if(PosicionOponente == NO_DETECTADO)
                      checkDeteccion(600);
                  else
                  {
                    do{
                        LeerSensores();
                        aux = ComprobarCNY();
                        
                    }while(aux != LEIDO_CNY_NONE);
                  }
                 
              }   // if(contadorCNY_I >= NUM_LECTURAS_CNY)
              break;


      default:
         break;
  }
}


