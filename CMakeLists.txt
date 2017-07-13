cmake_minimum_required(VERSION 2.8.3)
project(schunk_svh_gazebo)

find_package(catkin REQUIRED kdl_parser std_msgs roscpp)

catkin_package(
  # INCLUDE_DIRS include
  # LIBRARIES schunk_svh_gazebo
  # CATKIN_DEPENDS other_catkin_pkg
  # DEPENDS system_lib
)



# Inserted for Kinetic version
include_directories(${catkin_INCLUDE_DIRS})

## Declare a C++ executable
add_executable(schunk_svh_gazebo_node src/command_publisher_alone.cpp)
add_executable(command_publisher_node src/command_publisher_v2.cpp)
add_executable(ik_controllers src/joint_controller.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(schunk_svh_gazebo_node
  ${catkin_LIBRARIES}
)

target_link_libraries(command_publisher_node
  ${catkin_LIBRARIES}
)

target_link_libraries(ik_controllers
  ${catkin_LIBRARIES}
)
