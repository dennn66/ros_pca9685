cmake_minimum_required(VERSION 2.8.3)
project(ros_pca9685)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  pca9685_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_pca9685
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
   src/lib/PCA9685/src/ src/lib/I2C/src/ ${catkin_INCLUDE_DIRS}
)

add_library(I2C src/lib/I2C/src/I2C.cpp)
target_link_libraries(I2C ${catkin_LIBRARIES})

add_library(PCA9685 src/lib/PCA9685/src/PCA9685.cpp)
target_link_libraries(I2C PCA9685 ${catkin_LIBRARIES})

add_executable(controller_sub src/controller_sub.cpp)
target_link_libraries(controller_sub I2C PCA9685 ${catkin_LIBRARIES})


