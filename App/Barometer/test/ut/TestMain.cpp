	// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------
#include <Fw/Test/UnitTest.hpp>
#include "Tester.hpp"

TEST(Nominal, TestPort) {
    App::Tester tester;
    TEST_CASE(Barometer.0,"Test Data in port");
    tester.testDataIn();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}