
#ifndef DEVICE_H_
#define DEVICE_H_

#include <cstdint>

#include "tf/tf.h"
#include "../stm_interface/inter.h"
#include "../stm_interface/ticker.h"

namespace dRobot {

template <typename msgT, typename odrT>
class device {
protected:
	/* Common private variables */
	tf *origin;
	tf pose;

	/* Message */
	msgT myMsg;

	/* Callback before share a message */
	virtual void msgCallback(msgT msg){
	}

	/* Callback after be shared an order */
	virtual void odrCallback(odrT odr){
	}

	/* Update myself using ticker */
	virtual void selfTickerUpdate(ticker_args targs){
	}

	/* Update myself using inter */
	virtual void selfInterUpdate(){
	}

	/* Initialize */
	virtual void initialize(){
	}

	/* Error handler */
	virtual void deviceErrorHandler(){
		while(1);
	}

public:
	device(){
		origin = nullptr;
	}

	// Operator
	template <class devT>
	devT* operator>>(devT **dev){
		*dev = this;
		(*dev)->origin = &pose;

		return this;
	}

	// Setup
	void setup(){
		initialize();
	}

	// Setup with ticker
	void setup(float period, int priority){
		ticker_assign(tickerCallback, static_cast<void*>(this), priority, period, 's');
		initialize();
	}

	// Setup with inter
	void setup(const char *name){
		inter_register(name, interCallback, static_cast<void*>(this));
		initialize();
	}

	// Share msg
	msgT shareMsg(){
		msgCallback(myMsg);
		return myMsg;
	}

	// Share odr
	void shareOdr(odrT odr){
		odrCallback(odr);
		return;
	}

	// Returns relative pose
	tf getRelativePose(){
		return pose;
	}

	// Returns pose from attached origin
	tf getPose(){
		if (origin == nullptr){
			return pose;
		}

		return pose * (*origin);
	}

	void fixOrigin(tf *sigma){
		origin = sigma;
	}

	// Set position
	void setPosition(float x, float y, float z){
		pose.translate(x, y, z);
	}

	// Set angle x-axis
	void setAngle_x(float theta){
		pose.rotate_x(theta);
	}

	// Set angle y-axis
	void setAngle_y(float theta){
		pose.rotate_y(theta);
	}

	// Set angle z-axis
	void setAngle_z(float theta){
		pose.rotate_z(theta);
	}

private:
	static void tickerCallback(ticker_args targs){
		static_cast<device*>(targs.argptr)->selfTickerUpdate(targs);
	}

	static void interCallback(inter_arg iarg){
		static_cast<device*>(iarg.argptr)->selfInterUpdate();
	}
};

} /* namespace dRobot */

#endif /* DEVICE_H_ */
