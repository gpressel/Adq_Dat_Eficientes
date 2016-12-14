/* Copyright 2016
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

#ifndef LED_H
#define LED_H

/** \brief Led Driver Header (Baremetal)
 **
 **/


/*
 * Initials     Name
 * ---------------------------
 *    GP	    Germán Pressel Coretto
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"
#include "chip.h"
#include "gpio.h"

/*==================[macros]=================================================*/

#define DIR_IN      0
#define DIR_OUT     1
#define RED 		1
#define GREEN 		2
#define YELLOW		3
#define BLUE 		4
#define WHITE		5
/*==================[typedef]================================================*/

typedef struct{
    GPIO red;
    GPIO green;
    GPIO blue;
}Led_RGB;

typedef struct{
	GPIO red;
	GPIO yellow;
	GPIO green;
}Led;

/*==================[external data declaration]==============================*/
/*
 */

/*Description: Turn off all the leds*/
void TurnOff_Leds(void);

/*Description: Turn on all the leds*/
void TurnOn_Leds(void);

/*Description: Initialization of the GPIO Ports and Pins that are related to all the Leds. Leds end up off.*/
void Initialization_Leds(void);

/*Description: Turn on an individual Led*/
void TurnOn_Led(uint8_t color);

/* Description: Turn off an individual Led*/
void TurnOff_Led(uint8_t color);

/*Description: Turn on the RGB Led*/
void TurnOn_Led_RGB(uint8_t color);

/*Description: Turn off the RGB Led*/
void TurnOff_Led_RGB(uint8_t color);

/* Description: Toggle an individual Led*/
void Toggle_Led(uint8_t color);

/*Description: Toggle the RGB Led*/
void Toggle_Led_RGB(uint8_t color);


/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef LED_H */
