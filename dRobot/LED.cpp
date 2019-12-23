
#include "LED.h"

namespace dRobot {


/* PRIVATE */

/* Personal private functions */

void LED::writeLED(uint8_t in){
	if (in > 0){
		HAL_GPIO_WritePin(gpio, gpio_pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(gpio, gpio_pin, GPIO_PIN_RESET);
	}
}


} /* namespace dRobot */
