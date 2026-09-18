#pragma once
#include <WP_Vec.h>
#include <math.h>
#include <array>

template <typename Derived, typename T, size_t Elements>
template <typename... Args>
WP_VecBase<Derived, T, Elements>::WP_VecBase(Args... _values)
	requires (sizeof...(Args) <= Elements)
{
	std::array<T, sizeof...(Args)> currentValues{
			static_cast<T>(_values)...
	};

	for (int i = 0; i < sizeof...(Args); ++i)
	{
		(*this)[i] = currentValues[i];
	}
}

template <typename Derived, typename T, size_t Elements>
T& WP_VecBase<Derived, T, Elements>::operator[](size_t _index)
{
	return this->p_data[_index];
}

template <typename Derived, typename T, size_t Elements>
const T& WP_VecBase<Derived,T, Elements>::operator[](size_t _index) const
{
	return this->p_data[_index];
}

template <typename Derived, typename T, size_t Elements>
Derived& WP_VecBase<Derived,T, Elements>::operator+=(const Derived& _other)
{
	for (int i = 0; i < Elements;++i) {
		(*this)[i] += _other[i];
	}
	return static_cast<Derived&>(*this);;
}

template <typename Derived, typename T, size_t Elements>
Derived WP_VecBase<Derived,T,Elements>::operator+(const Derived& _other) const
{
	Derived returnValue = static_cast<const Derived&>(*this);
	returnValue += _other;
	return returnValue;
}

template <typename Derived,typename T, size_t Elements>
Derived& WP_VecBase<Derived, T, Elements>::operator-= (const Derived& _other)
{
	for (int i = 0; i < Elements;++i) {
		(*this)[i] -= _other[i];
	}
	return static_cast<Derived&>(*this);;
}
template <typename Derived, typename T, size_t Elements>
Derived WP_VecBase<Derived, T, Elements>::operator-(const Derived& _other) const
{
	Derived returnValue = static_cast<const Derived&>(*this);
	returnValue -= _other;
	return returnValue;
}

template <typename Derived, typename T, size_t Elements>
template <typename Scalar>
Derived& WP_VecBase<Derived, T, Elements>::operator/=(const Scalar& _other)
{
	for (int i = 0; i < Elements;++i) {
		(*this)[i] /= _other;
	}
	return static_cast<Derived&>(*this);
}
template <typename Derived, typename T, size_t Elements>
template <typename Scalar>
Derived WP_VecBase<Derived, T, Elements>::operator/(const Scalar& _other) const
{
	Derived returnValue = static_cast<const Derived&>(*this);
	returnValue /= _other;
	return returnValue;
}
template <typename Derived, typename T, size_t Elements>
template <typename Scalar>
Derived& WP_VecBase<Derived, T, Elements>::operator*=(const Scalar& _other)
{
	for (int i = 0; i < Elements;++i) {
		(*this)[i] *= _other;
	}
	return static_cast<Derived&>(*this);
}
template <typename Derived, typename T, size_t Elements>
template <typename Scalar>
Derived WP_VecBase<Derived, T, Elements>::operator*(const Scalar& _other) const
{
	Derived returnValue = static_cast<const Derived&>(*this);
	returnValue *= _other;
	return returnValue;
}
template <typename Derived, typename T, size_t Elements>
bool WP_VecBase<Derived, T, Elements>::operator==(const Derived& _other) const
{
	for (int i = 0; i < Elements;++i) {
		if ((*this)[i] != _other[i])
			return false;
	}
	return true;
}
template <typename Derived, typename T, size_t Elements>
bool WP_VecBase<Derived, T, Elements>::operator!=(const Derived&_other) const
{
	return !(*this ==_other);
}

template <typename Derived, typename T, size_t Elements>
T WP_VecBase<Derived, T, Elements>::SqDistance(const Derived& _other) const
{
	T totalValue = T(0);
	for (int i = 0; i < Elements;++i)
	{
		T difference = _other.data[i] - this->data[i];
		totalValue += difference * difference;
	}
	return totalValue;
}

template <typename Derived, typename T, size_t Elements>
T WP_VecBase<Derived, T, Elements>::Distance(const Derived& _other) const
	requires std::floating_point<T>
{
	return std::sqrt(this->SqDistance(_other));
}

template <typename Derived, typename T, size_t Elements>
T WP_VecBase<Derived, T, Elements>::DotProd(const Derived& _other) const
{
	T result = T(0);
	for (size_t i = 0; i < Elements; ++i)
	{
		result += (*this)[i] * _other[i];
	}
	return result;
}

template <typename Derived, typename T, size_t Elements>
T WP_VecBase<Derived, T, Elements>::SqMagnitude() const
{
	T totalValue = T(0);
	for (int i = 0; i < Elements;++i)
	{
		totalValue += (*this)[i] * (*this)[i];
	}
	return totalValue;
}
template <typename Derived, typename T, size_t Elements>
T WP_VecBase<Derived, T, Elements>::Magnitude() const
	requires std::floating_point<T>
{
	return std::sqrt(this->SqMagnitude());
}

template <typename Derived, typename T, size_t Elements>
Derived WP_VecBase<Derived, T, Elements>::GetNormalized() const
	requires std::floating_point<T>
{
	T magnitude = this->SqMagnitude();
	Derived returnValue = static_cast<const Derived&>(*this);

	//divide by 0 case
	if (magnitude == T(0))
	{
		return Derived();
	}

	returnValue /= this->Magnitude();
	return returnValue;
}

template <typename Derived, typename T, size_t Elements>
Derived WP_VecBase<Derived, T, Elements>::Project(const Derived& _other) const
{
	T magnitude = _other.SqMagnitude();

	//divide by 0 case
	if (magnitude == T(0))
	{
		return Derived();
	}

	return _other * (DotProd(_other) / magnitude);
}

template <typename T>
T WP_Vec<T,2>::CrossProd(const WP_Vec<T, 2>& _other) const
{
	return this->x * _other.y - this->y * _other.x;
}

template <typename T>
WP_Vec<T, 2> WP_Vec<T, 2>::Normal() const
{
	return WP_Vec<T, 2>(-this->y, this->x);
}

template <typename T>
WP_Vec<T, 2>& WP_Vec<T, 2>::Rotate(double _radians)
	requires std::floating_point<T>
{
	*this = GetRotatedOrigin(_radians);
	return *this;
}

template <typename T>
WP_Vec<T, 2> WP_Vec<T, 2>::GetRotatedOrigin(double _radians) const
	requires std::floating_point<T>
{
	return WP_Vec<T, 2>(this->x * cos(_radians) - this->y * sin(_radians),
		this->x * sin(_radians) + this->y * cos(_radians));
}

template <typename T>
double WP_Vec<T, 2>::Angle() const
{
	return atan2(this->y, this->x);
}

template <typename T>
double WP_Vec<T, 2>::Angle(const WP_Vec<T,2>& _other) const
{
	return atan2(CrossProd(_other), this->DotProd(_other));
}
template <typename T>
WP_Vec<T, 3> WP_Vec<T, 3>::CrossProd(const WP_Vec<T, 3>& _other) const
{
	WP_Vec<T, 3> result;
	result. x = this->y * _other. z - this->z * _other.y;
	result. y = this->z * _other. x - this->x * _other.z;
	result. z = this->x * _other. y - this->y * _other.x;
	return result;
}


template <typename T>
WP_Vec<T, 3>& WP_Vec<T, 3>::Rotate(
	const WP_Vec<T, 3>& axis,
	double radians
)
	requires std::floating_point<T>
{
	*this = GetRotatedOrigin(axis, radians);
	return *this;
}

//Rodrigues' rotation formula
//Vrot = Vcos(theta) + Cross(kv)sin(theta) + k * dot(kv)(1-cos(theta))
//where k is a unit vector
template <typename T>
WP_Vec<T, 3> WP_Vec<T, 3>::GetRotatedOrigin(
	const WP_Vec<T, 3>& axis,
	double radians) const
	requires std::floating_point<T>
{
	WP_Vec<T, 3> normalisedAxis = axis.GetNormalized();
	T cosAngle = static_cast<T>(std::cos(radians));
	T sinAngle = static_cast<T>(std::sin(radians));
	WP_Vec<T, 3> resultingRotate =
		(*this * cosAngle) +
		normalisedAxis.CrossProd(*this) +
		normalisedAxis * (normalisedAxis.DotProd(*this) * (1 - cosAngle));
	return resultingRotate;
}