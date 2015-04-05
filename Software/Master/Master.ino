#include "defines.h"
#include "Funciones.h"
#include <TimerOne.h>
#include <Wire.h>


void setup() 
{
  InitHw();
  bluePrintln("Selecciona la estrategia");
//  SeleccionarEstrategia();


  // Ya estamos preparados para arrancar con el mando  
  delay(500);
  bluePrintln("Iniciando!!!");


  Timer1.initialize(1500);
  Timer1.attachInterrupt( timerIsr );
}






void loop() 
{
        m_comprobarCNY = ComprobarCNY();
        UseCnyData();
        delay(1);
}


void timerIsr(void)
{
        DetectadoOponente = NO;
        DireccionAnterior = Direccion;
        _contadorPID++;
        
        
	if(_contadorPID == 30)	// Si han pasado (1500*30 usg) 45 msg, leo todos los sensores
	{
          bluePrint("Pido 4 datos");
          LeerSensores(4);
          _contadorPID = 0;
	}
	else	// Sino, solo leo los sensores digitales y los CNY
	{	
            LeerSensores(1);
            char cValor;
            bluePrint("Pido 1 datos");
            bluePrint(" - Leidos los siguientes datos: ");
            bluePrint("    cnyDer= "); itoa(cnyDer, &cValor,10); bluePrint(&cValor); 
            bluePrint("    cnyIzq= "); itoa(cnyIzq, &cValor,10); bluePrint(&cValor);
            bluePrint("    sDelDer= ");itoa(sDelDer, &cValor,10); bluePrint(&cValor);
            bluePrint("    sDelIzq= "); itoa(sDelIzq, &cValor,10); bluePrint(&cValor);
            _contadorPID = 0;
	}

        
        // --------------------------------        
        //       Sensores Delanteros
        // --------------------------------        
        if(sDelIzq == DETECTADO || sDelDer == DETECTADO)
        {
            bluePrintln("DetectadoOponente = DETECTADO_ADELANTE");
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
            bluePrintln("DetectadoOponente = NO");
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

            bluePrint("DetectadoOponente = DETECTADO_ATRAS");
        }

        
        if(DetectadoOponente == NO)
        {
            bluePrintln("DetectadoOponente = NO_DETECTADO");
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

