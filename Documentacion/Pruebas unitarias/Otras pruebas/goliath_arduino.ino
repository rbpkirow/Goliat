#include <TimerOne.h>

#define _Digole_Serial_UART_  //To tell compiler compile the special communication only, 

#define LCDCol 20
#define LCDRow 4

#define LED 13
#define MOTOR_DER_A  9
#define MOTOR_DER_B  10
#define MOTOR_IZQ_A  11
#define MOTOR_IZQ_B  12
#define NEGRO 0
#define REFERENCIA 6
#include <DigoleSerial.h>

    int KP, KD, direccion, direccionAnt, errorProp, errorPropAnt;
    int Velocidad;
    int pd;
    int pi;
    int arraySensores[10];
    DigoleSerialDisp mydisp(&Serial3, 9600);


void InicializarVariables()
{
    KP = 0;
    KD = 0;
    Velocidad = 0;  
    analogWrite(MOTOR_IZQ_A,0);
    analogWrite(MOTOR_IZQ_B,0);
    analogWrite(MOTOR_DER_A,0);
    analogWrite(MOTOR_DER_B,0);
}


void setup() 
{
  Serial.begin(115200);  // Inicio del bluetooth
  
// Modificacion de la frecuencia de PWM
//  TCCR5B = TCCR5B & 0b000 | 0x02;  // Frecuencia de la patilla 44,45,46  -- No modifica delay
//  TCCR4B = TCCR4B & 0b000 | 0x02;  // Frecuencia de la patilla 6,7,8  -- No modifica delay
//  TCCR3B = TCCR3B & 0b000 | 0x02;  // Frecuencia de la patilla 2,3,5  -- No modifica delay
  TCCR2B = TCCR2B & 0b000 | 0x02;  // Frecuencia de la patilla 9,10  -- No modifica delay    -- Rango de PWM = [0-255]
  TCCR1B = TCCR1B & 0b000 | 0x02;  // Frecuencia de la patilla 11,12  -- No modifica delay
//  TCCR0B = TCCR0B & 0b000 | 0x02;  // Frecuencia de la patilla 4,13  -- Modifica delay  -- NO TOCAR!!!!!!!

  InicializarVariables();
  ResetDisplay();

  Timer1.initialize(1000); // set a timer of length 1000 microseconds (or 1 msec)
  Timer1.attachInterrupt( timer1_Isr ); // attach the service routine here
    
  mydisp.drawStr(1, 0, "Config de Goliath"); //display string at: x=4, y=0

}

void EscribirPID_Display(int row)
{
    mydisp.drawStr(0, row, "P=");
    mydisp.drawStr(7, row, "D=");
    mydisp.drawStr(14, row, "V=");
    mydisp.setPrintPos(2, row);
    mydisp.print(KP,DEC);
    mydisp.setPrintPos(9, row);
    mydisp.print(KP,DEC);
    mydisp.setPrintPos(16, row);
    mydisp.print(Velocidad,DEC);
}


void loop() 
{

}

/// ----------------------------------
/// Interrupcion del Timer1 == PID
/// ----------------------------------
void timer1_Isr()
{
    // Interrupcion del PID
    LeerSensores();
    pd = PrimD();
    pi = PrimI();
    direccion = pd + pi;

    if(direccion == 0) 
        direccion = direccionAnt;
    else
        direccionAnt = direccion;

    errorProp = direccion - REFERENCIA;    
    
    Velocidad = PID_VELOCIDAD();
    
    PID(errorProp,errorPropAnt, Velocidad);
}

