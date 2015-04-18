// MASTER

// En loop:
// -------
// Lectura de CNY y evitar salirse del tatami

// En cada interrupcion:
// --------------------
// 1- Peticion de datos al esclavo
// 2- Decodificacion de datos segun el formato siguiente
// 3- Movimiento de los motores segun la ubicacion del oponente

// Formato de envio:
//    _________________________________________________________________________________________________
//    |   bit 7   |   bit 6   |   bit 5   |   bit 4   |   bit 3   |   bit 2   |   bit 1   |   bit 0   |
//    |___________|___________|___________|___________|___________|___________|___________|___________|
//    | SD_DelIzq | SD_DelDer |   SD_Del  |   SD_Izq  |   SD_Der  |   SD_Tras |   CNY_I   |   CNY_D   |
//    |___________|___________|___________|___________|___________|___________|___________|___________|








#include "defines.h"
#include "Funciones.h"
#include <Wire.h>


void setup() 
{
  
  InitHw();

  
  V_BASE_INICIAL = 80;
  V_BASE = V_BASE_INICIAL;
  
  bluePrintln("Selecciona la estrategia");
//  SeleccionarEstrategia();


  // Ya estamos preparados para arrancar
  Serial1.begin(115200);
  bluePrintln("Iniciando!!!");
  Direccion = IZQ_ADEL_DER_ADEL;
  
  //FijarUmbral(125);


  digitalWrite(LED1,HIGH);
  delay(1000);
  digitalWrite(LED1,LOW);
  delay(1000);
  digitalWrite(LED1,HIGH);
  delay(1000);
  digitalWrite(LED1,LOW);
  delay(1000);
  digitalWrite(LED1,HIGH);
  delay(950);  
  digitalWrite(LED1,LOW);
}


void loop() 
{
        now = millis();
        while((millis()-now) < 4)
        {
            LeerSensores();
            m_comprobarCNY = ComprobarCNY();
            UseCnyData2();
            delayMicroseconds(500);
        }
 
        DetectadoOponente = NO;
        DireccionAnterior = Direccion;
        PosicionOponente = NO_DETECTADO;
    
        LeerSensores();
        
        
        // ------------------------------        
        //       Sensores Trasero
        // ------------------------------     
        
        if(sTras == DETECTADO)
        {
            Direccion = IZQ_ADEL_DER_ATRAS;
            V_BASE = 150;
            motder_tmp = -V_BASE;
            motizq_tmp = V_BASE;
            PosicionOponente = DETECTADO_ATRAS;
            DetectadoOponente = SI;
        }
        
        

        // ------------------------------        
        //       Sensores Derecho
        // ------------------------------  
        
        if(sDer == DETECTADO)
        {
            Direccion = IZQ_ADEL_DER_ATRAS;
            V_BASE = 150;
            motder_tmp = -V_BASE;
            motizq_tmp = V_BASE;
            PosicionOponente = DETECTADO_DERECHA;
            DetectadoOponente = SI;
        }
        
        
        // ------------------------------        
        //       Sensores Derecho
        // ------------------------------  
        
        
        if(sIzq == DETECTADO)
        {
            Direccion = IZQ_ATRAS_DER_ADEL;
            V_BASE = 150;
            motder_tmp = V_BASE;
            motizq_tmp = -V_BASE;
            PosicionOponente = DETECTADO_DERECHA;
            DetectadoOponente = SI;
        }
        
        
        
        
        // --------------------------------        
        //       Sensores Delanteros
        // --------------------------------   

        if(sDelIzq == DETECTADO || sDelDer == DETECTADO || sDel == DETECTADO)
        {
            if(sDelDer != DETECTADO)
            {
                DetectadoOponente = SI;
                V_BASE = V_BASE_INICIAL;
                contador_V_BASE = 0;
                Direccion = IZQ_ADEL_DER_ADEL;
                motizq_tmp = V_BASE + 10*(!sDelIzq);
                motder_tmp = V_BASE + 10*(!sDelDer);
                PosicionOponente = DETECTADO_ADELANTE;
            }
            else
            {
              DetectadoOponente = SI;
              V_BASE++;
              if(V_BASE > 200)
              {
                  V_BASE = 200;
                  contador_V_BASE++;
                  if(contador_V_BASE > 200)
                  {
                      V_BASE = V_BASE_INICIAL;
                      contador_V_BASE = 0;
                  }
              }
              Direccion = IZQ_ADEL_DER_ADEL;
              motizq_tmp = V_BASE + 30*(!sDelIzq);
              motder_tmp = V_BASE + 30*(!sDelDer);
              PosicionOponente = DETECTADO_ADELANTE;
            }
        }  
        
        
        
        if(DetectadoOponente == NO)
        {
            contador_Giros++;
            if(contador_Giros >= MAX_CONT)
            {
                motder_tmp = 80;
                motizq_tmp = 80;
                switch (Direccion)
                {
                    case IZQ_STOP_DER_ADEL:
                        Direccion = IZQ_ADEL_DER_ADEL;
                        MAX_CONT = 100;
                        break;
                    case IZQ_ADEL_DER_STOP:
                        Direccion = IZQ_ADEL_DER_ADEL;
                        MAX_CONT = 100;
                        break;
                    case IZQ_ADEL_DER_ADEL:
                        if(Prueba == 1)
                        {
                            Direccion = IZQ_ADEL_DER_STOP;
                            motder_tmp = 0;
                            motizq_tmp = 80;
                        }
                        else
                        {
                            Direccion = IZQ_STOP_DER_ADEL;
                            motder_tmp = 80;
                            motizq_tmp = 0;
                        }
                        Prueba = !Prueba;
                        MAX_CONT = 100;
                        break;
                    default:
                        Direccion = IZQ_ADEL_DER_ADEL;
                        MAX_CONT = 1000;
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

