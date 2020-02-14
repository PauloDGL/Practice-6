#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL27Z644.h"
#include "fsl_debug_console.h"
#include "GPIO.h"
#include "LCD_DISPLAY.h"
#include "ADC.h"



int main(void) {
	while(1)
	{
		fnMuestreoCO2();
	}
	return 0 ;
}

