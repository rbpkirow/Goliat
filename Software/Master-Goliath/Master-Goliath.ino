// KIROW - 05/12/2014 - Version 0.1 
// Robot Goliath - MASTER
//  	0/1	  Tx/Rx    D	Tx/Rx
//	2/3	  SDA/SCL  D	SDA/SCL
//	4	  4/A6	   D/A	Boton1/2 - Input

//	5/6	  PWM	   D	PWM_1/2_MI  - Output
//	9/10	  PWM	   D	PWM_1/2_MD  - Output

//	7         Int4     D    Int. Mando a dist. - Input
//	14/15/16	   D	LED1/2/3      - Output
//	A0/A1	  Anal.	   A	IS_1/2_MI   -   Input
//	A2/A3	  A2/A3	   A	IS_1/2_MD   -   Input
#include <Wire.h>
#include <TimerOne.h>


void setup()
{
  InitSystem();
  Timer1.initialize(100000);
  Timer1.attachInterrupt(PID);
  delay(500);
  //CheckSlaveCom();  
}

void loop()
{
  
  delay(1000);
}


void PID()
{
  // Interrupcion cada 40 msg para el PID
  
  
  
}
