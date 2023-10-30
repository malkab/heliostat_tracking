#include <gtest/gtest.h>
#include "vec3d.h"

constexpr double Pi = 3.14159265358979323846;

class Vec3dTest : public ::testing::Test {
protected:
    vec3d v1, v2, v3;

    void SetUp() override {
        v1 = vec3d(1.0, 2.0, 3.0);
        v2 = vec3d(4.0, 5.0, 6.0);
        v3 = vec3d(0.0, 0.0, 0.0);
    }
};

// Constructor tests
TEST_F(Vec3dTest, DefaultConstructor) {
    vec3d v;

    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST_F(Vec3dTest, ParameterizedConstructor) {
    vec3d v(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

TEST_F(Vec3dTest, Vec2dConstructor) {
    vec2d v2(4.0, 5.0);
    vec3d v(v2, 6.0);

    EXPECT_DOUBLE_EQ(v.x, 4.0);
    EXPECT_DOUBLE_EQ(v.y, 5.0);
    EXPECT_DOUBLE_EQ(v.z, 6.0);
}

TEST_F(Vec3dTest, Vec2dConstructorWithDefaultZ) {
    vec2d v2(7.0, 8.0);
    vec3d v(v2);

    EXPECT_DOUBLE_EQ(v.x, 7.0);
    EXPECT_DOUBLE_EQ(v.y, 8.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);  // Default value of z
}

TEST_F(Vec3dTest, FloatPointerConstructor) {
    float values[3] = {9.0f, 10.0f, 11.0f};
    vec3d v(values);

    EXPECT_DOUBLE_EQ(v.x, 9.0);
    EXPECT_DOUBLE_EQ(v.y, 10.0);
    EXPECT_DOUBLE_EQ(v.z, 11.0);
}

TEST_F(Vec3dTest, DoublePointerConstructor) {
    double values[3] = {12.0, 13.0, 14.0};
    vec3d v(values);

    EXPECT_DOUBLE_EQ(v.x, 12.0);
    EXPECT_DOUBLE_EQ(v.y, 13.0);
    EXPECT_DOUBLE_EQ(v.z, 14.0);
}

// Constants tests
TEST_F(Vec3dTest, StaticConstantZero) {
    vec3d v = vec3d::Zero;

    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST_F(Vec3dTest, StaticConstantOne) {
    vec3d v = vec3d::One;

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 1.0);
    EXPECT_DOUBLE_EQ(v.z, 1.0);
}

TEST_F(Vec3dTest, StaticConstantUnitX) {
    vec3d v = vec3d::UnitX;

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST_F(Vec3dTest, StaticConstantUnitY) {
    vec3d v = vec3d::UnitY;

    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 1.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST_F(Vec3dTest, StaticConstantUnitZ) {
    vec3d v = vec3d::UnitZ;

    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 1.0);
}

// Arithmetic Operation Tests
TEST_F(Vec3dTest, Addition) {
    vec3d result = v1 + v2;

    EXPECT_DOUBLE_EQ(result.x, 5.0);
    EXPECT_DOUBLE_EQ(result.y, 7.0);
    EXPECT_DOUBLE_EQ(result.z, 9.0);
}

TEST_F(Vec3dTest, Negation) {
    vec3d result = -v1;

    EXPECT_DOUBLE_EQ(result.x, -1.0);
    EXPECT_DOUBLE_EQ(result.y, -2.0);
    EXPECT_DOUBLE_EQ(result.z, -3.0);
}

TEST_F(Vec3dTest, MultiplyByScalar) {
    double s = 2.0;
    vec3d result = v1 * s;

    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
}

TEST_F(Vec3dTest, MultiplyByVector) {
    vec3d result = v1 * v2;

    EXPECT_DOUBLE_EQ(result.x, 4.0);
    EXPECT_DOUBLE_EQ(result.y, 10.0);
    EXPECT_DOUBLE_EQ(result.z, 18.0);
}

TEST_F(Vec3dTest, DivideByScalar) {
    double s = 2.0;
    vec3d result = v1 / s;

    EXPECT_DOUBLE_EQ(result.x, 0.5);
    EXPECT_DOUBLE_EQ(result.y, 1.0);
    EXPECT_DOUBLE_EQ(result.z, 1.5);
}

TEST_F(Vec3dTest, DivideByVector) {
    vec3d result = v1 / v2;

    EXPECT_DOUBLE_EQ(result.x, 1.0/4.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0/5.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0/6.0);
}

// Arithmetic Assignments Tests

TEST_F(Vec3dTest, AdditionAssignment) {
    v1 += v2;

    EXPECT_DOUBLE_EQ(v1.x, 5.0);
    EXPECT_DOUBLE_EQ(v1.y, 7.0);
    EXPECT_DOUBLE_EQ(v1.z, 9.0);
}

TEST_F(Vec3dTest, SubtractionAssignment) {
    v1 -= v2;

    EXPECT_DOUBLE_EQ(v1.x, -3.0);
    EXPECT_DOUBLE_EQ(v1.y, -3.0);
    EXPECT_DOUBLE_EQ(v1.z, -3.0);
}

TEST_F(Vec3dTest, MultiplicationAssignmentByScalar) {
    double s = 2.0;
    v1 *= s;

    EXPECT_DOUBLE_EQ(v1.x, 2.0);
    EXPECT_DOUBLE_EQ(v1.y, 4.0);
    EXPECT_DOUBLE_EQ(v1.z, 6.0);
}

TEST_F(Vec3dTest, DivisionAssignmentByScalar) {
    double s = 2.0;
    v1 /= s;

    EXPECT_DOUBLE_EQ(v1.x, 0.5);
    EXPECT_DOUBLE_EQ(v1.y, 1.0);
    EXPECT_DOUBLE_EQ(v1.z, 1.5);
}

// Comparison Tests
TEST_F(Vec3dTest, Equality) {
    vec3d temp = v1;
    EXPECT_TRUE(v1 == temp);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(Vec3dTest, Inequality) {
    EXPECT_FALSE(v1 != v1);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(Vec3dTest, LessThanOrEqualTo) {
    vec3d v4(1.0, 2.0, 2.9);
    vec3d v5(1.0, 2.0, 3.1);

    EXPECT_TRUE(v1 <= v2);
    EXPECT_FALSE(v1 <= v3);
    EXPECT_TRUE(v4 <= v1);
    EXPECT_FALSE(v5 <= v1);
}

// Element Access Tests
TEST_F(Vec3dTest, ElementAccessConst) {
    EXPECT_DOUBLE_EQ(v1[0], 1.0);
    EXPECT_DOUBLE_EQ(v1[1], 2.0);
    EXPECT_DOUBLE_EQ(v1[2], 3.0);

    EXPECT_DOUBLE_EQ(v2[0], 4.0);
    EXPECT_DOUBLE_EQ(v2[1], 5.0);
    EXPECT_DOUBLE_EQ(v2[2], 6.0);

    EXPECT_DOUBLE_EQ(v3[0], 0.0);
    EXPECT_DOUBLE_EQ(v3[1], 0.0);
    EXPECT_DOUBLE_EQ(v3[2], 0.0);
}

TEST_F(Vec3dTest, ElementAccessNonConst) {
    v1[0] = 7.0;
    v1[1] = 8.0;
    v1[2] = 9.0;

    EXPECT_DOUBLE_EQ(v1[0], 7.0);
    EXPECT_DOUBLE_EQ(v1[1], 8.0);
    EXPECT_DOUBLE_EQ(v1[2], 9.0);
}

// Normalize and Norm Tests
TEST_F(Vec3dTest, Norm2) {
    EXPECT_DOUBLE_EQ(v1.norm2(), 14.0);  // 1*1 + 2*2 + 3*3
    EXPECT_DOUBLE_EQ(v2.norm2(), 77.0);  // 4*4 + 5*5 + 6*6
    EXPECT_DOUBLE_EQ(v3.norm2(), 0.0);
}

TEST_F(Vec3dTest, Norm) {
    EXPECT_DOUBLE_EQ(v1.norm(), std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(v2.norm(), std::sqrt(77.0));
    EXPECT_DOUBLE_EQ(v3.norm(), 0.0);
}

TEST_F(Vec3dTest, Normalized) {
    vec3d normalized_v1 = v1.normalized();
    vec3d normalized_v2 = v2.normalized();

    EXPECT_DOUBLE_EQ(normalized_v1.norm(), 1.0);
    EXPECT_DOUBLE_EQ(normalized_v2.norm(), 1.0);

    // Ensure original vectors are unchanged
    EXPECT_DOUBLE_EQ(v1.norm(), std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(v2.norm(), std::sqrt(77.0));
}

TEST_F(Vec3dTest, Normalize) {
    EXPECT_TRUE(v1.normalize());
    EXPECT_TRUE(v2.normalize());
    EXPECT_FALSE(v3.normalize());  // Should return false for zero vector

    EXPECT_DOUBLE_EQ(v1.norm(), 1.0);
    EXPECT_DOUBLE_EQ(v2.norm(), 1.0);
    EXPECT_DOUBLE_EQ(v3.norm(), 0.0);
}

// Vector transformations
TEST_F(Vec3dTest, Projected) {  
    // Project v1 onto a plane normal to v2
    vec3d n = v2.normalized();
    vec3d projected_v1_on_v2 = v1.projected(n);

    vec3d expected_projection(-0.6623376623376622, -0.07792207792207773, 0.506493506493507);

    EXPECT_NEAR(projected_v1_on_v2.x, expected_projection.x, 1e-9);
    EXPECT_NEAR(projected_v1_on_v2.y, expected_projection.y, 1e-9);
    EXPECT_NEAR(projected_v1_on_v2.z, expected_projection.z, 1e-9) << "projected_v1_on_v2: " << projected_v1_on_v2 << " expected_projection:" << expected_projection;

    // Project onto a unit vector, say UnitX
    vec3d projected_v1_on_unitX = v1.projected(vec3d::UnitX);
    EXPECT_TRUE(projected_v1_on_unitX == vec3d(0.0, 2.0, 3.0)) << "projected_v1_on_unitX: " << projected_v1_on_unitX << " expected_projection:" << vec3d(1.0, 0.0, 0.0);
}

TEST_F(Vec3dTest, Reflected) {
    // Reflect v1 about v2
    vec3d n = v2.normalized();
    vec3d reflected_v1_about_v2 = v1.reflected(n);
    vec3d expected_reflection(-2.3246753246753245, -2.1558441558441555, -1.987012987012986); 
    EXPECT_NEAR(reflected_v1_about_v2.x, expected_reflection.x, 1e-9);
    EXPECT_NEAR(reflected_v1_about_v2.x, expected_reflection.x, 1e-9);
    EXPECT_NEAR(reflected_v1_about_v2.x, expected_reflection.x, 1e-9);

    // Reflect v1 about UnitX
    vec3d reflected_v1_about_unitX = v1.reflected(vec3d::UnitX);
    EXPECT_TRUE(reflected_v1_about_unitX == vec3d(-1.0, 2.0, 3.0)) << "reflected_v1_about_unitX: " << reflected_v1_about_v2 << " expected_reflection:" << vec3d(-1.0, 2.0, 3.0);
}

TEST_F(Vec3dTest, Reflect) {
    // Test reflection sing the vectors defined in Vec3dTest
    vec3d reflected_v1 = v1.reflect(v2);
    vec3d expectedReflection_v1(-0.5714285714285712, -4.142857142857142, -7.7142857142857135);
    EXPECT_NEAR(reflected_v1.x, expectedReflection_v1.x, 1e-9);
    EXPECT_NEAR(reflected_v1.y, expectedReflection_v1.y, 1e-9);
    EXPECT_NEAR(reflected_v1.z, expectedReflection_v1.z, 1e-9);

    // Test reflection of v2 around the x-axis plane
    vec3d normal_x(1.0, 0.0, 0.0);  // Normal for x-axis plane reflection
    vec3d reflected_x = normal_x.reflect(v2);
    vec3d expected_reflection_x(-v2.x, v2.y, v2.z);
    EXPECT_NEAR(reflected_x.x, expected_reflection_x.x, 1e-9);
    EXPECT_NEAR(reflected_x.y, expected_reflection_x.y, 1e-9);
    EXPECT_NEAR(reflected_x.z, expected_reflection_x.z, 1e-9);

    // Test reflection of v2 around the y-axis plane
    vec3d normal_y(0.0, 1.0, 0.0);  // Normal for y-axis plane reflection
    vec3d reflected_y = normal_y.reflect(v2);
    vec3d expected_reflection_y(v2.x, -v2.y, v2.z);
    EXPECT_NEAR(reflected_y.x, expected_reflection_y.x, 1e-9);
    EXPECT_NEAR(reflected_y.y, expected_reflection_y.y, 1e-9);
    EXPECT_NEAR(reflected_y.z, expected_reflection_y.z, 1e-9);

    // Test reflection of v2 around the z-axis plane
    vec3d normal_z(0.0, 0.0, 1.0);  // Normal for z-axis plane reflection
    vec3d reflected_z = normal_z.reflect(v2);
    vec3d expected_reflection_z(v2.x, v2.y, -v2.z);
    EXPECT_NEAR(reflected_z.x, expected_reflection_z.x, 1e-9);
    EXPECT_NEAR(reflected_z.y, expected_reflection_z.y, 1e-9);
    EXPECT_NEAR(reflected_z.z, expected_reflection_z.z, 1e-9);
}

// Utility Methods Tests
TEST_F(Vec3dTest, UtilityMethods) {
    // Testing min method
    EXPECT_DOUBLE_EQ(v1.min(), 1.0);

    // Testing max method
    EXPECT_DOUBLE_EQ(v1.max(), 3.0);

    // Testing abs method
    vec3d v_abs = vec3d(-2.0, 3.0, -4.0).abs();
    EXPECT_DOUBLE_EQ(v_abs.x, 2.0);
    EXPECT_DOUBLE_EQ(v_abs.y, 3.0);
    EXPECT_DOUBLE_EQ(v_abs.z, 4.0);

    // Testing maxDimension method
    EXPECT_EQ(v1.maxDimension(), 2);  // Because z = 3.0 is the largest among (1.0, 2.0, 3.0)

    // Testing findOrthogonal method
    // This can be complex due to the nature of the function. We should mainly ensure that the result is orthogonal.
    vec3d v_orthogonal = v1.findOrthogonal();
    EXPECT_DOUBLE_EQ(dot(v1, v_orthogonal), 0.0);  // Check for orthogonality
}

// Static Utility Methods Tests
TEST_F(Vec3dTest, StaticUtilityMethods) {
    // Testing static min method
    vec3d min_vec = vec3d::min(v1, v2);
    EXPECT_DOUBLE_EQ(min_vec.x, 1.0);
    EXPECT_DOUBLE_EQ(min_vec.y, 2.0);
    EXPECT_DOUBLE_EQ(min_vec.z, 3.0);

    // Testing static max method
    vec3d max_vec = vec3d::max(v1, v2);
    EXPECT_DOUBLE_EQ(max_vec.x, 4.0);
    EXPECT_DOUBLE_EQ(max_vec.y, 5.0);
    EXPECT_DOUBLE_EQ(max_vec.z, 6.0);

    // Testing directionAE method
    // This is a tricky method to test due to trigonometry. A simple test might involve known inputs and outputs.
    // For simplicity's sake, let's just pick azimuth = 0 and elevation = pi/2, which should yield UnitZ.
    vec3d dir_vec = vec3d::directionAE(0.0, Pi/2.0);
    EXPECT_TRUE(dir_vec == vec3d::UnitZ);  // Should equal UnitZ
}

// External Methods Tests
TEST_F(Vec3dTest, ScalarMultiplicationLeft) {
    vec3d result = 2.0 * v1;
    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
}

TEST_F(Vec3dTest, DotProduct) {
    double result = dot(v1, v2);
    EXPECT_DOUBLE_EQ(result, 32.0);  // 1*4 + 2*5 + 3*6
}

TEST_F(Vec3dTest, CrossProduct) {
    vec3d result = cross(v1, v2);
    // Result should be: (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4)
    EXPECT_DOUBLE_EQ(result.x, -3.0);
    EXPECT_DOUBLE_EQ(result.y, 6.0);
    EXPECT_DOUBLE_EQ(result.z, -3.0);
}

TEST_F(Vec3dTest, TripleProduct) {
    // triple(a, b, c) = dot(a, cross(b, c))
    double result = triple(v1, v2, v3); // Since v3 is (0,0,0), cross product with any vector will also be (0,0,0). Hence, result = dot(v1, (0,0,0))
    EXPECT_DOUBLE_EQ(result, 0.0); 
}
