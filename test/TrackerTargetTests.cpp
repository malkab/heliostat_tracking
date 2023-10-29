#include "gtest/gtest.h"
#include "TrackerTarget.h"

// Fixture for TrackerTarget tests
class TrackerTargetTest : public ::testing::Test {
protected:
    TrackerTarget target;

    // Setup and Teardown can be added if needed
    void SetUp() override {
        // Code here will be called immediately after the constructor, right before each test
    }

    void TearDown() override {
        // Code here will be called immediately after each test, right before the destructor
    }
};

TEST_F(TrackerTargetTest, DefaultConstructorSetsAimingTypeToGlobal) {
    EXPECT_EQ(target.aimingType, TrackerTarget::global);
}

TEST_F(TrackerTargetTest, DefaultConstructorSetsAimingPointToGivenValues) {
    EXPECT_EQ(target.aimingPoint.x, 0.f);
    EXPECT_EQ(target.aimingPoint.y, 0.f);
    EXPECT_EQ(target.aimingPoint.z, 100.f);
}

TEST_F(TrackerTargetTest, DefaultConstructorSetsAnglesToZero) {
    EXPECT_EQ(target.angles.x, 0.f);
    EXPECT_EQ(target.angles.y, 0.f);
}

