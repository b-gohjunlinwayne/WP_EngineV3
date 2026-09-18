#pragma once
#include <iostream>
#include <WP_Vec.hpp>
#include <assert.h>
#include <WP_Logger.h>

/*
    Quick and dirty math validation
    generated from ai
*/
namespace WP_Validation
{
    // Helper for floating-point comparisons
    template <typename T>
    bool Near(T a, T b, T eps = static_cast<T>(1e-5))
    {
        return std::abs(a - b) <= eps;
    }

    // Validation for WP_Vec2 specific features
    inline void ValidateVec2()
    {
        WP_Logger() << "[Validation] Testing WP_Vec2...\n";

        WP_Vec2f v1(3.0f, 4.0f);
        WP_Vec2f v2(1.0f, 2.0f);

        // Test Magnitude & SqMagnitude
        assert(Near(v1.SqMagnitude(), 25.0f));
        assert(Near(v1.Magnitude(), 5.0f));

        // Test Dot Product
        // 3*1 + 4*2 = 3 + 8 = 11
        assert(Near(v1.DotProd(v2), 11.0f));

        // Test Cross Product (2D determinant)
        // 3*2 - 4*1 = 6 - 4 = 2
        assert(Near(v1.CrossProd(v2), 2.0f));

        // Test Normal / Perpendicular vector
        WP_Vec2f norm = v1.Normal();
        assert(Near(v1.DotProd(norm), 0.0f));

        // Test Normalization
        WP_Vec2f unitV1 = v1.GetNormalized();
        assert(Near(unitV1.Magnitude(), 1.0f));

        // Test Rotation (90 degrees / pi/2 radians)
        WP_Vec2f rot = v1.GetRotatedOrigin(3.14159265358979323846 / 2.0);
        assert(Near(rot.x, -4.0f));
        WP_Logger() << rot.y;
        assert(Near(rot.y, 3.0f));

        // Test Angle
        WP_Vec2f xAxis(1.0f, 0.0f);
        WP_Vec2f yAxis(0.0f, 1.0f);
        assert(Near(static_cast<float>(xAxis.Angle(yAxis)), static_cast<float>(3.14159265358979323846 / 2.0)));

        WP_Logger() << "[Validation] WP_Vec2 passed successfully!\n";
    }

    // Validation for WP_Vec3 specific features
    inline void ValidateVec3()
    {
        WP_Logger() << "[Validation] Testing WP_Vec3...\n";

        WP_Vec3f v1(1.0f, 0.0f, 0.0f);
        WP_Vec3f v2(0.0f, 1.0f, 0.0f);

        // Test Cross Product (X cross Y = Z)
        WP_Vec3f cross = v1.CrossProd(v2);
        assert(Near(cross.x, 0.0f));
        assert(Near(cross.y, 0.0f));
        assert(Near(cross.z, 1.0f));

        // Test Dot Product & Projections
        WP_Vec3f v3(3.0f, 4.0f, 0.0f);
        assert(Near(v3.Magnitude(), 5.0f));

        WP_Vec3f projAxis(1.0f, 0.0f, 0.0f);
        WP_Vec3f projected = v3.Project(projAxis);
        assert(Near(projected.x, 3.0f));
        assert(Near(projected.y, 0.0f));
        assert(Near(projected.z, 0.0f));

        // Test Rotation around Z axis (90 degrees)
        WP_Vec3f zAxis(0.0f, 0.0f, 1.0f);
        WP_Vec3f point(1.0f, 0.0f, 0.0f);
        WP_Vec3f rotPoint = point.GetRotatedOrigin(zAxis, 3.14159265358979323846 / 2.0);
        assert(Near(rotPoint.x, 0.0f));
        assert(Near(rotPoint.y, 1.0f));
        assert(Near(rotPoint.z, 0.0f));

        WP_Logger() << "[Validation] WP_Vec3 passed successfully!\n";
    }

    // Validation for general arithmetic operators across sizes
    inline void ValidateBaseOperations()
    {
        WP_Logger() << "[Validation] Testing General Vector Arithmetic...\n";

        WP_Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
        WP_Vec4f v2(5.0f, 6.0f, 7.0f, 8.0f);

        // Addition
        WP_Vec4f vAdd = v1 + v2;
        assert(Near(vAdd[0], 6.0f));
        assert(Near(vAdd[1], 8.0f));
        assert(Near(vAdd[2], 10.0f));
        assert(Near(vAdd[3], 12.0f));

        // Subtraction
        WP_Vec4f vSub = v2 - v1;
        assert(Near(vSub[0], 4.0f));
        assert(Near(vSub[1], 4.0f));
        assert(Near(vSub[2], 4.0f));
        assert(Near(vSub[3], 4.0f));

        // Scalar Multiplication
        WP_Vec4f vMul = v1 * 2.0f;
        assert(Near(vMul[0], 2.0f));
        assert(Near(vMul[3], 8.0f));

        // Equality operators
        WP_Vec4f v1Copy(1.0f, 2.0f, 3.0f, 4.0f);
        assert(v1 == v1Copy);
        assert(v1 != v2);

        // Anonymous union validation (checking x,y,z,w mapping to r,g,b,a on Vec3/Vec4)
        WP_Vec3f color(0.1f, 0.2f, 0.3f);
        assert(Near(color.x, color.r));
        assert(Near(color.y, color.g));
        assert(Near(color.z, color.b));

        WP_Logger() << "[Validation] General Vector Arithmetic passed successfully!\n";
    }

    template <typename T>
    bool MatNear(T a, T b, T eps = static_cast<T>(1e-4))
    {
        return std::abs(a - b) <= eps;
    }

    // Validation for Matrix Transpose
    inline void ValidateMatrixTranspose()
    {
        WP_Logger() << "[Validation] Testing WP_Mat Transpose...\n";

        // 1. Test Square Matrix Transpose (3x3)
        WP_Mat<float, 3, 3> m3x3;
        float val = 1.0f;
        for (size_t r = 0; r < 3; ++r) {
            for (size_t c = 0; c < 3; ++c) {
                m3x3(r, c) = val++;
            }
        }
        // m3x3 looks like:
        // [[1, 2, 3],
        //  [4, 5, 6],
        //  [7, 8, 9]]

        WP_Mat<float, 3, 3> transposed3x3 = m3x3.Transposed();

        for (size_t r = 0; r < 3; ++r) {
            for (size_t c = 0; c < 3; ++c) {
                assert(MatNear(transposed3x3(r, c), m3x3(c, r)));
            }
        }

        // 2. Test Rectangular Matrix Transpose (e.g., 2x3 matrix -> Transpose should be 3x2)
        WP_Mat<float, 2, 3> m2x3;
        m2x3(0, 0) = 1.0f; m2x3(0, 1) = 2.0f; m2x3(0, 2) = 3.0f;
        m2x3(1, 0) = 4.0f; m2x3(1, 1) = 5.0f; m2x3(1, 2) = 6.0f;
        // m2x3 looks like:
        // [[1, 2, 3],
        //  [4, 5, 6]]

        WP_Mat<float, 3, 2> transposed2x3 = m2x3.Transposed();
        // Expected transposed 3x2:
        // [[1, 4],
        //  [2, 5],
        //  [3, 6]]

        assert(MatNear(transposed2x3(0, 0), 1.0f));
        assert(MatNear(transposed2x3(0, 1), 4.0f));
        assert(MatNear(transposed2x3(1, 0), 2.0f));
        assert(MatNear(transposed2x3(1, 1), 5.0f));
        assert(MatNear(transposed2x3(2, 0), 3.0f));
        assert(MatNear(transposed2x3(2, 1), 6.0f));

        // 3. Test Double Transpose Property: (A^T)^T == A
        WP_Mat<float, 2, 3> doubleTransposed = transposed2x3.Transposed();
        for (size_t r = 0; r < 2; ++r) {
            for (size_t c = 0; c < 3; ++c) {
                assert(MatNear(doubleTransposed(r, c), m2x3(r, c)));
            }
        }

        WP_Logger() << "[Validation] WP_Mat Transpose Tests Passed Successfully!\n";
    }

    inline void ValidateMatrixLibrary()
    {
        WP_Logger() << "[Validation] Testing WP_Mat structural and arithmetic features...\n";

        // 1. Test Identity and Basic Element Access
        using Mat3f = WP_Mat<float, 3, 3>;
        Mat3f identity = Mat3f::Identity();

        for (size_t r = 0; r < 3; ++r)
        {
            for (size_t c = 0; c < 3; ++c)
            {
                if (r == c)
                    assert(MatNear(identity(r, c), 1.0f));
                else
                    assert(MatNear(identity(r, c), 0.0f));
            }
        }

        // 2. Test Translation 2D (3x3 matrix for 2D points)
        // For a 3x3 matrix, Translate takes Rows - 1 arguments (2 arguments: dx, dy)
        Mat3f trans2D = Mat3f::Translate(5.0f, -2.0f);
        WP_Vec2f p2D(1.0f, 1.0f);
        WP_Vec2f translatedP2D = trans2D.TransformPoint(p2D);
        assert(MatNear(translatedP2D.x, 6.0f));
        assert(MatNear(translatedP2D.y, -1.0f));

        // 3. Test Scale (Uniform and Non-Uniform)
        Mat3f scaleUnif = Mat3f::Scale(2.0f);
        assert(MatNear(scaleUnif(0, 0), 2.0f));
        assert(MatNear(scaleUnif(1, 1), 2.0f));
        assert(MatNear(scaleUnif(2, 2), 2.0f)); // Homogeneous scale factor if applicable, or check structure

        Mat3f scaleNonUnif = Mat3f::Scale(3.0f, 4.0f);
        assert(MatNear(scaleNonUnif(0, 0), 3.0f));
        assert(MatNear(scaleNonUnif(1, 1), 4.0f));

        // 4. Test 2D Rotation (9 = pi/2 radians)
        float halfPi = static_cast<float>(3.14159265358979323846 / 2.0);
        Mat3f rot2D = Mat3f::Rotation2D(halfPi);
        WP_Vec2f unitX(1.0f, 0.0f);
        WP_Vec2f rotatedX = rot2D.TransformPoint(unitX);
        // Rotating (1,0) by 90 degrees should yield roughly (0, 1)
        assert(MatNear(rotatedX.x, 0.0f));
        assert(MatNear(rotatedX.y, 1.0f));

        // 5. Test Matrix Addition and Subtraction
        Mat3f m1;
        Mat3f m2;
        for (size_t r = 0; r < 3; ++r) {
            for (size_t c = 0; c < 3; ++c) {
                m1(r, c) = static_cast<float>(r + c + 1);
                m2(r, c) = static_cast<float>(2);
            }
        }

        Mat3f mAdd = m1 + m2;
        assert(MatNear(mAdd(0, 0), 3.0f));
        assert(MatNear(mAdd(2, 2), 7.0f));

        Mat3f mSub = m1 - m2;
        assert(MatNear(mSub(0, 0), -1.0f));

        // 6. Test Scalar Multiplication and Division
        Mat3f mScalar = m1 * 2.0f;
        assert(MatNear(mScalar(0, 0), 2.0f));
        assert(MatNear(mScalar(0, 1), 4.0f));

        Mat3f mDiv = mScalar / 2.0f;
        assert(MatNear(mDiv(0, 0), 1.0f));
        assert(MatNear(mDiv(0, 1), 2.0f));

        // 7. Test Matrix Multiplication (Chain combination)
        // Identity * m1 should equal m1
        Mat3f mProduct = identity * m1;
        for (size_t r = 0; r < 3; ++r) {
            for (size_t c = 0; c < 3; ++c) {
                assert(MatNear(mProduct(r, c), m1(r, c)));
            }
        }

        ValidateMatrixTranspose();

        WP_Logger() << "[Validation] All WP_Mat Tests Passed Successfully!\n";
    }

    // Master function to execute all validation suites
    inline void RunAllValidations()
    {
        WP_Logger() << "========================================\n";
        WP_Logger() << "Starting WP_Vec Library Validation...\n";
        WP_Logger() << "========================================\n";

        ValidateBaseOperations();
        ValidateVec2();
        ValidateVec3();

        WP_Logger() << "========================================\n";
        WP_Logger() << "All Vector Validations Passed Successfully!\n";
        WP_Logger() << "========================================\n";

        ValidateMatrixLibrary();
    }


}