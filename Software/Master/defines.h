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
#define BLANCO 1

#define REF_P1 584
#define REF_P2 767
#define REF_P3 877
#define REF_P0 1023

#define V_MAXIMA  255

#define address   2

#define LEIDO_CNY_NONE  0
#define LEIDO_CNY_BOTH  1
#define LEIDO_CNY_D     2
#define LEIDO_CNY_I     3

#define NO_DETECTADO        0
#define DETECTADO_ADELANTE  1
#define DETECTADO_DERECHA   2
#define DETECTADO_IZQUIERDA 3
#define DETECTADO_ATRAS     4

#define NUM_LECTURAS_CNY 4

int valor;
int i;
int mi;
int md;

unsigned int TIME;

unsigned char varios;
unsigned char SA_TrasIzq;
unsigned char SA_TrasDer;
unsigned char SA_Del;

int _botonAn,_botonAn_tmp1,_botonAn_tmp2;
int Boton;
unsigned char _contadorPID;
char Pulsador;
char m_comprobarCNY;
char PosicionOponente;


unsigned char sAux,cnyDer,cnyIzq,sTras,sDer,sIzq,sDelDer,sDelIzq;  // todos son digitales

char contadorCNY_I;
char contadorCNY_D;
char contadorCNY_Ambos;

