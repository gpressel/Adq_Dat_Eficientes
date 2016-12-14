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

/** \brief  Signal acquisition using the ADC in pooling mode
 **
 **/

/*
 * Initials     Name
 * ---------------------------
 *	GP			Germán Pressel Coretto
 */


/*==================[inclusions]=============================================*/
#include "ADCpooling_baremetal.h"       /* <= own header */

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

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


int main(void)
{
   /* perform the needed initialization here */
    uint16_t ADCData;
    uint32_t rate=10;
    uint8_t burst=0;

   /* Configuración del GPIO */
    Initialization_Leds();

	/* Configuración del ADC */
    Initialization_ADC(ADC_CH1);
    Config_ADC(ADC_8BITS, burst=0, rate);

	/*Configuracion de la UART- USB*/
    Initialization_UART2();
    Set_Baud_UART2(115200);
    Tx_Enable_UART2();

	while(1)
	{
		/*Inicia la conversion y espera a que se complete*/
		Set_Start_ADC();
		while(Conversion_End_ADC(ADC_CH1))
		{		}

		/*Una vez finalizada, lee el dato y lo envia por la UART*/
		Read_ADC(ADC_CH1,&ADCData);

		/*Enviar datos en formato ascii*/
		Send_Data_UART2((uint8_t*)&ADCData,1);
		Toggle_Led(RED);
		/*Enviar datos en formato char*/
			//Send_Char_UART2(&ADCData,1);
	}
	return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

