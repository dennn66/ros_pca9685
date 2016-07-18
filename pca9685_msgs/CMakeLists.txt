cmake_minimum_required(VERSION 2.8.3)
project(pca9685_msgs)

find_package(catkin REQUIRED genmsg std_msgs)

add_message_files(FILES
		  ServoState.msg
		  PwmState.msg
                 )

generate_messages(DEPENDENCIES std_msgs)

catkin_package(DEPENDS std_msgs)

