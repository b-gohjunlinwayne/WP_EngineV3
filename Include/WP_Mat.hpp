#pragma once
#include <WP_Mat.h>
#include <math.h>

template <typename T, size_t Rows, size_t Cols >
WP_Mat<T,Rows,Cols> WP_Mat<T, Rows, Cols>::Identity()
	requires (Rows == Cols)
{
	WP_Mat<T,Rows,Cols> identityMatrix;
	for (int i = 0; i < Rows; ++i)
	{
		identityMatrix(i, i) = 1;
	}
	return identityMatrix;
}
template <typename T, size_t Rows, size_t Cols>
template <typename... Args>
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::Translate(Args... _values)
	requires (Rows == Cols && sizeof...(Args) == Rows - 1)
{
	WP_Mat<T,Rows, Cols> matrix = WP_Mat<T, Rows, Cols>::Identity();
	T translation[] = { static_cast<T>(_values)... };

	for (int i = 0; i < Rows - 1; ++i)
	{
		matrix(i, Rows - 1) = translation[i];
	}

	return matrix;
}

template <typename T, size_t Rows, size_t Cols >
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::Rotation2D(T _radians)
	requires (Rows == 3 && Cols == 3)
{
	WP_Mat<T,3,3> rotationMatrix;

	T cosine = cos(_radians);
	T sine = sin(_radians);

	rotationMatrix(0, 0) = cosine;
	rotationMatrix(0, 1) = -sine;
	rotationMatrix(1, 1) = cosine;
	rotationMatrix(1, 0) = sine;
	rotationMatrix(2, 2) = 1;

	return rotationMatrix;
}

template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::Rotation3DX(T _radians)
	requires (Rows == 4 && Cols == 4)
{
	WP_Mat<T, 4, 4> mat = Identity();
	T c = std::cos(_radians);
	T s = std::sin(_radians);

	mat(1, 1) = c;
	mat(1, 2) = -s;
	mat(2, 1) = s;
	mat(2, 2) = c;

	return mat;
}

template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::Rotation3DY(T _radians)
	requires (Rows == 4 && Cols == 4)
{
	WP_Mat<T, 4, 4> mat = Identity();
	T c = std::cos(_radians);
	T s = std::sin(_radians);

	mat(0, 0) = c;
	mat(0, 2) = s;
	mat(2, 0) = -s;
	mat(2, 2) = c;

	return mat;
}

template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::Rotation3DZ(T _radians)
	requires (Rows == 4 && Cols == 4)
{
	WP_Mat<T, 4, 4> mat = Identity();
	T c = std::cos(_radians);
	T s = std::sin(_radians);

	mat(0, 0) = c;
	mat(0, 1) = -s;
	mat(1, 0) = s;
	mat(1, 1) = c;

	return mat;
}

template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::Translate(const WP_Vec<T, Rows - 1> _translate)
	requires (Rows == Cols)
{
	WP_Mat<T, Rows, Cols> mat = Identity();
	for (size_t i = 0; i < Rows - 1; ++i)
	{
		mat(i, Rows - 1) = _translate[i];
	}
	return mat;
}

template <typename T,size_t Rows, size_t Cols>
WP_Mat<T,Rows,Cols> WP_Mat<T,Rows,Cols>::Scale(T _value)
	requires (Rows == Cols)
{
	WP_Mat<T, Rows, Cols> scaleMatrix = WP_Mat<T,Rows,Cols>::Identity();
	for (int i = 0; i < Rows; ++i)
	{
		scaleMatrix(i, i) = _value;
	}
	return scaleMatrix;
}

template <typename T, size_t Rows, size_t Cols>
template <typename... Args>
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::Scale(Args... _values)
	requires (Rows == Cols && sizeof...(Args) == Rows - 1)
{
	WP_Mat<T, Rows, Cols> scaleMatrix = WP_Mat<T, Rows, Cols>::Identity();
	T scale[] = { static_cast<T>(_values)... };
	for (int i = 0; i < Rows; ++i)
	{
		scaleMatrix(i, i) = scale[i];
	}
	return scaleMatrix;
}


template <typename T, size_t Rows, size_t Cols >
T& WP_Mat<T, Rows, Cols>::operator()(size_t _row, size_t _col)
{
	return p_data[_row][_col];
}

template <typename T, size_t Rows, size_t Cols >
const T& WP_Mat<T, Rows, Cols>::operator()(size_t _row, size_t _col) const
{
	return p_data[_row][_col];
}

template <typename T, size_t Rows, size_t Cols >
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::operator+(const WP_Mat<T, Rows,Cols>&_other) const
{
	WP_Mat<T, Rows, Cols> returnValue = *this;
	returnValue +=_other;
	return returnValue;
}
template <typename T, size_t Rows, size_t Cols >
WP_Mat<T, Rows, Cols>& WP_Mat<T, Rows, Cols>::operator+=(const WP_Mat<T, Rows, Cols>& _other)
{
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t x = 0; x < Cols;++x)
		{
			(*this)(i, x) +=_other(i, x);
		}
	}
	return *this;
}

template <typename T, size_t Rows, size_t Cols >
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::operator-(const WP_Mat<T, Rows, Cols>& _other) const
{
	WP_Mat<T, Rows, Cols> returnValue = *this;
	returnValue -=_other;
	return returnValue;
}

template <typename T, size_t Rows, size_t Cols >
WP_Mat<T, Rows, Cols>& WP_Mat<T, Rows, Cols>::operator-=(const WP_Mat<T, Rows, Cols>& _other)
{
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t x = 0; x < Cols;++x)
		{
			(*this)(i, x) -=_other(i, x);
		}
	}
	return *this;
}

template <typename T, size_t Rows, size_t Cols>
template <size_t OtherCols>
WP_Mat<T, Rows, OtherCols> WP_Mat<T, Rows, Cols>::operator*(const WP_Mat<T, Cols, OtherCols>& _other) const
{
	WP_Mat<T, Rows, OtherCols> product;
	for (size_t row = 0; row < Rows; ++row)
	{
		for (size_t col = 0; col < OtherCols; ++col)
		{
			for (size_t i = 0; i < Cols; ++i)
			{
				T val = (*this)(row, i);
				T _otherVal =_other(i, col);
				product(row, col) += val *_otherVal;
			}
		}
	}
	return product;
}

template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols>& WP_Mat<T, Rows, Cols>::operator*=(const WP_Mat<T, Cols, Cols>& _other) 
{
	WP_Mat<T, Rows, Cols> copy = *this;
	*this = copy *_other;
	return *this;
}

template <typename T, size_t Rows, size_t Cols>
WP_Vec<T, Rows> WP_Mat<T, Rows, Cols>::operator*(const WP_Vec <T, Rows>& _other) const
{
	WP_Vec<T, Rows> resultingVec;
	for (size_t row = 0; row < Rows; ++row)
	{
		T resultingData = T(0);
		for (size_t col = 0; col < Cols;++col)
		{
			resultingData +=
				(*this)(row, col) *_other.p_data[col];
		}
		resultingVec.p_data[row] = resultingData;
	}
	return resultingVec;
}

template <typename T, size_t Rows, size_t Cols>
WP_Vec<T, 2> WP_Mat<T, Rows, Cols>::TransformPoint(const WP_Vec<T, 2>& _points) const
	requires (Rows == 3 && Cols == 3)
{
	T x = (*this)(0, 0) * _points.x + (*this)(0, 1) * _points.y + (*this)(0, 2);
	T y = (*this)(1, 0) * _points.x + (*this)(1, 1) * _points.y + (*this)(1, 2);
	T z = (*this)(2, 0) * _points.x + (*this)(2, 1) * _points.y + (*this)(2, 2);

	WP_Vec<T, 2> returnValue = WP_Vec<T, 2>(x, y);
	returnValue /= z;
	return returnValue;
}
template <typename T, size_t Rows, size_t Cols>
WP_Vec<T, 3> WP_Mat<T, Rows, Cols>::TransformPoint(const WP_Vec<T, 3>& _points) const
	requires (Rows == 4 && Cols == 4)
{
	T x = (*this)(0, 0) * _points.x + (*this)(0, 1) * _points.y + (*this)(0, 2) * _points.z + (*this)(0,3);
	T y = (*this)(1, 0) * _points.x + (*this)(1, 1) * _points.y + (*this)(1, 2) * _points.z + (*this)(1,3);
	T z = (*this)(2, 0) * _points.x + (*this)(2, 1) * _points.y + (*this)(2, 2) * _points.z + (*this)(2,3);
	T w = (*this)(3, 0) * _points.x + (*this)(3, 1) * _points.y + (*this)(3, 2) * _points.z + (*this)(3,3);

	WP_Vec<T, 3> returnValue = WP_Vec<T, 3>(x, y,z);
	returnValue /= w;
	return returnValue;
}

template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::operator*(T _scalar) const
{
	WP_Mat<T, Rows, Cols> result;
	for (size_t row = 0; row < Rows; ++row)
	{
		for (size_t col = 0; col < Cols; ++col)
		{
			result(row, col) = (*this)(row, col) * _scalar;
		}
	}
	return result;
}
template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols>& WP_Mat<T, Rows, Cols>::operator*=(T _scalar)
{
	WP_Mat<T, Rows, Cols> copy = *this;
	*this = copy * _scalar;
	return *this;
}
template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols> WP_Mat<T, Rows, Cols>::operator/(T _scalar) const
{
	WP_Mat<T, Rows, Cols> result;
	for (size_t row = 0; row < Rows; ++row)
	{
		for (size_t col = 0; col < Cols; ++col)
		{
			result(row, col) = (*this)(row, col) / _scalar;
		}
	}
	return result;
}
template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Rows, Cols>& WP_Mat<T, Rows, Cols>::operator/=(T _scalar)
{
	WP_Mat<T, Rows, Cols> copy = *this;
	*this = copy / _scalar;
	return *this;
}

template <typename T, size_t Rows, size_t Cols>
WP_Mat<T, Cols, Rows> WP_Mat<T, Rows, Cols>::Transposed() const
{
	WP_Mat<T, Cols, Rows> result;
	for (size_t row = 0; row < Rows; ++row)
	{
		for (size_t col = 0; col < Cols; ++col)
		{
			result(col, row) = (*this)(row, col);
		}
	}
	return result;
}