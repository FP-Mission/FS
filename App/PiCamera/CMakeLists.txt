####
# : App/PiCamera/CMakeLists.txt
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# This file will setup the build for the PiCamera component. This is done by defining the SOURCE_FILES variable and then
# registering the component as an F prime module. This allows autocoding and more!
####

#add_definitions(-std=c++0x -L/home/pi/wiringPi/wiringPi -lwiringPi )

set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/PiCameraComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/PiCameraComponentImpl.cpp"
)
register_fprime_module()

find_library(wiringPi_LIB wiringPi)
find_library(LibRt rt)
find_library(Crypt crypt)
target_link_libraries(App_PiCamera ${wiringPi_LIB} ${LibRt} ${Crypt})
