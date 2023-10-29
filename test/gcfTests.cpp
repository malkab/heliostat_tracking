#include <gtest/gtest.h>
#include "gcf.h"

// Constant to represent the value of 2π
constexpr double TwoPi = 6.283185307179586;

// Test for normalizeAngle
TEST(GcfTest, NormalizeAngle) {
    // Testing the boundary
    EXPECT_DOUBLE_EQ(gcf::normalizeAngle(0.0, 0.0), 0.0);
    
    // Testing values within [0, 2π)
    EXPECT_DOUBLE_EQ(gcf::normalizeAngle(1.0, 0.0), 1.0);
    EXPECT_DOUBLE_EQ(gcf::normalizeAngle(TwoPi, 0.0), 0.0);  // It should wrap around
    
    // Testing values outside [0, 2π)
    EXPECT_DOUBLE_EQ(gcf::normalizeAngle(3*TwoPi + 1.0, 0.0), 1.0);  // It should wrap around to 1.0
    
    // Testing negative values
    EXPECT_DOUBLE_EQ(gcf::normalizeAngle(-1.0, 0.0), TwoPi - 1.0); // It should wrap to 2π - 1
    
    // Testing non-zero phi0
    EXPECT_DOUBLE_EQ(gcf::normalizeAngle(1.0, 1.0), 1.0);
    EXPECT_DOUBLE_EQ(gcf::normalizeAngle(TwoPi + 2.0, 1.0), 2.0);  // It should wrap around to 2.0 given the phi0 = 1.0
}


