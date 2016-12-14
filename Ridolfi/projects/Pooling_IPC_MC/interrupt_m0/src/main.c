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
#include "chip.h"


/*==================[macros and definitions]=================================*/
const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;
uint16_t* Write_Ptr= NULL;

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

void pause_time(uint32_t time){
	uint32_t time_mult=1000;
	while(time!=0){
		while(time_mult!=0){
			time_mult--;
		}
		time--;
	}
}
/*==================[internal data definition]===============================*/

/** @brief used for delay counter */


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
//void MX_CORE_IRQHandler(void){
	//Toggle_Led(YELLOW);
//}

void Send_Interrupt_Core(void){
	Chip_CREG_SetM0Event();
	pause_time(200);
	Toggle_Led(YELLOW);
}


/*==================[external functions definition]==========================*/


int main(void)
{
   /* perform the needed initialization here */

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	Write_Ptr=(uint16_t*)ADDRESS_TO_WRITE;

	uint32_t rate=100;
	uint8_t burst=0;

		/* Configuración del ADC */
	Initialization_ADC(ADC_CH1);
	Config_ADC(ADC_8BITS, burst=0, rate);
	while(1)
	{
		Set_Start_ADC();
		while(Conversion_End_ADC(ADC_CH1)){

		}
		Read_ADC(ADC_CH1,Write_Ptr);
		pause_time(200);
		Toggle_Led_RGB(BLUE);
		Send_Interrupt_Core();
	}
	return 0;
}
/*==================[end of file]============================================*/
