/* Copyright 2015,
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Signal acquisition using the ADC in burst mode
 **
 **/

/*
 * Initials     Name
 * ---------------------------
 *	GP			Germán Pressel Coretto
 */

/*==================[inclusions]=============================================*/
#include "ADCburst_baremetal.h"       /* <= own header */

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

#include "led.h"
#include "uart.h"
#include "adc.h"


/*==================[macros and definitions]=================================*/

#define REDUCE_RATE_FACTOR 10000

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */



int main(void)
{
   /* perform the needed initialization here */
    uint8_t ADCData[10];
    uint32_t rate= 70000; /*La frecuencia minima de adquisición es 800 kHz, luego se lo debe dividir por (Numero_bits_conversion + 1),
    						se reduce la frecuencia de muestreo por software por debajo de este limite.*/
    uint8_t burst=1;
    uint16_t i=0,Reduce_Rate;

    /* Configuración del GPIO */
    Initialization_Leds();

    /* Configuración del ADC */
    Initialization_ADC(ADC_CH1);
    Config_ADC(ADC_8BITS, burst, rate);

    /*Configuracion de la UART- USB*/
    Initialization_UART2();
    Set_Baud_UART2(115200);
    Tx_Enable_UART2();

    /*En modo BURST, no se debe iniciar la conversion*/
    Clear_Start_ADC();

	while (1){
				//Reduce_Rate=0;
				//while(Reduce_Rate<REDUCE_RATE_FACTOR){
				while(Conversion_End_ADC(ADC_CH1))
					{}
					Read_ADC(ADC_CH1,&ADCData[i]);
				//	Reduce_Rate++;
				//}
				if(i==10){
					Send_Data_UART2(&ADCData[0],10);
					i=0;
				}
				else{
					i++;
				}
	}
		return 0;
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

