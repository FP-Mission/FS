// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include <Fw/Test/UnitTest.hpp>

TEST(Nominal, TestCreated) {
    App::Tester tester;
    TEST_CASE(PiCamera.0,"Test created directories");
    tester.testCreatedDirectories();
    TEST_CASE(Picamera.1,"Test created file");
    tester.testFile();
}

TEST(Nominal, TestPort) {
    App::Tester tester;
    TEST_CASE(PiCamera.2,"Test BarometerPort");
    tester.testBarometerPort();
    TEST_CASE(PiCamera.3,"Test PositionPort");
    tester.testPositionPort();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}