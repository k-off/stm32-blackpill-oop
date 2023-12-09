/*
 * ENUMS.hpp
 *
 *  Created on: Dec 9, 2023
 *      Author: pawel
 */

#ifndef INC_GPIOENUMS_HPP_
#define INC_GPIOENUMS_HPP_

 // replace with #include "stm32f4xx_hal.h" if not a generated project
#include <main.h>
#include <stdbool.h>
#include <stdint.h>

enum State { Lo=0, Hi };

enum class Status { Disable=-1, Get, Enable };

enum PortLetter {
#ifdef GPIOA
	A=0,
#endif
#ifdef GPIOB
	B,
#endif
#ifdef GPIOC
	C,
#endif
#ifdef GPIOD
	D,
#endif
#ifdef GPIOE
	E,
#endif
#ifdef GPIOF
	F,
#endif
#ifdef GPIOG
	G,
#endif
#ifdef GPIOH
	H
#endif
};

GPIO_TypeDef *AvailablePorts[] = {
#ifdef GPIOA
	GPIOA,
#endif
#ifdef GPIOB
	GPIOB,
#endif
#ifdef GPIOC
	GPIOC,
#endif
#ifdef GPIOD
	GPIOD,
#endif
#ifdef GPIOE
	GPIOE,
#endif
#ifdef GPIOF
	GPIOF,
#endif
#ifdef GPIOG
	GPIOG,
#endif
#ifdef GPIOH
	GPIOH,
#endif
};

/* Pin Mode */
enum class Mode {
	Input, /* Input */
	Output, /* Output */
	AF, /* Alternate Function */
	Analog /* Analog */
};

/* Pin Output Speed */
enum class Speed {
	Low, /* Low */
	Medium, /* Medium */
	Fast, /* Fast */
	High /* High > Fast */
};

/* Pin Output Type */
enum class OType {
	PushPull, /* Push-Pull */
	OpenDrain /* Open-Drain */
};

/* Pin Pull-Up/Pull-Down */
enum class PUPD {
	NoPUPD, /* No pull-up no pull-down */
	PullUp, /* Pull-up */
	PullDown /* Pull-down */
};

/*
 * Pin alternate functions, see controller
 * reference manual for each GPIO
 */
enum class Alt {
	F0,  /* System */
	F1,  /* TiM_1/TiM_2 */
	F2,  /* TiM_3..5 */
	F3,  /* TiM_8..11 */
	F4,  /* i2C_1..3 */
	F5,  /* SPi_1/SPi_2 */
	F6,  /* SPi_3 */
	F7,  /* USART_1..3 */
	F8,  /* USART_4..6 */
	F9,  /* CAN_1/CAN_2, TiM_12..14 */
	F10, /* OTG_FS/OTG_HS */
	F11, /* ETH */
	F12, /* FSMC, SDIO, OTG_HS */
	F13, /* DCMi */
	F14, /* - */
	F15  /* EVENTOUT */
};

#endif /* INC_ENUMS_HPP_ */
