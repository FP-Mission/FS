####
# 'App' Deployment:
#
# This sets up the build for the 'Ref' Application, including the custom reference
# components. In addition, it imports FPrime.cmake, which includes the core F Prime
# components.
#
# This file has several sections.
#
# 1. Header Section: define basic properties of the build
# 2. F prime core: includes all F prime core components, and build-system properties
# 3. Local subdirectories: contains all deployment specific directory additions
####

##
# Section 1: Basic Project Setup
#
# This contains the basic project information. Specifically, a cmake version and
# project definition.
##
project(App C CXX)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

##
# Section 2: F prime Core
#
# This includes all of the F prime core components, and imports the make-system. F prime core
# components will be placed in the F-Prime binary subdirectory to keep them from
# colliding with deployment specific items.
##
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")
##
# Section 3: Components and Topology
#
# This section includes deployment specific directories. This allows use of non-
# core components in the topology, which is also added here.
##

# Add ports subdirectories
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/FlexTrak/Position/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/FlexTrak/BatteryLevelPort/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/FlexTrak/TemperaturePort/")

# Add component subdirectories
add_fprime_subdirectory("${FPRIME_FRAMEWORK_PATH}/Ref/PingReceiver/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/FlexTrak/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Eps/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Gps/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/PiCamera/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Predictor/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/RockBlock/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/TemperatureProbes/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/SenseHat/SenseHatPort/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/FlexTrak/Position/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/PiCamera/PiCameraPort/")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/SenseHat/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Thermometer/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/MotionTracking/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/MotionTracking/MotionTrackingType/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Barometer/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/PiCamera/")

# Add topology subdirectory
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

