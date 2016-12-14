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

/** \brief Driver Led (Baremetal)
 **
 **/


/*
 * Initials     Name
 * ---------------------------
 *    GP	    Germán Pressel Coretto
 */

/*==================[inclusions]=============================================*/
#include "chip.h"
#include "led.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

const Led led_individual = {{0,14},{1,11},{1,12}};
const Led_RGB led_RGB ={{5,0},{5,1},{5,2}};

/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*Description: Turn off all the leds*/
void TurnOff_Leds(void){
    Chip_GPIO_ClearValue(LPC_GPIO_PORT,led_RGB.red.Port,(1<<led_RGB.red.Pin)|(1<<led_RGB.green.Pin)|(1<<led_RGB.blue.Pin));
    Chip_GPIO_ClearValue(LPC_GPIO_PORT,led_individual.red.Port,(1<<led_individual.red.Pin));
    Chip_GPIO_ClearValue(LPC_GPIO_PORT,led_individual.green.Port,(1<<led_individual.green.Pin)|(1<<led_individual.yellow.Pin));
};

/*Description: Turn on all the leds*/
void TurnOn_Leds(void){
	Chip_GPIO_SetValue(LPC_GPIO_PORT,led_RGB.red.Port,(1<<led_RGB.red.Pin)|(1<<led_RGB.green.Pin)|(1<<led_RGB.blue.Pin));
	Chip_GPIO_SetValue(LPC_GPIO_PORT,led_individual.red.Port,(1<<led_individual.red.Pin));
	Chip_GPIO_SetValue(LPC_GPIO_PORT,led_individual.green.Port,(1<<led_individual.green.Pin)|(1<<led_individual.yellow.Pin));
};

/*Description: Initialization of the GPIO Ports and Pins that are related to all the Leds. Leds end up off.*/
void Initialization_Leds(void){
	Chip_GPIO_Init(LPC_GPIO_PORT);

	/*LED RGB :
	 * Pin Assignment, from 2.0 to GPIO 5.0(R), 2.1 to GPIO 5.1(G) and 2.2 to GPIO 5.2(B)
	 */
		Chip_SCU_PinMux(2,0,MD_PUP,FUNC4);
		Chip_SCU_PinMux(2,1,MD_PUP,FUNC4);
		Chip_SCU_PinMux(2,2,MD_PUP,FUNC4);
		/* Pin's Direction*/
		Chip_GPIO_SetDir(LPC_GPIO_PORT,led_RGB.red.Port,(1<<led_RGB.red.Pin)|(1<<led_RGB.green.Pin)|(1<<led_RGB.blue.Pin),DIR_OUT);

	/*Individual Leds:
	 * Pin Assignment, from 2.10 to GPIO 0.1(Red Led), 2.11 to GPIO 1.11(Yellow Led) and 2.12 to GPIO 1.12(Green Led)
	 */
		Chip_SCU_PinMux(2,10,MD_PUP,FUNC0);
		Chip_SCU_PinMux(2,11,MD_PUP,FUNC0);
		Chip_SCU_PinMux(2,12,MD_PUP,FUNC0);
		/*Pin's Direction*/
		Chip_GPIO_SetDir(LPC_GPIO_PORT,led_individual.red.Port,(1<<led_individual.red.Pin),DIR_OUT);
		Chip_GPIO_SetDir(LPC_GPIO_PORT,led_individual.green.Port,(1<<led_individual.green.Pin)|(1<<led_individual.yellow.Pin),DIR_OUT);

	/*Turn off all Leds*/
	TurnOff_Leds();

};

/*Description: Turn on an individual Led*/
void TurnOn_Led(uint8_t color){
	switch (color) {
		case RED:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_individual.red.Port,led_individual.red.Pin);
			break;
		case YELLOW:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_individual.yellow.Port,led_individual.yellow.Pin);
			break;
		case GREEN:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_individual.green.Port,led_individual.green.Pin);
		    break;
		default:
			break;
	}

};

/* Description: Turn off an individual Led*/
void TurnOff_Led(uint8_t color){
	switch (color) {
		case RED:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_individual.red.Port,led_individual.red.Pin);
			break;
		case YELLOW:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_individual.yellow.Port,led_individual.yellow.Pin);
			break;
		case GREEN:
			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_individual.green.Port,led_individual.green.Pin);
		    break;
		default:
			break;
	}
};

/*Description: Turn on the RGB Led*/
void TurnOn_Led_RGB(uint8_t color){
	switch (color) {
		case RED:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_RGB.red.Port,led_RGB.red.Pin);
			break;
		case BLUE:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_RGB.blue.Port,led_RGB.blue.Pin);
			break;
		case GREEN:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_RGB.green.Port,led_RGB.green.Pin);
		    break;
        case WHITE:
            Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_RGB.red.Port,led_RGB.red.Pin);
            Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_RGB.blue.Port,led_RGB.blue.Pin);
            Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,led_RGB.green.Port,led_RGB.green.Pin);
            break;
        default:
        	break;
	}

};

/*Description: Turn off the RGB Led*/
void TurnOff_Led_RGB(uint8_t color){
	switch (color) {
			case RED:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_RGB.red.Port,led_RGB.red.Pin);
				break;
			case BLUE:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_RGB.blue.Port,led_RGB.blue.Pin);
				break;
			case GREEN:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_RGB.green.Port,led_RGB.green.Pin);
			    break;
            case WHITE:
            	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_RGB.red.Port,led_RGB.red.Pin);
            	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_RGB.blue.Port,led_RGB.blue.Pin);
            	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,led_RGB.green.Port,led_RGB.green.Pin);
                break;
            default:
            	break;
		}
};

/* Description: Toggle an individual Led*/
void Toggle_Led(uint8_t color){
	switch (color){
			case RED:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_individual.red.Port,led_individual.red.Pin);
				break;
			case YELLOW:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_individual.yellow.Port,led_individual.yellow.Pin);
				break;
			case GREEN:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_individual.green.Port,led_individual.green.Pin);
				break;
			default:
				break;
	}
};

/*Description: Toggle the RGB Led*/
void Toggle_Led_RGB(uint8_t color){
	switch (color) {
			case RED:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_RGB.red.Port,led_RGB.red.Pin);
				break;
			case BLUE:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_RGB.blue.Port,led_RGB.blue.Pin);
				break;
			case GREEN:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_RGB.green.Port,led_RGB.green.Pin);
			    break;
            case WHITE:
                Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_RGB.red.Port,led_RGB.red.Pin);
                Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_RGB.blue.Port,led_RGB.blue.Pin);
                Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,led_RGB.green.Port,led_RGB.green.Pin);
                break;
            default:
            	break;
		}
};


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
