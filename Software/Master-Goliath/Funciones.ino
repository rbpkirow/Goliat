#define ID_SLAVE  4

#define LED1  14
#define LED2  15
#define LED3  16

#define BOTONx  4

#define PWM1_I  5
#define PWM2_I  6
#define PWM1_D  9
#define PWM2_D  10

#define IS_1_I  A0
#define IS_2_I  A1
#define IS_1_D  A2
#define IS_2_D  A3

void InitSystem()
{
  // Modificacion de la frecuencia de PWM --> 4 KHz de PWM
  TCCR4B = TCCR4B & 0b000 | 0x04;  // PWM-6
  TCCR3B = TCCR3B & 0b000 | 0x02;  // PWM-5
  TCCR1B = TCCR1B & 0b000 | 0x02;  // PWM-9-10
  TCCR0B = TCCR0B & 0b000 | 0x03;  // PWM-3 --> AFECTA A DELAY. Valor por defecto = 0x03

  // Configuracion de perifericos
  Serial.begin(115200);
  Serial.print("Iniciando el sistema.");

  Wire.begin();  // I2C como Maestro  
  Serial.print(".");
  
  pinMode(BOTONx, INPUT);
  pinMode(LED1, OUTPUT); // LED
  pinMode(LED2, OUTPUT); // LED  
  pinMode(LED3, OUTPUT); // LED
  Serial.print(".");
  
  pinMode(PWM1_I, OUTPUT);  // PWM
  analogWrite(PWM1_I, 0);
  pinMode(PWM2_I, OUTPUT);  // PWM
  analogWrite(PWM2_I, 0);
  pinMode(PWM1_D, OUTPUT);  // PWM
  analogWrite(PWM1_D, 0);
  pinMode(PWM2_D, OUTPUT);  // PWM
  analogWrite(PWM2_D, 0);

  pinMode(IS_1_I, INPUT);  // IS
  pinMode(IS_2_I, INPUT);  // IS
  pinMode(IS_1_D, INPUT);  // IS
  pinMode(IS_2_D, INPUT);  // IS  
  
  Serial.println(".");
  
  attachInterrupt(4,Interrupcion,CHANGE); // Interrupcion en la patilla 7 del arduino
}

void CheckSlaveCom()
{
  Serial.print("Comprobando comunicacion con esclavo...");
//  Wire.beginTransmission(ID_SLAVE);
//  Wire.endTransmission();
  delay(100);  
}
