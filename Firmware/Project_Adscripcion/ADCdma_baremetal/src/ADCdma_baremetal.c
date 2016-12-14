/* Copyright 2015, German Pressel Coretto
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

/** \brief  Signal acquisition using the ADC in burst mode and
 * sending the converted data through DMA.
 **
 **/

/*
 * Initials     Name
 * ---------------------------
 *	GP			Germán Pressel Coretto
 */

/*==================[inclusions]=============================================*/
#include "ADCdma_baremetal.h"       /* <= own header */

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

#include "timer.h"
#include "uart.h"
#include "gpdma.h"
#include "adc.h"
#include "led.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
uint32_t Buffer_DMA[40];
uint8_t Channel_Num;
uint8_t channelTC;
uint32_t trial=0,indice=0;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void DMA_IRQHandler(void);
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
    uint32_t rate=5000;
    uint8_t burst=1;
    uint16_t i;

    /* Configuración del GPIO */
       Initialization_Leds();

	/*Configuracion del DMA*/
       Initialization_GPDMA();
       Set_GPDMA_Interrupt();
       Get_GPDMA_FreeChannel(&Channel_Num,GPDMA_CONN_ADC_0);

	/* Configuración del ADC */
       Initialization_ADC(ADC_CH1);
       Config_ADC(ADC_8BITS, burst, rate);
       Set_ADC_Interrupt(ADC_CH1);  // Do not remove this line or the DMAIRQ will never be called.

	/*Configuracion de la UART- USB*/
       Initialization_UART2();
	   Set_Baud_UART2(115200);
	   Tx_Enable_UART2();

	while (1){

		channelTC=0;
		while(!channelTC){

			while(Conversion_End_ADC(ADC_CH1)){}
			Transfer_GPDMA_P2M(Channel_Num,GPDMA_CONN_ADC_0,(uint32_t*)&Buffer_DMA[i],1);
			i++;
		}
		if(i==40){i=0;}

	}
		return 0;
}


void DMA_IRQHandler(void){
	uint8_t dataAdc;
	if(Status_GPDMA_Interrupt(Channel_Num)){
		dataAdc=(uint8_t)(Buffer_DMA[indice]>>8);
		Send_Data_UART2(&dataAdc,1);
		indice++;
		if(indice==40){
			indice=0;
		}
	}
	channelTC=1;
}




/*
 * void Init_DMA (void){

	Chip_GPDMA_Init(LPC_GPDMA);
	NVIC_DisableIRQ(DMA_IRQn);
	NVIC_SetPriority(DMA_IRQn,((0x01<<3)|0x01));
	NVIC_EnableIRQ(DMA_IRQn);
	LPC_GPDMA->SOFTBREQ |= (1<<13);
	LPC_GPDMA->CONFIG|=(1<<0);
	LPC_GPDMA->CH[1].SRCADDR=0x400e3004;
	LPC_GPDMA->CH[1].DESTADDR=0x100000a8;
	LPC_GPDMA->CH[1].LLI=0;
	LPC_GPDMA->CH[1].CONTROL|=0x89489001;
	LPC_GPDMA->CH[1].CONFIG|=0x0000101b;
} */

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

