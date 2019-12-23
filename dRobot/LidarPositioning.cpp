
#include "LidarPositioning.h"

namespace dRobot {


/* PRIVATE */

/* Personal private functions */

char LidarPositioning::receiveCommand(){
	scom_status status;

	static struct{
		union{
			uint8_t data[1];
			char c;
		};
	} c;

	static scom_databuf c_buf = {c.data, 1};

	if (scom_is_valid_connection(connection)){
		if (scom_sync_status(connection) == SCOM_SUCCESS){
			status = scom_receive(connection, c_buf, NULL);
		}
	}

	if (status == SCOM_ERROR)
		deviceErrorHandler();

	return c.c;
}

void LidarPositioning::receiveData(){
	scom_status status;

	static struct{
		union{
			uint8_t data[12];
			struct{
				float x;
				float y;
				float theta;
			};
		};
	} pos2d;

	static scom_databuf data_buf = {pos2d.data, 12};

	if (scom_is_valid_connection(connection)){
		if (scom_sync_status(connection) == SCOM_SUCCESS){
			status = scom_receive(connection, data_buf, NULL);
		}
	}

	if (status == SCOM_SUCCESS){
		myMsg.x = pos2d.x;
		myMsg.y = pos2d.y;
		myMsg.theta = pos2d.theta;
	}
}

void LidarPositioning::sendData(){
	scom_status status;

	static struct{
		union{
			uint8_t data[12];
			struct{
				float x;
				float y;
				float theta;
			};
		};
	} pose2d_payload;

	pose2d_msg msg = positioning->shareMsg();

	pose2d_payload.x = msg.x;
	pose2d_payload.y = msg.y;
	pose2d_payload.theta = msg.theta;

	scom_databuf data_buf = {pose2d_payload.data, 12};

	status = scom_transmit(connection, data_buf);

	if (status == SCOM_ERROR)
		deviceErrorHandler();
}

void LidarPositioning::setupNextCommunication(){
	scom_sync_start_it(connection);
}


} /* namespace dRobot */
