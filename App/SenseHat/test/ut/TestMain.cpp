// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include <Fw/Test/UnitTest.hpp>
#include "Tester.hpp"

TEST(Nominal, TestPort) {
    App::Tester tester;
    TEST_CASE(SenseHat.0,"Test scheduler in port");
    tester.testSchedIn();
}

TEST(Nominal, TestCommand) {
    App::Tester tester;
    TEST_CASE(SenseHat.1,"Test sending cmd to get tm data");
    tester.testCmdMS_GET_TM();

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
