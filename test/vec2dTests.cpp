#include <limits>
#include <sstream>
#include <gtest/gtest.h>
#include "vec2d.h"

// Constructor Tests
TEST(Vec2dTest, Constructor) {
    vec2d defaultConstructed; // uses default arguments
    EXPECT_DOUBLE_EQ(defaultConstructed.x, 0.);
    EXPECT_DOUBLE_EQ(defaultConstructed.y, 0.);

    vec2d a(1.5, 2.5);
    EXPECT_DOUBLE_EQ(a.x, 1.5);
    EXPECT_DOUBLE_EQ(a.y, 2.5);
}

// Constants Tests
TEST(Vec2dTest, Constants) {
    EXPECT_EQ(vec2d::Zero, vec2d(0., 0.));
    EXPECT_EQ(vec2d::One, vec2d(1., 1.));
    EXPECT_EQ(vec2d::UnitX, vec2d(1., 0.));
    EXPECT_EQ(vec2d::UnitY, vec2d(0., 1.));
}

// Arithmetic Operation Tests
TEST(Vec2dTest, ArithmeticOperations) {
    vec2d a(1, 2);
    vec2d b(3, 4);

    EXPECT_EQ(a + b, vec2d(4, 6));
    EXPECT_EQ(a - b, vec2d(-2, -2));
    EXPECT_EQ(-a, vec2d(-1, -2));
    EXPECT_EQ(a * 2, vec2d(2, 4));
    EXPECT_EQ(a * b, vec2d(3, 8));
    EXPECT_EQ(a / 2, vec2d(0.5, 1));
    EXPECT_EQ(a / b, vec2d(1./3., 0.5));
}

// Arithmetic Assignments Tests
TEST(Vec2dTest, ArithmeticAssignments) {
    vec2d a(1, 2);
    vec2d b(3, 4);

    a += b;
    EXPECT_EQ(a, vec2d(4, 6));
    a -= b;
    EXPECT_EQ(a, vec2d(1, 2));
    a *= 2;
    EXPECT_EQ(a, vec2d(2, 4));
    a /= 2;
    EXPECT_EQ(a, vec2d(1, 2));
}

// Comparison Tests
TEST(Vec2dTest, Comparison) {
    vec2d a(1, 2);
    vec2d b(1 + (std::numeric_limits<double>::epsilon())*0.5, 2); // a tiny deviation

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a <= b);
}

// Element Access Tests
TEST(Vec2dTest, ElementAccess) {
    vec2d a(1.5, 2.5);

    EXPECT_DOUBLE_EQ(a[0], 1.5);
    EXPECT_DOUBLE_EQ(a[1], 2.5);
    a[0] = 3.0;
    a[1] = 4.0;
    EXPECT_EQ(a, vec2d(3.0, 4.0));
}

// Normalize and Norm Tests
TEST(Vec2dTest, NormalizeMethods) {
    vec2d a(3, 4);
    EXPECT_EQ(a.norm2(), 25);
    EXPECT_EQ(a.norm(), 5);
    EXPECT_TRUE(a.normalize());
    EXPECT_NEAR(a.norm(), 1.0, 1e-9);

    vec2d zeroVec(0, 0);
    EXPECT_FALSE(zeroVec.normalize());
}

// Utility Functions Tests
TEST(Vec2dTest, UtilityMethods) {
    vec2d a(-2, 3);
    vec2d b(2, 0);

    EXPECT_EQ(a.abs(), vec2d(2, 3));
    EXPECT_DOUBLE_EQ(a.min(), -2);
    EXPECT_DOUBLE_EQ(a.max(), 3);
    EXPECT_EQ(a.maxDimension(), 1);
    EXPECT_EQ(vec2d::min(a, b), vec2d(-2, 0));
    EXPECT_EQ(vec2d::max(a, b), vec2d(2, 3));
}

// Scalar Multiplication from the Left Test
TEST(Vec2dTest, ScalarMultiplicationFromLeft) {
    vec2d v(2, 3);
    double s = 4.0;
    EXPECT_EQ(s * v, vec2d(8, 12));
}

// Dot Product Test
TEST(Vec2dTest, DotProduct) {
    vec2d a(1, 2);
    vec2d b(3, 4);
    EXPECT_DOUBLE_EQ(dot(a, b), 11); // 1*3 + 2*4 = 3 + 8 = 11
}

// Cross Product Test
TEST(Vec2dTest, CrossProduct) {
    vec2d a(1, 2);
    vec2d b(3, 4);
    EXPECT_DOUBLE_EQ(cross(a, b), -2); // 1*4 - 2*3 = 4 - 6 = -2
}

// Stream Output Test
TEST(Vec2dTest, StreamOutput) {
    vec2d a(1.23, 4.56);
    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "1.23, 4.56");
}
