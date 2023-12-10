# stm32-blackpill-oop
This might at some point become a complete oop library for STM32F4 blackpill

For a STM32CubeIDE project see `develop` branch

### GPIO
Added GPIO class that allows to start and stop port's clock, to access it's pins using array subsckript operator, and to lock current pin setting

### PIN
Added PIN class that allows to set it's mode, alternate function, speed, output type, pull-up/pull-down

### helper enums
Try to eliminate unnecessary asserts and make code more readable

## Usage

```
#include "stm32f4xx_hal.h"
#include "GPIO.hpp"

int main() {
  SystemClock_Config();
  HAL_Init();

  Speed s{};
  OType o{};
  Mode m{};
  PUPD p{};
  Alt al{};
  State val{};
  
  GPIO<C> c;
  c.Init();
  c[13].Set(Speed::High).Set(OType::OpenDrain).Set(Mode::Output).Set(PUPD::NoPUPD);
  c[13].Get(s).Get(o).Get(m).Get(p).Get(al);
  c[13].Write(Hi).Read(val);
  
  GPIO<A> a;
  a.Init();
  a[0].Set(Mode::Input).Set(OType::OpenDrain).Set(Speed::High).Set(PUPD::PullUp);
  
  while (1) { c[13].Write(a[0].Read()); } // blink on button press

  return 0;
}
```
