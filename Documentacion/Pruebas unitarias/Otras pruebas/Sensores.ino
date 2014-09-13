int LeerSensorCentral(void)
{
  return analogRead(A0);
}

void LeerSensores()
{
  arraySensores[0] = analogRead(A1);
}

int PrimD(void)
{
   if(arraySensores[0] == NEGRO)  return 1;
   if(arraySensores[1] == NEGRO)  return 2;
   if(arraySensores[2] == NEGRO)  return 3;
   if(arraySensores[3] == NEGRO)  return 4;
   if(arraySensores[4] == NEGRO)  return 5;
   if(arraySensores[5] == NEGRO)  return 6;
   if(arraySensores[6] == NEGRO)  return 7;
   if(arraySensores[7] == NEGRO)  return 8;
   return 0;
}


int PrimI(void)
{
   if(arraySensores[7] == NEGRO)  return 8;
   if(arraySensores[6] == NEGRO)  return 7;
   if(arraySensores[5] == NEGRO)  return 6;
   if(arraySensores[4] == NEGRO)  return 5;
   if(arraySensores[3] == NEGRO)  return 4;
   if(arraySensores[2] == NEGRO)  return 3;
   if(arraySensores[1] == NEGRO)  return 2;
   if(arraySensores[0] == NEGRO)  return 1;
   return 0;
}
