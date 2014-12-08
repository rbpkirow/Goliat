// Prueba de frecuencias PWM en arduino Micro


void setup()
{
  // Modificacion de la frecuencia de PWM --> 4 KHz de PWM
  TCCR4B = TCCR4B & 0b000 | 0x04;  // PWM-6
  TCCR3B = TCCR3B & 0b000 | 0x02;  // PWM-5
  TCCR1B = TCCR1B & 0b000 | 0x02;  // PWM-9-10
  TCCR0B = TCCR0B & 0b000 | 0x03;  // PWM-3 --> AFECTA A DELAY. Valor por defecto = 0x03
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);  // PWM
  pinMode(5, OUTPUT);  // PWM
  pinMode(6, OUTPUT);  // PWM
  pinMode(9, OUTPUT);  // PWM
  pinMode(10, OUTPUT);  // PWM
  
  analogWrite(3, 128);
  analogWrite(5, 128);
  analogWrite(6, 128);
  analogWrite(9, 128);
  analogWrite(10, 128);
}

void loop()
{
  delay(10);
  digitalWrite(2,LOW);
  delay(10);
  digitalWrite(2,HIGH);
}




