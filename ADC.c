#include "ADC.h"
#include "MKL27Z644.h"
#include "GPIO.h"

void fnADC (void)
{
	SIM -> SCGC6 |= SIM_SCGC6_ADC0(ON); /*Activo el reloj para el ADC*/
	PORTE->PCR[20] |= PORT_PCR_MUX(OFF); /*Activo el Puerto E20 como opción de ADC*/
	ADC0->CFG1 |= ADC_CFG1_MODE(0b00);
	ADC0->SC3 |= ADC_SC3_ADCO(0b0);
	ADC0->SC1[0] = ADC_SC1_ADCH(0b00000);
}


//REGISTRO DE SOP PARA VER QUE RELOJ LE VOY A PROVEER.
//PINES CON LOS ENABLE
