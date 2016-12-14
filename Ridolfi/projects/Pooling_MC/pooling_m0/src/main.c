/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
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

/** @brief blink Multicore blink example for LPC54102 (M0 core)
 *
 */

/*==================[inclusions]=============================================*/

#include "main.h"
#include "led.h"
#include "adc.h"
#include "uart.h"
//#include "board.h"

/*==================[macros and definitions]=================================*/
const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;

uint32_t ADCData;
extern uint32_t *Data_ADC;
Data_ADC=&ADCData;

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/

/** @brief used for delay counter */


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/



/*==================[external functions definition]==========================*/


int main(void)
{
   /* perform the needed initialization here */

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);


    uint32_t rate=100;
    uint8_t burst=0;

	/* Configuración del ADC */
    Initialization_ADC(ADC_CH1);
    Config_ADC(ADC_8BITS, burst=0, rate);

	/*Configuracion de la UART- USB*/
    Initialization_UART2();
    Set_Baud_UART2(57600);
    Tx_Enable_UART2();

	while(1)
	{
		/*Inicia la conversion y espera a que se complete*/
		Set_Start_ADC();
		//Toggle_Led_RGB(BLUE);
		//uint8_t send= 10;
		//while(send!=0){
		while(Conversion_End_ADC(ADC_CH1))
		{

		}

		/*Una vez finalizada, lee el dato y lo envia por la UART*/
		Read_ADC(ADC_CH1,(uint32_t*)&ADCData);
		/*Enviar datos en formato ascii*/
		//send--;
		//}

		//Send_Data_UART2(&ADCData,1);
		/*Enviar datos en formato char*/
//Send_Char_UART2(&ADCData,1);
	}
	return 0;
}
/*==================[end of file]============================================*/
