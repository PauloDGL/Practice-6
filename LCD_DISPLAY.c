#include "board.h"
#include "clock_config.h"
#include "MKL27Z644.h"
#include "LCD_DISPLAY.h"
#include "GPIO.h"
#include <stdio.h>
#include "ADC.h"


void fnLCD_Enable(int bPulso) /*Función para habilitar el ENABLE*/
{
	if (bPulso == 1)
	{
	fnDigitalwrite (E, 0, ON); /*Manda el pulso positivo*/
	fnDelay(); /*Hace un Delay para alcanzar a tomar el pulso*/
	fnDigitalwrite (E, 0, OFF);/*Manda el pulso negativo*/
	}
}

void fnRS_DATAorINSTRUCTION(int bModo) /*Función capaz de configurar el RS para mandar comandos o datos*/
{
	if(bModo == 1) /*Para mandarle un dato*/
	{
		fnDigitalwrite (E, 1, ON);
	}
	else if (bModo == 0) /*Para mandarle comando*/
	{
		fnDigitalwrite (E, 1, OFF);
	}
}

void fnClearScreen (void) /*Función para limpiar la Pantalla*/
{
	fnDigitalwrite (E, 1, OFF);
	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= 0x01;
	fnLCD_Enable(1);
}

void fnLCD_Inicializacion(void) /*Inicialización de los puertos*/
{
long *dwgpClockenabled; /*Apuntador para habilitar los relojes de los puertos*/

	dwgpClockenabled = (long *) SIM5; /*Se da para activar los relojes de los puertos*/
	*dwgpClockenabled = CLOCK_ON;

	fnPinMODE (E, 0, OUTPUT); /*Se selecciona los pines que seran RS (E1) y los de ENABLE (E0)*/
	fnPinMODE (E, 1, OUTPUT);

	fnPinMODE (D, 0, OUTPUT); /*Se seleccionan los pines que van a ser los 8 bits para controlar el LCD*/
	fnPinMODE (D, 1, OUTPUT);
	fnPinMODE (D, 2, OUTPUT);
	fnPinMODE (D, 3, OUTPUT);
	fnPinMODE (D, 4, OUTPUT);
	fnPinMODE (D, 5, OUTPUT);
	fnPinMODE (D, 6, OUTPUT);
	fnPinMODE (D, 7, OUTPUT);

	fnDigitalwrite (E, 1, OFF); /*Prende la pantalla en el modo de 8-bits*/
	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= 0x38; /*Manda instruccion para modo de 8-bits*/
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= 0x0F; /*Display on, cursor blinking para modo de 8-bits*/
	fnLCD_Enable(1);
}

void fnMensaje(void) /*Función para enviar mensaje en la primera linea sobre medición de CO2*/
{
	/*Escribo mensaje de la distancia es y me coloco en la segunda línera*/
	fnDigitalwrite (E, 1, ON);
	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= P;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= O;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= RR;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= CC;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= EE;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= N;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= T;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= AA;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= J;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= EE;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= ESPACIO;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= DD;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= EE;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= CC;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= O;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= DOS;
	fnLCD_Enable(1);
}

void fnLCD_CambiardeFila(int bLinea) /*Función capaz de determinar en que fila quiere escribir*/
{
	fnDigitalwrite (E, 1, OFF);

	if(bLinea == 1)
	{
	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= PRIMERALINEA; /*Manda instruccion para modo de 8-bits*/
	fnLCD_Enable(1);
	}
	else if(bLinea == 2)
	{
	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= SEGUNDALINEA; /*Manda instruccion para modo de 8-bits*/
	fnLCD_Enable(1);
	}
}

void fnPorcentaje(int bResultado) /*Función donde se lleva a cabo el procesamiento del dato para mostrarlo*/
{

int bMillares= bResultado/1000;
int bCentenas= (bResultado-(bMillares*1000))/100;
int bDecenas= (bResultado-(bMillares*1000+bCentenas*100))/10;
int bUnidades= (bResultado-(bMillares*1000+bCentenas*100+bDecenas*10));

	fnDigitalwrite (E, 1, ON);


	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= NUMEROBASE + bMillares;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= NUMEROBASE + bCentenas;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= NUMEROBASE + bDecenas;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= NUMEROBASE + bUnidades;
	fnLCD_Enable(1);

	GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
	GPIOD->PDOR |= PORCIENTO;
	fnLCD_Enable(1);
}

void fnMuestreoCO2(void) /*Función donde se va tomando el muestreo*/
{
long *pdwResultado;
int bgResultado;

		fnLCD_Inicializacion();
		fnLCD_CambiardeFila(1);
		fnMensaje();
		fnLCD_CambiardeFila(2);
		fnADC();
		pdwResultado = (long *) CONVERSION_ADC;
		printf("%d\n", *pdwResultado);
		bgResultado = 0 + (*pdwResultado * 5.5);
		if(bgResultado >= 500)
		{
			fnPorcentaje(bgResultado);
		}
		else if(bgResultado < 500)
		{
			fnErrordeMuestreo();
		}
		fnSeg();
		fnClearScreen();
}

void fnErrordeMuestreo(void)
{
	/*Escribo mensaje de que el rango de medicion es muy bajo y me coloco en la segunda línera*/
		fnDigitalwrite (E, 1, ON);
		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= M;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= U;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= EE;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= S;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= T;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= RR;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= AA;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= ESPACIO;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= EE;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= RR;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= RR;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= O;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= N;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= EE;
		fnLCD_Enable(1);

		GPIOD->PDOR &= ~(0xFF); /*Limpia mis salidas*/
		GPIOD->PDOR |= AA;
		fnLCD_Enable(1);
}

void fnDelay() /*Delay para que el LCD alcance a detectar el pulso del ENABLE*/
{
	long dwDelay = 29000;

	for (long dwCuenta=0; dwCuenta < dwDelay; dwCuenta++)
		dwCuenta += 1;
}

void fnSeg(void)
{
long dwDelay = NUMERO * SEGUNDO;

	for (long dwCuenta=0; dwCuenta < dwDelay; dwCuenta++) /*Realiza una cuenta hasta 925926, que es igual a esperar un segundo*/
		dwCuenta += 1;

return;
}

