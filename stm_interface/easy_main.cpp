#include "easy_main.h"

#include "common_includes.h"

#include "../dRobot/general_msgs/geometry_msgs.h"
#include "../dRobot/general_odrs/numeric_odrs.h"

#include "../dRobot/Keyboard.h"
#include "../dRobot/Kinematics.h"
#include "../dRobot/LED.h"
#include "../dRobot/Odometer.h"
#include "../dRobot/DeadReckoning.h"
#include "../dRobot/PIDController.h"
#include "../dRobot/PosePoint.h"
#include "../dRobot/MotorDriver.h"
#include "../dRObot/WheelObserver.h"

/* External global variables */

// Timer for Ticker interrupt
extern TIM_HandleTypeDef htim6;

// TImer for PWM generation
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;

// Timer counters for encoder
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

// UART connection for PC serial
extern UART_HandleTypeDef huart3;


/* All devices */

// Input device
dRobot::Keyboard keyboard(&huart3);

// Point device
dRobot::PosePoint wheel_point1;
dRobot::PosePoint wheel_point2;
dRobot::PosePoint wheel_point3;
dRobot::PosePoint wheel_point4;

// Sensor device
dRobot::Odometer odometer_r(TIM2, 4800, 0.030);
dRobot::Odometer odometer_f(TIM3, 4800, 0.030);
dRobot::Odometer odometer_l(TIM4, 4800, 0.030);

// System device
dRobot::Kinematics kinematics;
dRobot::DeadReckoning dead_reckoning;
dRobot::PIDController pid_controller1(1.0, 0.001, 0.00001);
dRobot::PIDController pid_controller2(1.0, 0.001, 0.00001);
dRobot::PIDController pid_controller3(1.0, 0.001, 0.00001);
dRobot::PIDController pid_controller4(1.0, 0.001, 0.00001);
dRobot::WheelObserver wheel_observer;

// Output device
dRobot::LED led(GPIOB,GPIO_PIN_14);
dRobot::MotorDriver motor_driver1(&(TIM1->CCR1), &(TIM1->CCR2), 0, 1000, 0.2);
dRobot::MotorDriver motor_driver2(&(TIM8->CCR1), &(TIM8->CCR2), 0, 1000, 0.2);
dRobot::MotorDriver motor_driver3(&(TIM8->CCR3), &(TIM8->CCR4), 0, 1000, 0.2);
dRobot::MotorDriver motor_driver4(&(TIM1->CCR3), &(TIM1->CCR4), 0, 1000, 0.2);


/* Setup */

void easy_setup(){
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);

	ticker_init(&htim6, 16, 'm');

	// setup wheel_point
	wheel_point1.setPosition(0.29915, 0.29915, 0.0);
	wheel_point1.setAngle_z(3.0*M_PI/4.0);

	wheel_point2.setPosition(-0.29915, 0.29915, 0.0);
	wheel_point2.setAngle_z(-3.0*M_PI/4.0);

	wheel_point3.setPosition(-0.29915, -0.29915, 0.0);
	wheel_point3.setAngle_z(-M_PI/4.0);

	wheel_point4.setPosition(0.29915, -0.29915, 0.0);
	wheel_point4.setAngle_z(M_PI/4.0);

	// setup odometer_r
	odometer_r.setPosition(0.0, -0.28837, 0.0);
	odometer_r.setAngle_z(M_PI);
	odometer_r.setup();

	// setup odometer_l
	odometer_f.setPosition(0.28837, 0.0, 0.0);
	odometer_f.setAngle_z(-M_PI/2.0);
	odometer_f.setup();

	// setup odometer_r
	odometer_l.setPosition(0.0, 0.28837, 0.0);
	odometer_l.setAngle_z(0.0);
	odometer_l.setup();

	// setup kinematics
	odometer_r >> &kinematics.wheel[0];
	odometer_f >> &kinematics.wheel[1];
	odometer_l >> &kinematics.wheel[2];
	kinematics.setup(0.020, 1);

	// setup dead_reckoning
	kinematics >> &dead_reckoning.kinematics;
	dead_reckoning.setup(0.020, 2);

	// setup pid_controller
	motor_driver1 >> &pid_controller1.output;
	pid_controller1.setup();

	motor_driver2 >> &pid_controller2.output;
	pid_controller2.setup();

	motor_driver3 >> &pid_controller3.output;
	pid_controller3.setup();

	motor_driver4 >> &pid_controller4.output;
	pid_controller4.setup();

	// setup wheel_observer
	kinematics >> &wheel_observer.obs;
	pid_controller1 >> &wheel_observer.err[0];
	pid_controller2 >> &wheel_observer.err[1];
	pid_controller3 >> &wheel_observer.err[2];
	pid_controller4 >> &wheel_observer.err[3];
	wheel_point1 >> &wheel_observer.wheel[0];
	wheel_point2 >> &wheel_observer.wheel[1];
	wheel_point3 >> &wheel_observer.wheel[2];
	wheel_point4 >> &wheel_observer.wheel[3];
	wheel_observer.setup(0.020, 2);

	// setup keyboard
	led >> &keyboard.toggle_dev[1];
	wheel_observer >> &keyboard.twist_dev;
	keyboard.setup("KeyI");


	ticker_schedule();
	ticker_start();
}


void easy_loop(){

}

