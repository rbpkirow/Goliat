#define BOTON_PIN A6

#define LED1 14
#define LED2 15
#define LED3 16

#define PWM_I_1  5
#define PWM_I_2  6

#define PWM_D_1  9
#define PWM_D_2 10

#define CNY_D  7
#define CNY_I  8

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

#define SLAVE_ADD   2

#define LEIDO_CNY_NONE  0
#define LEIDO_CNY_BOTH  1
#define LEIDO_CNY_D     2
#define LEIDO_CNY_I     3

#define NO_DETECTADO        0
#define DETECTADO_ADELANTE  1
#define DETECTADO_DERECHA   2
#define DETECTADO_IZQUIERDA 3
#define DETECTADO_ATRAS     4

#define NUM_LECTURAS_CNY 10


// Direcciones de movimiento
#define NOSE		                0 //   |  MI   |  MD   |
                                  //   |       |       |
#define IZQ_ATRAS_DER_ATRAS		1 //   |   -1  |   -1  |
#define IZQ_ATRAS_DER_STOP		2 //   |   -1  |    0  |
#define IZQ_ATRAS_DER_ADEL		3 //   |   -1  |    1  |
#define IZQ_STOP_DER_ATRAS		4 //   |    0  |   -1  |
#define IZQ_STOP_DER_STOP		5 //   |    0  |    0  |
#define IZQ_STOP_DER_ADEL		6 //   |    0  |    1  |
#define IZQ_ADEL_DER_ATRAS		7 //   |    1  |   -1  |
#define IZQ_ADEL_DER_STOP		8 //   |    1  |    0  |
#define IZQ_ADEL_DER_ADEL      	        9 //   |    1  |    1  |
#define PARADO                         10 // Igual que stop-stop

#define NO		0
#define	SI		1

#define DETECTADO 	0


int valor;
int i;
int mi;
int md;

unsigned int TIME;

unsigned char varios;

int _botonAn,_botonAn_tmp1,_botonAn_tmp2;
int Boton;
char Pulsador;
char m_comprobarCNY;
char PosicionOponente;


unsigned char sCnyD, sCnyI, sTras, sDer, sIzq, sDelDer, sDelIzq, sDel;  // todos son digitales

char contadorCNY_I;
char contadorCNY_D;
char contadorCNY_Ambos;

int motizq_tmp;
int motder_tmp;
unsigned char contador_V_BASE;
int V_BASE;
int V_BASE_INICIAL;

char Direccion;
char DireccionAnterior;
char DetectadoOponente;

unsigned char MAX_CONT;
unsigned char contador_Giros;
char Prueba;
char EnviarDatos;

unsigned long now;


