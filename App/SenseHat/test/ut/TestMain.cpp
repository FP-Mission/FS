// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include <Fw/Test/UnitTest.hpp>
#include "Tester.hpp"

TEST(Nominal, SenseHat) {
    App::Tester tester;
    tester.toDo();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
