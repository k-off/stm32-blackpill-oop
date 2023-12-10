/*
 * GPIO.hpp
 *
 *  Created on: Dec 5, 2023
 *      Author: pawel
 */

#ifndef INC_GPIO_HPP_
#define INC_GPIO_HPP_

 // replace with #include "stm32f4xx_hal.h" if not a generated project
#include <main.h>
#include <stdbool.h>
#include <stdint.h>

#include "GpioEnums.hpp"
#include "GpioPin.hpp"

/**
 * @brief GPIO class allows to enable and disable port clock,
 * 			to lock current pin configuration and
 * 			to get access to individual pins
 */
template <PortLetter pl>
class GPIO {
public:
	GPIO(): port(AvailablePorts[(uint8_t)pl]), pins() {
		for (uint32_t idx = 0; idx < 16; ++idx) {
			pins[idx].Init(idx, port);
		}
	}

	~GPIO() { }

	/**
	 * @brief Starts port clock and sets all pins to default states
	 */
	void Init() {
		if (!GPIO<pl>::Set(Status::Get)) {
			GPIO<pl>::Set(Status::Enable); // enable gpio clock
			for (uint32_t idx = 0; idx < 16; ++idx) {
				if (pl == A && (idx == 13 || idx == 14)) continue; // skip header SCK pin (GPIOA[14])
				pins[idx].Set(Mode::Output)
						.Set(Speed::Low)
						.Set(OType::PushPull)
						.Set(PUPD::NoPUPD)
						.Write(Lo);
			}
		}
	}

	// get pin reference for further manipulation
	const PIN& operator[](uint8_t idx) const {
		return pins[idx & 0xF];
	}

	/**
	 * @brief Locks pin configuration till next hardware reset
	 * @param pins bitset of the pins that are to be locked ie
	 * 			b0101010101010101 to lock pins 0, 2, .., 14
	 */
	const GPIO& ConfLock(uint16_t pins) const {
	    port->LCKR = (1 << 16) | pins;
	    port->LCKR = pins;
	    port->LCKR = (1 << 16) | pins;
	    (void)port->LCKR;

	    return *this;
	}

	/**
	 * @brief Enables or disables port clock and updates flag
	 * 			in case Status::Get returns current flag status
	 * 	@param Status Enable or Disable (or Get to only retrieve curr status)
	 * 	@return bool Enabled or Disabled
	 */
	static bool Set(Status s) {
		static uint8_t isInitialized = 0;
		if (s == Status::Disable) {
			RCC->AHB1ENR &= ~(1 << (uint8_t)pl);	// disable gpio clock
			isInitialized &= ~(1 << pl);			// unset current gpio flag
		}
		if (s == Status::Enable) {
			RCC->AHB1ENR |= (1 << (uint8_t)pl);	// enable gpio clock
			isInitialized |= (1 << pl);			// set current gpio flag
		}
		return (isInitialized & (1 << pl));
	}
private:
	GPIO_TypeDef *port;
	PIN pins[16] = {};
};

#endif /* INC_GPIO_HPP_ */
