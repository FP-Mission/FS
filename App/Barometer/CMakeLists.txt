set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/BarometerComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/BarometerComponentImpl.cpp"
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMain.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterBase.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/GTestBase.cpp"
)
register_fprime_ut()

