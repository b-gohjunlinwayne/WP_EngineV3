#pragma once

#include <WP_Vec.hpp>

template <typename T , size_t Rows, size_t Cols >
struct WP_Mat
{
    T p_data[Rows][Cols]{};

    static WP_Mat Identity()
        requires (Rows == Cols);
    template <typename... Args>
    static WP_Mat<T, Rows, Cols> Translate(Args... _values)
        requires (Rows == Cols && sizeof...(Args) == Rows - 1);

    static WP_Mat Scale(T _value)
        requires (Rows == Cols);
    template <typename... Args>
    static WP_Mat Scale(Args... _values)
        requires (Rows == Cols && sizeof...(Args) == Rows - 1);

    static WP_Mat Rotation2D(T _radians)
        requires (Rows == 3 && Cols == 3);
    static WP_Mat Rotation3DX(T _radians)
        requires (Rows == 4 && Cols == 4);
    static WP_Mat Rotation3DY(T _radians)
        requires (Rows == 4 && Cols == 4);
    static WP_Mat Rotation3DZ(T _radians)
        requires (Rows == 4 && Cols == 4);

    static WP_Mat Translate(const WP_Vec<T, Rows - 1> _translate)
        requires (Rows == Cols);


	T& operator()(size_t _row, size_t _col);
	const T& operator()(size_t _row, size_t _col) const;

    //compiler optimise loops so we use default instead of writing own
    WP_Mat& operator=(const WP_Mat& _other) = default;

    // Matrix operations
    WP_Mat operator+(const WP_Mat& _other) const;
    WP_Mat& operator+=(const WP_Mat& _other);
    WP_Mat operator-(const WP_Mat& _other) const;
    WP_Mat& operator-=(const WP_Mat& _other);
    template <size_t OtherCols>
    WP_Mat<T, Rows, OtherCols> operator*(const WP_Mat<T, Cols, OtherCols>& _other) const;
    WP_Mat& operator*=(const WP_Mat<T, Cols, Cols>& _other);

    //Affine Transformation
    WP_Vec<T, Rows> operator*(const WP_Vec <T, Rows>& _other) const;
    WP_Vec<T, 2> TransformPoint(const WP_Vec<T, 2>& _points) const
        requires (Rows == 3 && Cols == 3);
    WP_Vec<T, 3> TransformPoint(const WP_Vec<T, 3>& _points) const
        requires (Rows == 4 && Cols == 4);

    //Scalar
    WP_Mat operator*(T _scalar) const;
    WP_Mat& operator*=(T _scalar);
    WP_Mat operator/(T _scalar) const;
    WP_Mat& operator/=(T _scalar);

    WP_Mat<T, Cols, Rows> Transposed() const;
};


using WP_Mat2x2f = WP_Mat<float, 2, 2>;
using WP_Mat3x3f = WP_Mat<float, 3, 3>;
using WP_Mat4x4f = WP_Mat<float, 4, 4>;