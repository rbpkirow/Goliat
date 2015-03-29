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
}


