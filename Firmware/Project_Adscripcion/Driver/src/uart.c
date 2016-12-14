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

/** \brief Driver UART (Baremetal)
 **
 **/


/*
 * Initials     Name
 * ---------------------------
 *    GP	    Germán Pressel Coretto
 */

/*==================[inclusions]=============================================*/
#include "chip.h"
#include "uart.h"
#include "gpio.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/

GPIO Tx_UART2={7,1};
GPIO Rx_UART2={7,2};

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void Initialization_UART2(void){
	Chip_UART_Init(LPC_USART2);
	Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
	Chip_SCU_PinMux(Tx_UART2.Port,Tx_UART2.Pin, MD_PDN, FUNC6);              /* P7_1: UART2_TXD */
	Chip_SCU_PinMux(Rx_UART2.Port,Rx_UART2.Pin, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2: UART2_RXD */
};

void Set_Baud_UART2(uint32_t baud){
	Chip_UART_SetBaud(LPC_USART2,baud);
}

void Tx_Enable_UART2(void){
	Chip_UART_TXEnable(LPC_USART2);
}

uint8_t Read_Data_UART2(void){
	uint8_t dato;
	Chip_UART_Read(LPC_USART2,&dato,1);
	return dato;
}

void Send_Data_UART2(uint8_t *dato, uint8_t length){
	uint8_t* address;
	address=dato;
	uint8_t largo=length;
	while(largo!=0){
		if(Chip_UART_CheckBusy(LPC_USART2)==RESET){
		Chip_UART_Send(LPC_USART2,address,1);
		largo--;
		address++;}
		else{}
	}
}

void Send_Char_UART2(uint16_t* dato, uint16_t length){
	uint8_t count=0;
	uint16_t *pointer;

	while(count!=length){
	char Caracter[6];
	pointer=dato+count;
	uint8_t Numero=0,i=0,k=1;
	uint16_t Resto=*pointer;
	uint16_t Divisor=10000;
	for(k=1;k<5;k++)
	{		Numero=Resto/Divisor;
			Resto=Resto-Numero*Divisor;
			Divisor/=10;
			Caracter[i]=48+Numero;
			i++;
	}
	Caracter[i]=48+Resto;
	i++;
	Caracter[i]=' ';
	Chip_UART_SendBlocking(LPC_USART2,&Caracter,6);
	count++;
	}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
