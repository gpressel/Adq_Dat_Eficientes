/* Copyright 2016,
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

/** \brief Driver DMA (Baremetal)
 **
 **/


/*
 * Initials     Name
 * ---------------------------
 *    GP	    Germán Pressel Coretto
 */

/*==================[inclusions]=============================================*/
#include "chip.h"
#include "gpdma.h"
#include "gpio.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void Initialization_GPDMA(void){
	Chip_GPDMA_Init(LPC_GPDMA);
}

void Set_GPDMA_Interrupt(void){
	NVIC_DisableIRQ(DMA_IRQn);
	NVIC_SetPriority(DMA_IRQn,((0x01<<3)|0x01));
	NVIC_EnableIRQ(DMA_IRQn);
}

void Get_GPDMA_FreeChannel(uint8_t *Channel, uint8_t Peripheric){
	*Channel=Chip_GPDMA_GetFreeChannel(LPC_GPDMA,Peripheric);
}

uint8_t Status_GPDMA_Interrupt(uint8_t Channel){
	uint8_t Status;
	if(Chip_GPDMA_Interrupt(LPC_GPDMA, Channel)==0){
		return Status=0;
	}
	else{
		return Status=1;
	}
}

void Transfer_GPDMA_P2M(uint8_t Channel,uint8_t Peripheric,uint32_t* Data, uint32_t transfer_size){
	Chip_GPDMA_Transfer(LPC_GPDMA,Channel,Peripheric,Data,GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,transfer_size);
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
