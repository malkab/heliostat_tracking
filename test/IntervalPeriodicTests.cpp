#include <gtest/gtest.h>
#include "IntervalPeriodic.h"

constexpr double Pi = 3.14159265358979323846;

// Test to check the inherited constructor
TEST(IntervalPeriodicTest, Constructor) {
    IntervalPeriodic iv(1.0, 4.0);
    EXPECT_DOUBLE_EQ(iv.min(), 1.0);
    EXPECT_DOUBLE_EQ(iv.max(), 4.0);
    EXPECT_TRUE(iv.isValid());
}

// Test for normalizeAngle
TEST(IntervalPeriodicTest, NormalizeAngle) {
    IntervalPeriodic iv(0.0, 2 * Pi);  // Interval from 0 to 2Pi

    EXPECT_DOUBLE_EQ(iv.normalizeAngle(0.0), 0.0);        // Angle already inside the interval
    EXPECT_DOUBLE_EQ(iv.normalizeAngle(2 * Pi), 0.0);     // At the boundary, should return start of interval
    EXPECT_DOUBLE_EQ(iv.normalizeAngle(2.5 * Pi), 0.5 * Pi);  // Angle outside the interval
    EXPECT_DOUBLE_EQ(iv.normalizeAngle(-0.5 * Pi), 1.5 * Pi); // Negative angle outside the interval
}

// Test inherited functionalities
TEST(IntervalPeriodicTest, InheritedSetLimits) {
    IntervalPeriodic iv(4.0, 1.0);
    EXPECT_DOUBLE_EQ(iv.min(), 1.0);
    EXPECT_DOUBLE_EQ(iv.max(), 4.0);
}

TEST(IntervalPeriodicTest, InheritedSize) {
    IntervalPeriodic iv(1.0, 4.0);
    EXPECT_DOUBLE_EQ(iv.size(), 3.0);
}

TEST(IntervalPeriodicTest, InheritedMid) {
    IntervalPeriodic iv(1.0, 4.0);
    EXPECT_DOUBLE_EQ(iv.mid(), 2.5);
}

TEST(IntervalPeriodicTest, InheritedExpand) {
    IntervalPeriodic iv(1.0, 4.0);
    iv.expand(5.0);
    EXPECT_DOUBLE_EQ(iv.max(), 5.0);

    iv.expand(0.0);
    EXPECT_DOUBLE_EQ(iv.min(), 0.0);

    IntervalPeriodic iv2(6.0, 7.0);
    iv.expand(iv2);
    EXPECT_DOUBLE_EQ(iv.max(), 7.0);
}

TEST(IntervalPeriodicTest, InheritedIsInside) {
    IntervalPeriodic iv(1.0, 4.0);
    EXPECT_TRUE(iv.isInside(3.0));
    EXPECT_FALSE(iv.isInside(4.5));
}

TEST(IntervalPeriodicTest, InheritedIntersect) {
    IntervalPeriodic iv(1.0, 4.0);
    IntervalPeriodic iv2(3.5, 5.0);
    EXPECT_TRUE(iv.intersect(iv2));

    IntervalPeriodic iv3(5.0, 6.0);
    EXPECT_FALSE(iv.intersect(iv3));
}

TEST(IntervalPeriodicTest, InheritedNormalizedMapping) {
    IntervalPeriodic iv(1.0, 4.0);
    EXPECT_DOUBLE_EQ(iv.toNormalized(2.5), 0.5);
    EXPECT_DOUBLE_EQ(iv.fromNormalized(0.5), 2.5);
}
