cmake_minimum_required(VERSION 2.8.3)
project(rosbag_direct_write_examples)

find_package(catkin REQUIRED COMPONENTS rosbag_direct_write sensor_msgs roscpp)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(bagger src/bagger.cpp)
target_link_libraries(bagger ${catkin_LIBRARIES})
set_target_properties(bagger PROPERTIES COMPILE_FLAGS "-std=c++11")

add_executable(direct_bagger src/direct_bagger.cpp)
target_link_libraries(direct_bagger ${catkin_LIBRARIES})
set_target_properties(direct_bagger PROPERTIES COMPILE_FLAGS "-std=c++11")

add_executable(reader src/reader.cpp)
target_link_libraries(reader ${catkin_LIBRARIES})
set_target_properties(direct_bagger PROPERTIES COMPILE_FLAGS "-std=c++11")

catkin_package()

## Install executables and/or libraries
install(TARGETS bagger direct_bagger reader
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
