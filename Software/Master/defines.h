#define BOTON_PIN A6

#define LED1 14
#define LED2 15
#define LED3 16

#define PWM_I_1  5
#define PWM_I_2  6

#define PWM_D_1  9
#define PWM_D_2 10

#define NO_P_PULSADO 0
#define P1_PULSADO 1
#define P2_PULSADO 2
#define P3_PULSADO 3

#define NEGRO 0

#define REF_P1 584
#define REF_P2 767
#define REF_P3 877
#define REF_P0 1023

#define V_MAXIMA  255

#define address   2


int valor;
int i;
int mi;
int md;


unsigned char varios;
unsigned char SA_TrasIzq;
unsigned char SA_TrasDer;
unsigned char SA_Del;

int _botonAn,_botonAn_tmp1,_botonAn_tmp2;
int Boton;
unsigned char _contadorPID;
char Pulsador;

//char Pulsador;

