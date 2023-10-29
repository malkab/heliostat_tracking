#include <gtest/gtest.h>
#include "ArmatureJoint.h"

bool areTransformsEqual(const Transform& t1, const Transform& t2);

class ArmatureJointTest : public ::testing::Test {
protected:
    vec3d defaultShift;
    vec3d defaultAxis;
    IntervalPeriodic defaultAngleInterval;

    vec3d expectedShift;
    vec3d expectedAxis;
    IntervalPeriodic expectedAngleInterval;

    void SetUp() override {
        defaultShift = vec3d::Zero;
        defaultAxis = vec3d::UnitZ;
        defaultAngleInterval = IntervalPeriodic(-90.*gcf::degree, 90.*gcf::degree);

        expectedShift = vec3d(2.0, 3.0, 4.0);
        expectedAxis = vec3d(1.0, 0.0, 0.0);
        expectedAngleInterval = IntervalPeriodic(0.0, gcf::Pi);
    }
};

// Constructor Tests
TEST_F(ArmatureJointTest, DefaultConstructor) {
    ArmatureJoint joint;

    EXPECT_EQ(joint.shift, defaultShift);
    EXPECT_EQ(joint.axis, defaultAxis);

    IntervalPeriodic angleInterval = joint.angles;
    EXPECT_EQ(angleInterval.min(), defaultAngleInterval.min());
    EXPECT_EQ(angleInterval.max(), defaultAngleInterval.max());
}

TEST_F(ArmatureJointTest, ParameterizedConstructor) {
    ArmatureJoint joint(expectedShift, expectedAxis, expectedAngleInterval);

    EXPECT_EQ(joint.shift, expectedShift);
    EXPECT_EQ(joint.axis.normalized(), expectedAxis.normalized());

    IntervalPeriodic angleInterval = joint.angles;
    EXPECT_EQ(angleInterval.min(), expectedAngleInterval.min());
    EXPECT_EQ(angleInterval.max(), expectedAngleInterval.max());
}

// Testing Transform generation for various angles
TEST_F(ArmatureJointTest, TransformForAngle) {
    ArmatureJoint joint(expectedShift, expectedAxis, expectedAngleInterval);
    double testAngle = 45. * gcf::degree;

    Transform expectedTransform = Transform::translate(expectedShift) * Transform::rotate(testAngle, expectedAxis);
    Transform actualTransform = joint.getTransform(testAngle);
    
    // Here, you might want a utility function to compare matrices/transforms.
    EXPECT_TRUE(areTransformsEqual(expectedTransform, actualTransform));
}

// Testing normalizeAngle function
TEST_F(ArmatureJointTest, NormalizeAngle) {
    double minAngle = -90. * gcf::degree;
    double maxAngle = 90. * gcf::degree;
    IntervalPeriodic angleInterval(minAngle, maxAngle);

    EXPECT_DOUBLE_EQ(angleInterval.normalizeAngle(180.*gcf::degree), 180.*gcf::degree);
    EXPECT_DOUBLE_EQ(angleInterval.normalizeAngle(-180.*gcf::degree), 180.*gcf::degree);
    EXPECT_DOUBLE_EQ(angleInterval.normalizeAngle(0.0), 0.0);
}

bool areTransformsEqual(const Transform& t1, const Transform& t2) {
    // For simplicity, this example just checks if the matrices from both transforms are the same.
    // Depending on precision issues, you might want to use an epsilon-based comparison for each element of the matrix.
    return *(t1.getMatrix()) == *(t2.getMatrix());
}
