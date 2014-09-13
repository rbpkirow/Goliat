int PID_VELOCIDAD(void)
{
  // sensorDelantero = [0,1024]
  int _sensorDelantero = LeerSensorCentral();
  return (_sensorDelantero/8); // = [0,128]
}


void PID(long _error, long _errorAnt, long _Velocidad)
{
    int valorPID;
    int V_Motor_Der;
    int V_Motor_Izq;

    valorPID = KP*(_error) + KD*(_error - _errorAnt);

    errorPropAnt = _error;

    V_Motor_Izq = _Velocidad + valorPID;
    V_Motor_Der = _Velocidad - valorPID;


    SetPWM(V_Motor_Izq,V_Motor_Der);    
}



void SetPWM(int _motorIzquierdo, int _motorDerecho)
{
    if(_motorIzquierdo >=0)
    {
        analogWrite(0,MOTOR_IZQ_A);
        analogWrite(_motorIzquierdo,MOTOR_IZQ_B);
    }
    else
    {
        analogWrite(_motorIzquierdo,MOTOR_IZQ_A);
        analogWrite(0,MOTOR_IZQ_B);
    }

    if(_motorDerecho >=0)
    {
        analogWrite(0,MOTOR_DER_A);
        analogWrite(_motorDerecho,MOTOR_DER_B);
    }
    else
    {
        analogWrite(_motorDerecho,MOTOR_DER_A);
        analogWrite(0,MOTOR_DER_B);
    }
}

