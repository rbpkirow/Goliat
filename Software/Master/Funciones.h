#include <Wire.h>
#include "arduino.h"

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
        Serial1.begin(115200);
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
        _contadorPID = 0;
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
    Serial1.println(_botonAn_tmp1);
    
    
    if(abs(_botonAn_tmp1 - _botonAn_tmp2) < 10)  // Si el valor es el mismo, es que el boton esta pulsado
      _botonAn = _botonAn_tmp1;
    else
      _botonAn = REF_P0;  // Sino, es que ha pillado un cambio y no se cual es el boton pulsado
    
    if(BOTON_P1_PULSADO)
    {
      Pulsador = P1_PULSADO;	// Indica arranque del robot      
      Serial1.println("P1_PULSADO");
    }
    if(BOTON_P2_PULSADO)
    {
      Pulsador = P2_PULSADO;	// Indica cambio de estrategia inicial
      Serial1.println("P2_PULSADO");
      // Enviar por lcd la estrategia utilizada
    }
    if(BOTON_P3_PULSADO)
    {
      Pulsador = P3_PULSADO;
      Serial1.println("P3_PULSADO");
    }
  }while(Pulsador != P1_PULSADO);
}


char ComprobarCNY(void)
{
    char LecturaCNY_D = cnyDer;
    char LecturaCNY_I = cnyIzq;
    if(LecturaCNY_D == BLANCO || LecturaCNY_I == BLANCO)
    {
        if(LecturaCNY_D == BLANCO && LecturaCNY_I == BLANCO)
	{
	  return LEIDO_CNY_BOTH;
	}
	else
        {
	  if(LecturaCNY_D == BLANCO)
	  {
	    return LEIDO_CNY_D;
	  }
	  else    // LecturaCNY_I == NEGRO
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
            Serial1.println("Leidos 2 CNY");
            contadorCNY_D = 0;
            contadorCNY_I = 0;
            contadorCNY_Ambos++;
            if(contadorCNY_Ambos >= NUM_LECTURAS_CNY)
            {
              contadorCNY_Ambos = 0;
              Serial1.println("Confirmado 2 CNY");
            
              ponMotores(-10, -10);    delay(10);
              ponMotores(-50, -50);    delay(400);
              ponMotores(50, 50);      delay(100);
              
              if(PosicionOponente != DETECTADO_ADELANTE)
              {
                  ponMotores(50, -50);  delay(700);
                  ponMotores(50, 50);	delay(100);
              }
            }   // if(contadorCNY_Ambos >= NUM_LECTURAS_CNY)
            break;

            case LEIDO_CNY_D:
              contadorCNY_Ambos = 0;
              contadorCNY_I = 0;
              contadorCNY_D++;

              if(contadorCNY_D >= NUM_LECTURAS_CNY)
              {
                  contadorCNY_D = 0;

                  switch(PosicionOponente)
                  {
                      case NO_DETECTADO:
                          ponMotores(-10, -10);    delay(10);
                          ponMotores(-10, -50);   delay(400);
                          ponMotores(50, 50);    delay(10);
                          break;
                      case DETECTADO_ADELANTE:	// Si detecto adelante, no hago caso a los cny, simplemente empujo.
                          ponMotores(0, -50);	    delay(200);
                          ponMotores(50, 50);	    delay(10);
                          break;
                      case DETECTADO_DERECHA:		// Si detecto a la derecha y se activa el cny derecho, es casi imposible. No lo contemplo
                          break;
                      case DETECTADO_IZQUIERDA:	// Si detecto a la izquierda y se activa el cny derecho, es que me esta empujando. Intento salir dando marcha atras.
                          ponMotores(-10, -10);	    delay(10);
                          ponMotores(-50, -50);	    delay(400);
                          ponMotores(50, 50);	    delay(10);
                          break;
                      case DETECTADO_ATRAS:
                          ponMotores(-10, -10);  delay(10);
                          ponMotores(-50, -50);  delay(10);
                          ponMotores(50, 50);    delay(10);
                          break;
                      default:
                          break;
                  } // switch(PosicionOponente)
              } // if(contadorCNY_D >= NUM_LECTURAS_CNY)
              break;
          case LEIDO_CNY_I:
              contadorCNY_Ambos = 0;
              contadorCNY_D = 0;
              contadorCNY_I++;
              if(contadorCNY_I >= NUM_LECTURAS_CNY)
              {
                  contadorCNY_I = 0;

                  switch(PosicionOponente)
                  {
                      case NO_DETECTADO:
                          ponMotores(-10, -10);	delay(10);
                          ponMotores(-50, -10);	delay(400);
                          ponMotores(50, 50);	delay(10);
                          break;
                      case DETECTADO_ADELANTE:	// Si detecto adelante, no hago caso a los cny, simplemente empujo.
                          ponMotores(-150, 0);	delay(10);
                          ponMotores(100, 100);	delay(10);
                          break;
                      case DETECTADO_DERECHA:		// Si detecto a la derecha y se activa el cny izquierdo, es que me esta empujando. Intento salir dando marcha atras.
                          ponMotores(-10, -10);	    delay(10);
                          ponMotores(-200, -130);   delay(10);
                          ponMotores(100, 100);	    delay(10);
                          break;
                      case DETECTADO_IZQUIERDA:	// Si detecto a la izquierda y se activa el cny izquierdo, es casi imposible. No lo contemplo
                          break;
                      case DETECTADO_ATRAS:
                          ponMotores(-10, -10);	    delay(10);
                          ponMotores(-50, -50);     delay(400);
                          ponMotores(50, 50);	    delay(10);
                          break;
                      default:
                          break;
                  }   // switch(PosicionOponente)
              }   // if(contadorCNY_I >= NUM_LECTURAS_CNY)
              break;


      default:
         contadorCNY_Ambos = 0;
         ponMotores(50, 50);
         break;
  }
}
















