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

/** \brief Driver ADC (Baremetal)
 **
 **/


/*
 * Initials     Name
 * ---------------------------
 *    GP	    Germán Pressel Coretto
 */

/*==================[inclusions]=============================================*/
#include "chip.h"
#include "adc.h"
#include "gpio.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/

uint32_t ADC_0=0;
ADC_CLOCK_SETUP_T ADC_CLOCK_SETUP_PARAM;

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void Initialization_ADC(uint8_t adc_channel){
	Chip_SCU_ADC_Channel_Config(ADC_0,adc_channel);
	Chip_ADC_Init(LPC_ADC0,&ADC_CLOCK_SETUP_PARAM);
	Chip_ADC_EnableChannel(LPC_ADC0,adc_channel,ENABLE);
};

void Config_ADC(uint8_t nbits, uint8_t burst_mode, uint32_t fire_rate){
	ADC_CLOCK_SETUP_PARAM.bitsAccuracy=nbits;
	ADC_CLOCK_SETUP_PARAM.burstMode=burst_mode;
	ADC_CLOCK_SETUP_PARAM.adcRate=fire_rate;
	Chip_ADC_SetResolution(LPC_ADC0,&ADC_CLOCK_SETUP_PARAM,nbits);
	Chip_ADC_SetSampleRate(LPC_ADC0,&ADC_CLOCK_SETUP_PARAM,fire_rate);
	if (ADC_CLOCK_SETUP_PARAM.burstMode==1){
		Chip_ADC_SetBurstCmd(LPC_ADC0,ENABLE);
	}
	else{}
}

void Set_Start_ADC(void){
	Chip_ADC_SetStartMode(LPC_ADC0,ADC_START_NOW,ADC_TRIGGERMODE_RISING);
}

void Clear_Start_ADC(void){
	Chip_ADC_SetStartMode(LPC_ADC0,ADC_NO_START,ADC_TRIGGERMODE_RISING);
}

uint8_t Conversion_End_ADC(uint8_t adc_channel){

	uint8_t status_adc;
	status_adc=Chip_ADC_ReadStatus(LPC_ADC0,adc_channel,ADC_DR_DONE_STAT);

	if(status_adc==0){
		return status_adc=1;
	}
	else{
		return status_adc=0;
	}
}

void Read_ADC(uint8_t adc_channel,uint16_t *Data_ADC){
	Chip_ADC_ReadValue(LPC_ADC0,adc_channel,Data_ADC);
}


void Set_ADC_Interrupt(uint8_t adc_channel){
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0,adc_channel,ENABLE);
}




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
