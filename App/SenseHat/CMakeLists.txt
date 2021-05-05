set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/SenseHatComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/SenseHatComponentImpl.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/SHTC3/SHTC3.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/LPS22/LPS22.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ICM/ICM.cpp"
)

register_fprime_module()

find_library(wiringPi_LIB wiringPi)
find_library(LibRt rt)
find_library(Crypt crypt)
target_link_libraries(App_SenseHat ${wiringPi_LIB} ${LibRt} ${Crypt})

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMain.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterBase.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/GTestBase.cpp"
)
register_fprime_ut()
