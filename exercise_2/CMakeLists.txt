cmake_minimum_required(VERSION 3.8)
project(exercise_2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_robot_interfaces REQUIRED) 

add_executable(led src/led.cpp)
ament_target_dependencies(led rclcpp my_robot_interfaces)

add_executable(battery src/battery.cpp)
ament_target_dependencies(battery rclcpp my_robot_interfaces)

install(TARGETS 
  led
  battery
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
