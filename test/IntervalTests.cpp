#include <gtest/gtest.h>
#include "Interval.h"
 
// Test for the constructor
TEST(IntervalTest, DefaultConstructor) {
    Interval iv;
    EXPECT_FALSE(iv.isValid());
}

// Parameterized Constructor and setLimits Tests
TEST(IntervalTest, ParameterizedConstructor) {
    Interval iv(2.0, 5.0);
    EXPECT_DOUBLE_EQ(iv.min(), 2.0);
    EXPECT_DOUBLE_EQ(iv.max(), 5.0);
    
    Interval iv_reversed(5.0, 2.0);
    EXPECT_DOUBLE_EQ(iv_reversed.min(), 2.0);
    EXPECT_DOUBLE_EQ(iv_reversed.max(), 5.0);
}

TEST(IntervalTest, SetLimits) {
    Interval iv;
    iv.setLimits(3.0, 1.0);
    EXPECT_DOUBLE_EQ(iv.min(), 1.0);
    EXPECT_DOUBLE_EQ(iv.max(), 3.0);
}

TEST(IntervalTest, IsValid) {
    Interval iv_invalid;
    EXPECT_FALSE(iv_invalid.isValid());
    
    Interval iv_valid(2.0, 5.0);
    EXPECT_TRUE(iv_valid.isValid());
}

// Test for size, mid, min and max
TEST(IntervalTest, SizeAndMid) {
    Interval iv(1.0, 4.0);
    EXPECT_DOUBLE_EQ(iv.size(), 3.0);
    EXPECT_DOUBLE_EQ(iv.mid(), 2.5);
    EXPECT_DOUBLE_EQ(iv.min(), 1.0);
    EXPECT_DOUBLE_EQ(iv.max(), 4.0);
}

// Expand related tests
TEST(IntervalTest, ExpandLimits) {
    Interval iv(1.0, 4.0);
    iv.expandLimits(1.0);
    EXPECT_DOUBLE_EQ(iv.min(), 0.0);
    EXPECT_DOUBLE_EQ(iv.max(), 5.0);
}

TEST(IntervalTest, ExpandValue) {
    Interval iv(1.0, 4.0);
    iv.expand(0.5);
    EXPECT_DOUBLE_EQ(iv.min(), 0.5);
    iv.expand(5.0);
    EXPECT_DOUBLE_EQ(iv.max(), 5.0);
}

TEST(IntervalTest, ExpandInterval) {
    Interval iv(1.0, 4.0);
    Interval iv2(-1.0, 2.0);
    iv.expand(iv2);
    EXPECT_DOUBLE_EQ(iv.min(), -1.0);
    EXPECT_DOUBLE_EQ(iv.max(), 4.0);
}

TEST(IntervalTest, OperatorExpandValue) {
    Interval iv(1.0, 4.0);
    iv << 0.5;
    EXPECT_DOUBLE_EQ(iv.min(), 0.5);
}

TEST(IntervalTest, OperatorExpandInterval) {
    Interval iv(1.0, 4.0);
    Interval iv2(-1.0, 2.0);
    iv << iv2;
    EXPECT_DOUBLE_EQ(iv.min(), -1.0);
}

// Inside and Intersect tests
TEST(IntervalTest, IsInside) {
    Interval iv(1.0, 4.0);
    EXPECT_TRUE(iv.isInside(2.0));
    EXPECT_FALSE(iv.isInside(5.0));
}

TEST(IntervalTest, Intersect) {
    Interval iv(1.0, 4.0);
    Interval iv2(3.0, 5.0);
    EXPECT_TRUE(iv.intersect(iv2));
    
    Interval iv3(5.0, 6.0);
    EXPECT_FALSE(iv.intersect(iv3));
}

// Normalized conversion tests
TEST(IntervalTest, NormalizedConversion) {
    Interval iv(1.0, 5.0);
    EXPECT_DOUBLE_EQ(iv.toNormalized(3.0), 0.5);
    EXPECT_DOUBLE_EQ(iv.fromNormalized(0.5), 3.0);
}

// Static members tests
TEST(IntervalTest, StaticMembers) {
    EXPECT_DOUBLE_EQ(Interval::UnitPositive.min(), 0.0);
    EXPECT_DOUBLE_EQ(Interval::UnitPositive.max(), 1.0);
    
    EXPECT_DOUBLE_EQ(Interval::UnitCentered.min(), -0.5);
    EXPECT_DOUBLE_EQ(Interval::UnitCentered.max(), 0.5);
}