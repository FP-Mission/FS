####
# : App/TemperatureProbes/CMakeLists.txt
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# This file will setup the build for the TemperatureProbes component. This is done by defining the SOURCE_FILES variable and then
# registering the component as an F prime module. This allows autocoding and more!
####
set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/TemperatureProbesComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/TemperatureProbesComponentImpl.cpp"
)
register_fprime_module()