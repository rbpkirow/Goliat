/*
IBT-2 Motor Control Board driven by Arduino.
 
 Speed and direction controlled by a potentiometer attached to analog input 0.
 One side pin of the potentiometer (either one) to ground; the other side pin to +5V
 
 Connection to the IBT-2 board:
 IBT-2 pin 1 (RPWM) to Arduino pin 5(PWM)
 IBT-2 pin 2 (LPWM) to Arduino pin 6(PWM)
 IBT-2 pins 3 (R_EN), 4 (L_EN), 7 (VCC) to Arduino 5V pin
 IBT-2 pin 8 (GND) to Arduino GND
 IBT-2 pins 5 (R_IS) and 6 (L_IS) not connected
 */

int RPWM_Output = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output = 6; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)
  int prueba = 0;
void setup()
{
  Serial.begin(9600);
  // Modificacion de la frecuencia de PWM
//  TCCR5B = TCCR5B & 0b000 | 0x02;  // Frecuencia de la patilla 44,45,46  -- No modifica delay
//  TCCR4B = TCCR4B & 0b000 | 0x02;  // Frecuencia de la patilla 6,7,8  -- No modifica delay
//  TCCR3B = TCCR3B & 0b000 | 0x02;  // Frecuencia de la patilla 2,3,5  -- No modifica delay
  TCCR2B = TCCR2B & 0b000 | 0x02;  // Frecuencia de la patilla 9,10  -- No modifica delay    -- Rango de PWM = [0-255]
//  TCCR1B = TCCR1B & 0b000 | 0x02;  // Frecuencia de la patilla 11,12  -- No modifica delay
//  TCCR0B = TCCR0B & 0b000 | 0x02;  // Frecuencia de la patilla 4,13  -- Modifica delay  -- NO TOCAR!!!!!!!
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(51, OUTPUT);  
  
  int reversePWM = 512;
  analogWrite(2, 100);
  analogWrite(3, 100);
  analogWrite(4, 100);
  analogWrite(5, 100);
  analogWrite(6, 100);
  analogWrite(7, 100);
  analogWrite(8, 100);
  analogWrite(9, 100);
  analogWrite(10, 100);
  analogWrite(11, 100);
  analogWrite(12, 100);
  analogWrite(13, 100);
  analogWrite(44, 100);
  analogWrite(45, 100);
  analogWrite(46, 100);


}

void loop()
{
  analogWrite(9, 255);
  analogWrite(10, 0);   
  delay(100);  
//  analogWrite(9, 0);
//  analogWrite(10, 511);
//  delay(100);  
}




