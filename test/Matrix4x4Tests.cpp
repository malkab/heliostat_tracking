#include "Matrix4x4.h"
#include "gtest/gtest.h"

TEST(Matrix4x4Test, DefaultConstructorIdentityMatrix) {
    Matrix4x4 matrix;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (i == j)
                EXPECT_EQ(matrix.m[i][j], 1.0);
            else
                EXPECT_EQ(matrix.m[i][j], 0.0);
}

TEST(Matrix4x4Test, ArrayConstructor) {
    double data[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    Matrix4x4 matrix(data);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            EXPECT_EQ(matrix.m[i][j], data[i][j]);
}

TEST(Matrix4x4Test, CopyConstructor) {
    double data[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    Matrix4x4 matrix1(data);
    Matrix4x4 matrix2(matrix1);
    EXPECT_EQ(matrix1, matrix2);
}

TEST(Matrix4x4Test, EqualityOperator) {
    double data[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    Matrix4x4 matrix1(data);
    Matrix4x4 matrix2(data);
    EXPECT_EQ(matrix1, matrix2);
    
    matrix2.m[0][0] = 17;
    EXPECT_NE(matrix1, matrix2);
}

TEST(Matrix4x4Test, Transposed) {
    double data[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    Matrix4x4 matrix(data);
    auto transposed = matrix.transposed();
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            EXPECT_EQ(transposed->m[i][j], matrix.m[j][i]);
}
 
TEST(Matrix4x4Test, TestTranspose) {
    Matrix4x4 mat(1.0, 2.0, 3.0, 4.0,
                  5.0, 6.0, 7.0, 8.0,
                  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0);
    
    auto transposedMat = mat.transposed();
    Matrix4x4 expected(1.0, 5.0, 9.0, 13.0,
                       2.0, 6.0, 10.0, 14.0,
                       3.0, 7.0, 11.0, 15.0,
                       4.0, 8.0, 12.0, 16.0);
    
    ASSERT_TRUE(*transposedMat == expected);
}

TEST(Matrix4x4Test, TestDeterminant) {
    // Using a known matrix and its determinant for verification
    Matrix4x4 mat1(5.0, -2.0, 2.0, 7.0,
                  1.0, 0.0, 0.0, 3.0,
                  -3.0, 2.0, 5.0, 1.0,
                  3.0, -2.0, -9.0, 6.0);

    double det1 = mat1.determinant();
    double expectedDet1 = 114.0;
    
    ASSERT_NEAR(det1, expectedDet1, 1e-5);

    // Using a known matrix and its determinant for verification
    Matrix4x4 mat2(20, -250.0, 30.0, -4.0,
                  22.0, -12.0, 18.6, 2.0,
                  56.0, -2.0, 14.0, 12.0,
                  2.17, 23.8, -78.2, 7.8);

    double det2 = mat2.determinant();
    double expectedDet2 = 1402101.376;
    
    ASSERT_NEAR(det2, expectedDet2, 1e-5);    
}

TEST(Matrix4x4Test, MultiplyFunction) {
    Matrix4x4 mat1{
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

    Matrix4x4 mat2{
        16.0f, 15.0f, 14.0f, 13.0f,
        12.0f, 11.0f, 10.0f, 9.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    };

    std::shared_ptr<Matrix4x4> result = multiply(mat1, mat2);

    Matrix4x4 expected{
        80.0f, 70.0f, 60.0f, 50.0f,
        240.0f, 214.0f, 188.0f, 162.0f,
        400.0f, 358.0f, 316.0f, 274.0f,
        560.0f, 502.0f, 444.0f, 386.0f
    };

    for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                EXPECT_EQ(result->m[i][j], expected.m[i][j]);
}

TEST(Matrix4x4Test, TestOutputStream) {
    Matrix4x4 mat(1.0, 2.0, 3.0, 4.0,
                  5.0, 6.0, 7.0, 8.0,
                  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0);
    
    std::stringstream ss;
    ss << mat;

    std::string expected = "[ 1, 2, 3, 4 ] \n[ 5, 6, 7, 8 ] \n[ 9, 10, 11, 12 ] \n[ 13, 14, 15, 16 ] \n";
    ASSERT_EQ(ss.str(), expected);
}

