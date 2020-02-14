#include "MKL27Z644.h"

void fnTurnOn_Clks (void)
{
	SIM->SCGC5=0x3E00;
}

