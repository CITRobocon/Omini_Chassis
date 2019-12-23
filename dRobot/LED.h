
#ifndef LED_H_
#define LED_H_

/*
 *   Name: LED
 *   About: A LED light
 *
 *   Upward output: None
 *   Upward input:  0: down, 1: light
 *
 *   Downward output: World
 *   Downward input:  None
 *                _______
 *      None --> |       | --> LED/empty
 *               |  LED  |
 *     World <-- |_______| <-- LED/uint8
 *
 */


#include <cstdint>
#include "common_includes.h"

#include "device.h"
#include "general_msgs/empty_msgs.h"
#include "general_odrs/numeric_odrs.h"


namespace dRobot {


/* Message structure */

// common_msgs/empty_msgs/empty_msg


/* Order structure */

// common_odrs/numeric_odrs/uint8_odr


/* device class */

class LED: public device<empty_msg, uint8_odr> {
	/* Pointers of child device */
	// None

	/* Override: Called back before share a message */
	void msgCallback(empty_msg msg){
	}

	/* Override: Called back after be shared an order */
	void odrCallback(uint8_odr odr){
		writeLED(odr.val);
	}

	/* Personal private variables */

	/* Personal private functions */
	void writeLED(uint8_t);
	GPIO_TypeDef *gpio;
	uint16_t gpio_pin;

public:
	/* Constructor */
	LED(GPIO_TypeDef *gpiot, uint16_t pin){
		gpio = gpiot;
		gpio_pin = pin;
	}
};


} /* namespace dRobot */

#endif /* LED_H_ */
