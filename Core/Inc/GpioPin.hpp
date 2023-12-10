/*
 * PIN.hpp
 *
 *  Created on: Dec 9, 2023
 *      Author: pawel
 */

#ifndef INC_GPIOPIN_HPP_
#define INC_GPIOPIN_HPP_

 // replace with #include "stm32f4xx_hal.h" if not a generated project
#include <main.h>
#include <stdbool.h>
#include <stdint.h>

#include "GpioEnums.hpp"

/**
 * @brief Most used functionality of a GPIO pin
 */
class PIN {
public:
	/*
	 * @brief	Initialize pin
	 * @param	uint8_t _idx index of the pin
	 * @param	GPIO_TypeDef *_port pointer to the port
	 * @retval	const PIN&
	 */
	const PIN& Init(uint8_t _idx, GPIO_TypeDef *_port) {
		idx = _idx;
		port = _port;
		return *this;
	}

	/*
	 * @brief Read value on the pin
	 * @retval Hi or Lo
	 */
	State Read() const {
		return (State)(port->IDR & (1 << idx) >> idx);
	}

	/*
	 * @brief Read value on the pin
	 * @param	int16_t &val value to store data in
	 * @retval	const PIN&
	 */
	const PIN& Read(State &val) const {
		val = Read();
		return *this;
	}

	/*
	 * @brief Read value on the pin
	 * @param	bool value to write into pin
	 * @retval	const PIN&
	 */
	const PIN& Write(bool val) const {
		port->BSRR = (1 << (idx + 16 * (val == GPIO_PIN_SET)));
		return *this;
	}

	/*
	 * @brief Set Pin mode and, optionally, alternate function
	 * @param	Mode mode see enum class
	 * @param	Alt af alternate function, see enum class and docs
	 * @retval	const PIN&
	 */
	const PIN& Set(Mode mode, Alt af=Alt::F0) const {
		port->MODER &= ~(3 << (idx << 1));
		port->MODER |= ((uint32_t)mode << (idx << 1));
		if (mode == Mode::AF) {
			port->AFR[idx > 7] &= ~(15 << (idx << 4));
			port->AFR[idx > 7] |= ((uint32_t)af << (idx << 4));
		}
		return *this;
	}

	/*
	 * @brief Set Pin mode and, optionally, alternate function
	 * @param	Speed speed, see enum class
	 * @retval	const PIN&
	 */
	const PIN& Set(Speed speed) const {
		port->OSPEEDR &= ~(3 << (idx << 1));
		port->OSPEEDR |= ((uint32_t)speed << (idx << 1));
		return *this;
	}

	/*
	 * @brief Set Pin mode and, optionally, alternate function
	 * @param	OType ot, see enum class
	 * @retval	const PIN&
	 */
	const PIN& Set(OType ot) const {
		port->OTYPER |= ((uint16_t)ot << idx);
		return *this;
	}

	/*
	 * @brief Set Pin pull-up or pull-down or none
	 * @param	PUPD p, see enum class
	 * @retval	const PIN&
	 */
	const PIN& Set(PUPD p) const {
		port->PUPDR &= ~(3 << (idx << 1));
		port->PUPDR |= ((uint32_t)p << (idx << 1));
		return *this;
	}

	const PIN& Get(Mode& m) const {
		m = GetMode();
		return *this;
	}

	Mode  GetMode() const {
		return (Mode)((port->MODER & (3 << (idx << 1))) >> (idx << 1));
	}

	const PIN& Get(Alt& a) const {
		a = GetAlt();
		return *this;
	}

	Alt GetAlt() const {
		if (GetMode() == Mode::AF)
			return (Alt)((port->AFR[idx > 7] & (15 << (idx << 4))) >> (idx << 4));
		return (Alt)0;
	}

	const PIN& Get(Speed& s) const {
		s = GetSpeed();
		return *this;
	}

	Speed GetSpeed() const {
		return (Speed)((port->OSPEEDR & (3 << (idx << 1))) >> (idx << 1));
	}

	const PIN& Get(OType& o) const {
		o = GetOType();
		return *this;
	}

	OType GetOType() const {
		return (OType)((port->OTYPER & (1 << idx)) >> idx);
	}

	const PIN& Get(PUPD& p) const {
		p = GetPUPD();
		return *this;
	}

	PUPD GetPUPD() const {
		return (PUPD)((port->PUPDR & (3 << (idx << 1))) >> (idx << 1));
	}

private:
	uint8_t idx = 0;			// PIN index
	GPIO_TypeDef *port = NULL;	// port of the PIN
};




#endif /* INC_GPIOPIN_HPP_ */
