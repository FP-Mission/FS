// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"
#include <Fw/Test/UnitTest.hpp>

TEST(Nominal, TestCreatedTree) {
    Ref::Tester tester;
    TEST_CASE(PiCamera.0,"Test directory are created");
    tester.testCreatedDirectory();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
