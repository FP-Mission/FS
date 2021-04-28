set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/MotionTrackingComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/MotionTrackingComponentImpl.cpp"
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMain.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterBase.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/GTestBase.cpp"
)
register_fprime_ut()