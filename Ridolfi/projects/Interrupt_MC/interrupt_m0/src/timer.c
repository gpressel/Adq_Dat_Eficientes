/* Copyright 2016, XXXXXXXXX  
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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
/*#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)*/
#include "chip.h"
/*#elif (mk60fx512vlq15 == CPU)
#else
#endif*/
#include "timer.h"
#include "stdint.h"
/*#include "cmsis_43xx.h" No debería hacer esto*/

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*Initialization of the RIT Timer*/
void Initialization_RITTimer(void){
	Chip_RIT_Init(LPC_RITIMER);
};

/*Enable or Disable the RIT_Timer Interrupt*/
void Set_RIT_Interrupt(uint8_t Value){
	if(Value==ENABLE){
		NVIC_EnableIRQ(RITIMER_IRQn);
	}
	else{
		if(Value==DISABLE){
			NVIC_DisableIRQ(RITIMER_IRQn);
		}
	else{}}
};

/*Config RIT_Timer interval in msec*/

void Interval_RITTimer(uint32_t interval){
	Chip_RIT_SetTimerInterval(LPC_RITIMER,interval);
};

///*Config RIT_Timer interval in usec*/
//
//void Interval_RITTimer_uSec(uint32_t interval){
//
//	Chip_RIT_SetTimerIntervalus(LPC_RITIMER,interval);
//};

/*Clean the RIT_Timer interrupt flag*/
void Clear_RIT_IntFlag(void){
	Chip_RIT_ClearInt(LPC_RITIMER);
};





/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

