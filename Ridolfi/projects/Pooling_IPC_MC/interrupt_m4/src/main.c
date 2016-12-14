/* Copyright 2016, German Pressel
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

/** @brief Multicore Data Acquisition(M4 core)
 */

/*==================[inclusions]=============================================*/

#include "main.h"
#include "led.h"
#include "uart.h"
#include "chip.h"
#include "cr_start_m0.h"

/*==================[macros and definitions]=================================*/
const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/** @brief delay function
 * @param t desired milliseconds to wait
 */





/*==================[internal data definition]===============================*/



/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/** @brief delay function
 * @param t desired milliseconds to wait
 */



void pause_time(uint32_t time){
	uint32_t time_mult=100;
	while(time!=0){
		while(time_mult!=0){
			time_mult--;
		}
		time--;
	}
}


void M0APP_IRQHandler(void){
	pause_time(1000);
	Send_Data_UART2((uint8_t*)ADDRESS_TO_READ,1);
	Toggle_Led_RGB(RED);
	Chip_CREG_ClearM0AppEvent();
	NVIC_ClearPendingIRQ(1);

}

/*==================[external functions definition]==========================*/


int main(void)
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	Initialization_Leds();


	Initialization_UART2();
	Set_Baud_UART2(1152000);
	Tx_Enable_UART2();

	TurnOn_Led(GREEN);
	NVIC_EnableIRQ(1);
	/* Boot M0 core, using reset vector and stack pointer from the CM0+
	   image in FLASH. */
	cr_start_m0(SLAVE_M0APP, (uint8_t *)0x1B000000);
	//TurnOff_Led(GREEN);

	while (1)
	{

		__WFI();

	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
