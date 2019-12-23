
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

/*
 *   Name: Keyboard
 *   About: Keyboard interface connecting to debuging PC
 *
 *   Upward output: None
 *   Upward input:	None
 *
 *   Downward output: Float value volumed keyboard input
 *   Downward input:  None
 *
 *                ____________
 *     empty --> |            | --> Keyboard/empty
 *               |  Keyboard  |
 *     float <-- |____________| <-- Keyboard/empty
 *
 */


#include <cstdint>
#include "common_includes.h"

#include "device.h"
#include "general_msgs/empty_msgs.h"
#include "general_odrs/empty_odrs.h"
#include "general_odrs/numeric_odrs.h"
#include "general_odrs/geometry_odrs.h"


namespace dRobot {


/* Message structure */
// common_msgs/empty_msgs/empty_msg


/* Order structure */
// common_odrs/numeric_odrs/float_odr


/* Device class */

class Keyboard: public device<empty_msg, empty_odr> {
public:
	/* Pointers of child device */
	device<empty_msg, float_odr> *volume_dev[10];
	device<empty_msg, uint8_odr> *toggle_dev[10];
	device<empty_msg, twist_odr> *twist_dev;

protected:
	/* Override: Update myself */
	void selfInterUpdate(){
		interpretInput(cbuf[0]);

		setupNextInput();
	}

	/* Override: Initialize */
	void initialize(){
		for (int i = 0; i < 10; i++){
			volume[i] = 0.0f;
			toggle[i] = 0;
		}

		twist[0] = 0.0f;
		twist[1] = 0.0f;
		twist[2] = 0.0f;

		setupNextInput();
	}

	/* Personal private variables */
	UART_HandleTypeDef *huart_pc;
	float volume[10];
	uint8_t toggle[10];
	float twist[3];

	uint8_t mode;
	uint8_t ch;
	uint8_t cbuf[1];

	/* Personal private functions */
	void setupNextInput();
	void interpretInput(uint8_t);

public:
	/* Constructor */
	Keyboard(UART_HandleTypeDef *huart){
		for (int i = 0; i < 10; i++){
			toggle_dev[i] = nullptr;
			volume_dev[i] = nullptr;
		}

		twist_dev = nullptr;

		huart_pc = huart;
		ch = 1;
		mode = 0;
	}
};


} /* namespace dRobot */

#endif /* KEYBOARD_H_ */
