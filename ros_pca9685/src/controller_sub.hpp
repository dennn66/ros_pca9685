
#ifndef CONTROLLER_SUB_HPP_
#define CONTROLLER_SUB_HPP_

#define I2C_BUS 1
#define I2C_ADDRESS 0x40
#define SERVO_MIN_PULSE 150
#define SERVO_MAX_PULSE 600
#define SERVO_PULSE_RANGE 4096

#include <ros/ros.h>
#include <pca9685_msgs/ServoState.h>
#include <pca9685_msgs/PwmState.h>

#include "PCA9685.h"

class Controller {
	public:
		Controller();

	private:

		ros::NodeHandle node;
		PCA9685 *controller;

		double joint_lower_limit, joint_upper_limit, limit_coef;
		ros::Subscriber sub_servo;
                ros::Subscriber sub_pwm;

		void chatterServoState (const pca9685_msgs::ServoStateConstPtr &servo_state);
		void chatterPwmState (const pca9685_msgs::PwmStateConstPtr &pwm_state);

};

#endif /* CONTROLLER_SUB_HPP_ */
