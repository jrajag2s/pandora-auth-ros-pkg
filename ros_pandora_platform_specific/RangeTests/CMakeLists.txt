cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(dataFusionTestHoleExists dataFusion/dataFusionTestHoleExists.cpp)
#rosbuild_add_executable(dataFusionTestMlx dataFusion/dataFusionTestMlx.cpp)
#rosbuild_add_executable(dataFusionTestTpa dataFusion/dataFusionTestTpa.cpp)
#rosbuild_add_executable(dataFusionTestCo2 dataFusion/dataFusionTestCo2.cpp)
#rosbuild_add_executable(dataFusionTestNotThermal dataFusion/dataFusionTestNotThermal.cpp)
rosbuild_add_executable(rangeTest src/rangeTest.cpp)
#target_link_libraries(example ${PROJECT_NAME})
