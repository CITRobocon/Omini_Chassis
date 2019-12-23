
#ifndef LidarPositioning_H_
#define LidarPositioning_H_

/*
 *   Name: LidarPositioning
 *   About: An interface to positioning system using lidar with PC
 *
 *   Upward output: 2D pose from attached origin
 *   Upward input:	2D pose as attached origin
 *
 *   Downward output: None
 *   Downward input:  Dead reckoning system as initial value
 *                        ____________________
 *     DeadReckoning --> |                    | --> LidarPositioning/pos2d
 *                       |  LidarPositioning  |
 *              None <-- |____________________| <-- LidarPositioning/command
 */


#include <cstdint>
#include "common_includes.h"
#include "../connection/scom.h"

#include "device.h"
#include "general_msgs/geometry_msgs.h"
#include "general_odrs/empty_odrs.h"


namespace dRobot {


/* Message structure */

typedef struct{
	struct{
		float x;
		float y;
		float theta;
	} pos2d;
} LidarPositioning_msg;


/* Order structure */

typedef struct{
	enum{
	} command;
} LidarPositioning_odr;


/* device class */

class LidarPositioning: public device<pose2d_msg, empty_odr> {
	/* Pointers of child device */
	device<pose2d_msg, empty_odr> *positioning;

	/* Override: Called back after be shared an order */
	void odrCallback(empty_odr odr){
	}

	/* Override: Update myself using inter */
	void selfInterUpdate(){
		char c = receiveCommand();

		switch(c){
		case 's':
			receiveData();
			return;

		case 'r':
			sendData();
			return;
		}

		setupNextCommunication();
	}

	void initialize(){
		connection = scom_connect(huart_ptr);
	}

	/* Personal private variables */
	scom_connection connection;
	UART_HandleTypeDef *huart_ptr;

	/* Personal private functions */
	char receiveCommand();
	void receiveData();
	void sendData();
	void setupNextCommunication();

public:
	/* Constructor */
	LidarPositioning(UART_HandleTypeDef *ptr){
		huart_ptr = ptr;
	}
};


} /* namespace dRobot */

#endif /* LidarPositioning_H_ */
