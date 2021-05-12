####
# : App/PiCamera/CMakeLists.txt
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# This file will setup the build for the PiCamera component. This is done by defining the SOURCE_FILES variable and then
# registering the component as an F prime module. This allows autocoding and more!
####

set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/PiCameraComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/PiCameraComponentImpl.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/toojpeg.cpp"
)
register_fprime_module()
include_directories(../lib/include)
include_directories(../lib/include/libpng16)

find_library(RASPICAM raspicam /usr/local/lib)
find_library(PNG png ..lib/lib)

target_link_libraries(App_PiCamera ${RASPICAM} ${PNG})
