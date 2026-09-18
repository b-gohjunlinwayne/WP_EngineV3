#pragma once

#include <WP_Vec.hpp>

template <typename T , size_t Rows, size_t Cols >
struct WP_Mat
{
    T data[Rows][Cols]{};

    static WP_Mat Identity()
        requires (Rows == Cols);
    template <typename... Args>
    static WP_Mat<T, Rows, Cols> Translate(Args... values)
        requires (Rows == Cols && sizeof...(Args) == Rows - 1);

    static WP_Mat Scale(T value)
        requires (Rows == Cols);
    template <typename... Args>
    static WP_Mat Scale(Args... values)
        requires (Rows == Cols && sizeof...(Args) == Rows - 1);

    static WP_Mat Rotation2D(T radians)
        requires (Rows == 3 && Cols == 3);
    static WP_Mat Rotation3DX(T radians)
        requires (Rows == 4 && Cols == 4);
    static WP_Mat Rotation3DY(T radians)
        requires (Rows == 4 && Cols == 4);
    static WP_Mat Rotation3DZ(T radians)
        requires (Rows == 4 && Cols == 4);

    static WP_Mat Translate(const WP_Vec<T, Rows - 1> translate)
        requires (Rows == Cols);


	T& operator()(size_t row, size_t col);
	const T& operator()(size_t row, size_t col) const;

    //compiler optimise loops so we use default instead of writing own
    WP_Mat& operator=(const WP_Mat& other) = default;

    // Matrix operations
    WP_Mat operator+(const WP_Mat& other) const;
    WP_Mat& operator+=(const WP_Mat& other);
    WP_Mat operator-(const WP_Mat& other) const;
    WP_Mat& operator-=(const WP_Mat& other);
    template <size_t OtherCols>
    WP_Mat<T, Rows, OtherCols> operator*(const WP_Mat<T, Cols, OtherCols>& other) const;
    WP_Mat& operator*=(const WP_Mat<T, Cols, Cols>& other);

    //Affine Transformation
    WP_Vec<T, Rows> operator*(const WP_Vec <T, Rows>& other) const;
    WP_Vec<T, 2> TransformPoint(const WP_Vec<T, 2>& points) const
        requires (Rows == 3 && Cols == 3);
    WP_Vec<T, 3> TransformPoint(const WP_Vec<T, 3>& points) const
        requires (Rows == 4 && Cols == 4);

    //Scalar
    WP_Mat operator*(T scalar) const;
    WP_Mat& operator*=(T scalar);
    WP_Mat operator/(T scalar) const;
    WP_Mat& operator/=(T scalar);

    WP_Mat<T, Cols, Rows> Transposed() const;
};


using WP_Mat2x2f = WP_Mat<float, 2, 2>;
using WP_Mat3x3f = WP_Mat<float, 3, 3>;
using WP_Mat4x4f = WP_Mat<float, 4, 4>;