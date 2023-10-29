#include "gtest/gtest.h"

#include "gcf.h"
#include "Transform.h"

class TransformTest : public ::testing::Test {
protected:
    double matrixValues1[4][4];

    Transform identity;
    Transform t1;
    Transform t2;
    Transform t3;
    Transform t4;

    TransformTest() {
        // Sample matrix values for test
        matrixValues1[0][0] = 1; matrixValues1[0][1] = 0; matrixValues1[0][2] = 0; matrixValues1[0][3] = 2;
        matrixValues1[1][0] = 0; matrixValues1[1][1] = 1; matrixValues1[1][2] = 0; matrixValues1[1][3] = 3;
        matrixValues1[2][0] = 0; matrixValues1[2][1] = 0; matrixValues1[2][2] = 1; matrixValues1[2][3] = 4;
        matrixValues1[3][0] = 0; matrixValues1[3][1] = 0; matrixValues1[3][2] = 0; matrixValues1[3][3] = 1;

        // Initialize identity and transformations for testing
        identity = Transform::Identity;
        t1 = Transform(matrixValues1);

        double matrixValues2[4][4] = {
            {1, 0, 0, 5},
            {0, 1, 0, 6},
            {0, 0, 1, 7},
            {0, 0, 0, 1}
        };
        t2 = Transform(matrixValues2);

        double matrixValues3[4][4] = {
            {2, 0, 0, 0},
            {0, 3, 0, 0},
            {0, 0, 4, 0},
            {0, 0, 0, 1}
        };
        t3 = Transform(matrixValues3);

        double matrixValues4[4][4] = {
            {2, 0, 0, 1},
            {0, 3, 0, 2},
            {0, 0, 4, 3},
            {0, 0, 0, 1}
        };
        t4 = Transform(matrixValues4);
    }
};

TEST_F(TransformTest, DefaultConstructorTest) {
    Transform t;
    auto pMatrix = t.getMatrix();
    EXPECT_TRUE(pMatrix == nullptr);
}

TEST_F(TransformTest, MatrixConstructorTest) {
    // Check if the matrix constructor initializes the matrix correctly
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(t1.getMatrix()->m[i][j], matrixValues1[i][j]);
        }
    }
}

TEST_F(TransformTest, TransposedTest) {
    Transform transposed = t1.transposed();

    // Check if the transposed matrix is correct
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(transposed.getMatrix()->m[j][i], t1.getMatrix()->m[i][j]);
        }
    }
}

TEST_F(TransformTest, InversedTest) {
    // Create a test transformation matrix
    Transform t(
        1, 2, 3, 4,
        5, 62.8, 7, 8,
        9, 10, 11, 12,
        13, 14, 15.00, 16.2
    );

    // Calculate the inverse of the matrix manually
    double inversedMatrixValues[4][4] = {
        {0.566901, -0.00880282, -3.5581, 2.5}, 
        {-0.00880282, 0.0176056, -0.00880282, 0.0}, 
        {-3.1831, -0.00880282, 11.1919, -7.5}, 
        {2.5, 0.0, -7.5, 5.}
    };

    Transform inversed = t.inversed();

    // Check each element of the calculated inverse
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_NEAR(inversed.getMatrix()->m[i][j], inversedMatrixValues[i][j], 1e-5);
        }
    }
}

TEST_F(TransformTest, MultVecMatrixTest) {
    vec3d v(1, 2, 3);
    vec3d result = t3.multVecMatrix(v);

    // Check if the transformation applies correctly
    EXPECT_EQ(result.x, 2); // 2x1 = 2
    EXPECT_EQ(result.y, 6); // 3x2 = 6
    EXPECT_EQ(result.z, 12); // 4x3 = 12
}

TEST_F(TransformTest, TransformPointTest) {
    vec3d p(1, 1, 1);
    vec3d result = t4.transformPoint(p);

    // Check if the transformation applies correctly (includes translation)
    EXPECT_EQ(result.x, 3); // (2x1 + 1) = 3
    EXPECT_EQ(result.y, 5); // (3x1 + 2) = 5
    EXPECT_EQ(result.z, 7); // (4x1 + 3) = 7
}

TEST_F(TransformTest, TransformVectorTest) {
    vec3d v(1, 2, 3);
    vec3d result = t3.transformVector(v);

    // Check if the transformation applies correctly (ignores translation)
    EXPECT_EQ(result.x, 2); // 2x1 = 2
    EXPECT_EQ(result.y, 6); // 3x2 = 6
    EXPECT_EQ(result.z, 12); // 4x3 = 12
}

TEST_F(TransformTest, TransformNormalTest) {
    vec3d n(1, 2, 3);
    vec3d result = t3.transformNormal(n);

    // Check if the transformation applies correctly (ignores translation and scales)
    EXPECT_EQ(result.x, 0.5);
    EXPECT_EQ(result.y, 0.6666666666666666666);
    EXPECT_EQ(result.z, 0.75);
}

TEST_F(TransformTest, TransformInverseNormalTest) {
    vec3d n(1, 2, 3);
    vec3d result = t3.transformInverseNormal(n);

    // Check if the transformation applies correctly (ignores translation and scales)
    EXPECT_EQ(result.x, 2.); 
    EXPECT_EQ(result.y, 6.); 
    EXPECT_EQ(result.z, 12.); 
}

TEST_F(TransformTest, OperatorParenthesesTest) {
    vec3d v(1, 1, 1);
    vec3d result = t4(v);

    // Check if the operator() correctly transforms the point
    // The assumption is that in the call to operator(v), v is expected to be a vector and not a point
    // Therefore, the translation of the Transformation matrix is not applied.
    EXPECT_EQ(result.x, 2); // (2x1 + 1) = 3
    EXPECT_EQ(result.y, 3); // (3x1 + 2) = 5
    EXPECT_EQ(result.z, 4); // (4x1 + 3) = 7
}

TEST_F(TransformTest, OperatorParenthesesOutTest) {
    vec3d v(1, 1, 1);
    vec3d result;
    t4(v, result);

    // Check if the operator() correctly transforms the point and stores it in 'ans'
    // The assumption is that in the call to operator(v), v is expected to be a vector and not a point
    // Therefore, the translation of the Transformation matrix is not applied.
    EXPECT_EQ(result.x, 2); 
    EXPECT_EQ(result.y, 3); 
    EXPECT_EQ(result.z, 4); 
}

TEST_F(TransformTest, OperatorEqualTest) {
    // Create a Transform identical to the t1 transform
    Transform t4_copy(
        2, 0, 0, 1,
        0, 3, 0, 2,
        0, 0, 4, 3,
        0, 0, 0, 1
    );

    // Check if the equality operator works correctly
    EXPECT_TRUE(t4 == t4_copy);
}

TEST_F(TransformTest, ScaleTest) {
    // Test the scale transformation
    Transform scale = Transform::scale(2, 3, 4);
    vec3d v(1, 2, 3);
    vec3d result = scale(v);
    
    // Check if scaling is applied correctly
    EXPECT_EQ(result.x, 2); // 2x1 = 2
    EXPECT_EQ(result.y, 6); // 3x2 = 6
    EXPECT_EQ(result.z, 12); // 4x3 = 12
}

TEST_F(TransformTest, TranslateTest) {
    // Test the translation transformation
    Transform translate = Transform::translate(1, 2, 3);
    vec3d point(1, 1, 1);
    vec3d result = translate.transformPoint(point);

    // Check if translation is applied correctly
    EXPECT_EQ(result.x, 2); // 1 + 1 = 2
    EXPECT_EQ(result.y, 3); // 1 + 2 = 3
    EXPECT_EQ(result.z, 4); // 1 + 3 = 4
}

TEST_F(TransformTest, RotateXTest) {
    // Test counterclockwise rotation about the X-axis
    double angle = gcf::Pi/2.0; // 90 degrees
    Transform rotate = Transform::rotateX(angle);
    vec3d v(0, 0, 1);
    vec3d result = rotate(v);

    // Check if rotation about X-axis is applied correctly
    EXPECT_NEAR(result.x, 0, 1e-6);
    EXPECT_NEAR(result.y, -1, 1e-6);
    EXPECT_NEAR(result.z, 0, 1e-6);
}

TEST_F(TransformTest, RotateYTest) {
    // Test rotation about the Y-axis
    double angle = gcf::Pi/2.0; // 90 degrees
    Transform rotate = Transform::rotateY(angle);
    vec3d v(1, 0, 0);
    vec3d result = rotate(v);

    // Check if rotation about Y-axis is applied correctly
    EXPECT_NEAR(result.x, 0, 1e-6);
    EXPECT_NEAR(result.y, 0, 1e-6);
    EXPECT_NEAR(result.z, -1, 1e-6);
}

TEST_F(TransformTest, RotateZTest) {
    // Test rotation about the Z-axis
    double angle = gcf::Pi/2.0; // 90 degrees
    Transform rotate = Transform::rotateZ(angle);
    vec3d v(1, 0, 0);
    vec3d result = rotate(v);

    // Check if rotation about Z-axis is applied correctly
    EXPECT_NEAR(result.x, 0, 1e-6);
    EXPECT_NEAR(result.y, 1, 1e-6);
    EXPECT_NEAR(result.z, 0, 1e-6);
}

TEST_F(TransformTest, RotateTest) {
    // Test general rotation about an arbitrary axis
    double angle = 25.4*gcf::degree; // 25.4 degrees
    vec3d axis(1, 1, 0); // Arbitrary axis
    Transform rotate = Transform::rotate(angle, axis);
    vec3d v(1, 0, 0);
    vec3d result = rotate(v);

    // Check if general rotation is applied correctly
    EXPECT_NEAR(result.x, 0.9516676464316504, 1e-6); 
    EXPECT_NEAR(result.y, 0.04833235356834936, 1e-6); 
    EXPECT_NEAR(result.z, -0.3033029415185209, 1e-6);   
}

TEST_F(TransformTest, LookAtTest) {
    // Test LookAt transformation
    vec3d pos(1, 0, 0);
    vec3d look(0, 1, 0);
    vec3d up(0, 0, 1);
    Transform lookAt = Transform::LookAt(pos, look, up);
    vec3d v(0, 0, -1);
    vec3d result = lookAt(v);

    // Check if LookAt transformation is applied correctly
    EXPECT_NEAR(result.x, 0.0, 1e-6);
    EXPECT_NEAR(result.y, 0.0, 1e-6);
    EXPECT_NEAR(result.z, -1.0, 1e-6);
}
