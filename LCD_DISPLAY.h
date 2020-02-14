#define AA 0x41
#define BB 0x42
#define CC 0x43
#define DD 0x44
#define EE 0x45
#define F 0x46
#define G 0x47
#define H 0x48
#define I 0x49
#define J 0x4A
#define K 0x4B
#define L 0x4C
#define M 0x4D
#define N 0x4E
#define O 0x4F
#define P 0x50
#define Q 0x51
#define RR 0x52
#define S 0x53
#define T 0x54
#define U 0x55
#define V 0x56
#define W 0x57
#define X 0x58
#define Y 0x59
#define Z 0x5A
#define DOSPUNTOS 0x3A
#define ESPACIO 0x20
#define PRIMERALINEA 0x80
#define SEGUNDALINEA 0xC0
#define PORCIENTO 0x25
#define CERO 0x30
#define UNO 0x31
#define DOS 0x32
#define TRES 0x33
#define CUATRO 0x34
#define CINCO 0x35
#define SEIS 0x36
#define SIETE 0x37
#define OCHO 0x38
#define NUEVE 0x39
#define NUMEROBASE 0x30
#define SEGUNDO 925926 /*La duración de un segundo*/
#define NUMERO 2 /*Define durante cuanto tiempo se quiere visualizar el resultado*/
#define CONVERSION_ADC 0x4003b010

extern void fnDelay(void);
extern void fnLCD_Enable(int bPulso);
extern void fnRS_DATAorINSTRUCTION (int bModo);
extern void fnLCD_Inicializacion(void);
extern void fnClearScreen (void);
extern void fnLCD_CambiardeFila(int bLinea);
extern void fnMensaje(void);
extern void fnPorcentaje(int bResultado);
extern void fnSeg(void);
extern void fnMuestreoCO2(void);
extern void fnErrordeMuestreo(void);
