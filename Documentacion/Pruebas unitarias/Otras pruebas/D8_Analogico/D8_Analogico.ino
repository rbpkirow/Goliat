int valor;
int i;

void setup() 
{
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  valor = 0;
  i = 128;
  analogWrite(10,i);
}

void loop() 
{
  analogWrite(10,i);
  
  valor = analogRead(0);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(1);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(2);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(3);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(4);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(5);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(6);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(7);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(8);
  Serial.print(valor);
  Serial.print(" : ");
  valor = analogRead(11);
  Serial.println(valor);
  delay(800);
}

