#include "controller_sub.hpp"


Controller::Controller(){

  // Get Min and Max joints limits
	node.param("joint_lower_limit", joint_lower_limit, -1.570796327);
	node.param("joint_upper_limit", joint_upper_limit, 1.570796327);

	controller = new PCA9685(I2C_BUS, I2C_ADDRESS);
 	controller->setPWMFreq(60);
	d009a_limit_coef  = (D009A_SERVO_MAX_PUL - D009A_SERVO_MIN_PUL) / (joint_upper_limit - joint_lower_limit);
	d150a_limit_coef  = (D150A_SERVO_MAX_PUL - D150A_SERVO_MIN_PUL) / (joint_upper_limit - joint_lower_limit);
	sub_servo = node.subscribe("pca9685/servostate_to_controller", 100, &Controller::chatterServoState, this);
	ROS_INFO("Servo controller is ready...");
        sub_pwm = node.subscribe("pca9685/pwmstate_to_controller", 100, &Controller::chatterPwmState, this);
        ROS_INFO("PWM controller is ready...");
}

void Controller::chatterServoState (const pca9685_msgs::ServoStateConstPtr &servo_state){
	int target_value;
        ROS_INFO("CMD Servo %d",  servo_state->port_num);
	if((servo_state->servo_type ==  servo_state->STOP) && (servo_state->port_num == 0)){
		for(int i = 1; i < 13; i++){
	                controller->setPWM(i, 0,  0);
		}
                ROS_INFO("All servos disabled");
	} else {	
		if(servo_state->servo_type ==  servo_state->D150A) {
	        	target_value = (D150A_SERVO_MIN_PUL + D150A_SERVO_MAX_PUL)/2 + (int)(servo_state->servo_rot * d150a_limit_coef);
                	controller->setPWM(servo_state->port_num, 0, (int) target_value);
		} else if (servo_state->servo_type ==   servo_state->D009A){
			target_value = (D009A_SERVO_MIN_PUL + D009A_SERVO_MAX_PUL)/2 + (int)(servo_state->servo_rot * d009a_limit_coef);
                	controller->setPWM(servo_state->port_num, 0, (int) target_value);
		} else {
                	target_value =  0;
                	controller->setPWM(servo_state->port_num, 0,  (int) target_value);
		}
       		ROS_INFO("Servo %d: [%d]",  servo_state->port_num, (int) target_value);
	}
}

void Controller::chatterPwmState (const pca9685_msgs::PwmStateConstPtr &pwm_state){

        controller->setPWM(pwm_state->port_num, pwm_state->on_value, pwm_state->off_value );

        ROS_INFO("PWM %d: [%d, %d]",  pwm_state->port_num, pwm_state->on_value, pwm_state->off_value);
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "controller_sub");
	Controller c;
    ros::spin();
}


