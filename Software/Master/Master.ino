#include "defines.h"
#include "Funciones.h"
#include <TimerOne.h>
#include <Wire.h>

unsigned int contador_aux;

void setup() 
{
  InitHw();
  EnviarDatos = 0;
  bluePrintln("Selecciona la estrategia");
//  SeleccionarEstrategia();


  // Ya estamos preparados para arrancar con el mando  
  delay(500);
  bluePrintln("Iniciando!!!");

  contador_aux = 0;

  Timer1.initialize(4000);
  Timer1.attachInterrupt( timerIsr );
}


void loop() 
{
      if(EnviarDatos == 1)
      {
        m_comprobarCNY = ComprobarCNY();
        UseCnyData();
        EnviarDatos = 0;
      }
}


void timerIsr(void)
{

        DetectadoOponente = NO;
        DireccionAnterior = Direccion;
        _contadorPID++;
        
        
	if(_contadorPID == 30)	// Si han pasado (1500*30 usg) 45 msg, leo todos los sensores
	{
          LeerSensores(4);
          _contadorPID = 0;
	}
	else	// Sino, solo leo los sensores digitales y los CNY
	{	
            LeerSensores(1);
            _contadorPID = 0;
	}
        EnviarDatos = 1;

        
        // --------------------------------        
        //       Sensores Delanteros
        // --------------------------------        
        if(sDelIzq == DETECTADO || sDelDer == DETECTADO)
        {
            DetectadoOponente = SI;
            V_BASE+=2;
            if(V_BASE > 150)
            {
                V_BASE = 150;
                contador_V_BASE++;
                if(contador_V_BASE > 500)
                {
                    V_BASE = 80;
                    contador_V_BASE = 0;
                }
            }

            Direccion = IZQ_ADEL_DER_ADEL;
            motizq_tmp = V_BASE + 30*(!sDelIzq);
            motder_tmp = V_BASE + 30*(!sDelDer);
            PosicionOponente = DETECTADO_ADELANTE;
        }  
        else
        {
            contador_V_BASE = 0;
            V_BASE = 80;
            motizq_tmp = V_BASE;
            motder_tmp = V_BASE;
            PosicionOponente = NO_DETECTADO;
        }
        
        
        
        // ------------------------------        
        //       Sensores Trasero
        // ------------------------------        
        if(sTras == DETECTADO)
        {
            Direccion = IZQ_ADEL_DER_ADEL;
            V_BASE = 150;
            motder_tmp = -V_BASE;
            motizq_tmp = V_BASE;
            PosicionOponente = DETECTADO_ATRAS;
            DetectadoOponente = SI;
        }

        
        if(DetectadoOponente == NO)
        {
            contador_Giros++;
            if(contador_Giros >= MAX_CONT)
            {
                motder_tmp = V_BASE;
                motizq_tmp = V_BASE;
                switch (Direccion)
                {
                    case IZQ_STOP_DER_ADEL:
                        Direccion = IZQ_ADEL_DER_ADEL;
                        MAX_CONT = 10;
                        break;
                    case IZQ_ADEL_DER_STOP:
                        Direccion = IZQ_ADEL_DER_ADEL;
                        MAX_CONT = 10;
                        break;
                    case IZQ_ADEL_DER_ADEL:
                        if(Prueba == 1)
                        {
                            Direccion = IZQ_ADEL_DER_STOP;
                            motder_tmp = 0;
                            motizq_tmp = 150;
                        }
                        else
                        {
                            Direccion = IZQ_STOP_DER_ADEL;
                            motder_tmp = 150;
                            motizq_tmp = 0;
                        }
                        Prueba = !Prueba;
                        MAX_CONT = 10;
                        break;
                    default:
                        Direccion = IZQ_ADEL_DER_ADEL;
                        MAX_CONT = 100;
                        break;
                }
                PosicionOponente = NO_DETECTADO;
                contador_Giros = 0;
            }
        }
        else
        {
            contador_Giros = 0;
        }
        
        
        
        
        ponMotores(motizq_tmp,motder_tmp);

        digitalWrite( LED2, digitalRead( LED2 ) ^ 1 );
}

