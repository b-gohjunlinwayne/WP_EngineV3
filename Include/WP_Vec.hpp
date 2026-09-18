#pragma once
#include <WP_Vec.h>
#include <math.h>
#include <array>

template <typename Derived, typename T, size_t elements>
template <typename... Args>
WP_VecBase<Derived, T,elements>::WP_VecBase(Args... values)
	requires (sizeof...(Args) <= elements) 
{
	std::array<T, sizeof...(Args)> currentValues{
			static_cast<T>(values)...
	};

	for (int i = 0; i < sizeof...(Args); ++i)
	{
		(*this)[i] = currentValues[i];
	}
}

template <typename Derived, typename T, size_t elements>
T& WP_VecBase<Derived, T,elements>::operator[](size_t index)
{
	return this-> data[index];
}

template <typename Derived, typename T, size_t elements>
const T& WP_VecBase<Derived,T, elements>::operator[](size_t index) const
{
	return this-> data[index];
}

template <typename Derived, typename T, size_t elements>
Derived& WP_VecBase<Derived,T,elements>::operator+=(const Derived& other)
{
	for (int i = 0; i < elements;++i) {
		(*this)[i] += other[i];
	}
	return static_cast<Derived&>(*this);;
}

template <typename Derived, typename T, size_t elements>
Derived WP_VecBase<Derived,T,elements>::operator+(const Derived& other) const
{
	Derived returnValue = static_cast<const Derived&>(*this);
	returnValue += other;
	return returnValue;
}

template <typename Derived,typename T, size_t elements>
Derived& WP_VecBase<Derived, T, elements>::operator-= (const Derived& other)
{
	for (int i = 0; i < elements;++i) {
		(*this)[i] -= other[i];
	}
	return static_cast<Derived&>(*this);;
}
template <typename Derived, typename T, size_t elements>
Derived WP_VecBase<Derived, T, elements>::operator-(const Derived& other) const
{
	Derived returnValue = static_cast<const Derived&>(*this);
	returnValue -= other;
	return returnValue;
}

template <typename Derived, typename T, size_t elements>
template <typename Scalar>
Derived& WP_VecBase<Derived, T, elements>::operator/=(const Scalar& other)
{
	for (int i = 0; i < elements;++i) {
		(*this)[i] /= other;
	}
	return static_cast<Derived&>(*this);
}
template <typename Derived, typename T, size_t elements>
template <typename Scalar>
Derived WP_VecBase<Derived, T, elements>::operator/(const Scalar& other) const
{
	Derived returnValue = static_cast<const Derived&>(*this);
	returnValue /= other;
	return returnValue;
}
template <typename Derived, typename T, size_t elements>
template <typename Scalar>
Derived& WP_VecBase<Derived, T, elements>::operator*=(const Scalar& other)
{
	for (int i = 0; i < elements;++i) {
		(*this)[i] *= other;
	}
	return static_cast<Derived&>(*this);
}
template <typename Derived, typename T, size_t elements>
template <typename Scalar>
Derived WP_VecBase<Derived, T, elements>::operator*(const Scalar& other) const
{
	Derived returnValue = static_cast<const Derived&>(*this);
	returnValue *= other;
	return returnValue;
}
template <typename Derived, typename T, size_t elements>
bool WP_VecBase<Derived, T, elements>::operator==(const Derived& other) const
{
	for (int i = 0; i < elements;++i) {
		if ((*this)[i] != other[i])
			return false;
	}
	return true;
}
template <typename Derived, typename T, size_t elements>
bool WP_VecBase<Derived, T, elements>::operator!=(const Derived& other) const
{
	return !(*this == other);
}

template <typename Derived, typename T, size_t elements>
T WP_VecBase<Derived, T, elements>::SqDistance(const Derived& other) const
{
	T totalValue = T(0);
	for (int i = 0; i < elements;++i)
	{
		T difference = other.data[i] - this->data[i];
		totalValue += difference * difference;
	}
	return totalValue;
}

template <typename Derived, typename T, size_t elements>
T WP_VecBase<Derived, T, elements>::Distance(const Derived& other) const
	requires std::floating_point<T>
{
	return std::sqrt(this->SqDistance(other));
}

template <typename Derived, typename T, size_t elements>
T WP_VecBase<Derived, T, elements>::DotProd(const Derived& other) const
{
	T result = T(0);
	for (size_t i = 0; i < elements; ++i)
	{
		result += (*this)[i] * other[i];
	}
	return result;
}

template <typename Derived, typename T, size_t elements>
T WP_VecBase<Derived, T, elements>::SqMagnitude() const
{
	T totalValue = T(0);
	for (int i = 0; i < elements;++i)
	{
		totalValue += (*this)[i] * (*this)[i];
	}
	return totalValue;
}
template <typename Derived, typename T, size_t elements>
T WP_VecBase<Derived, T, elements>::Magnitude() const
	requires std::floating_point<T>
{
	return std::sqrt(this->SqMagnitude());
}

template <typename Derived, typename T, size_t elements>
Derived WP_VecBase<Derived, T, elements>::GetNormalized() const
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

template <typename Derived, typename T, size_t elements>
Derived WP_VecBase<Derived, T, elements>::Project(const Derived& other) const
{
	T magnitude = other.SqMagnitude();

	//divide by 0 case
	if (magnitude == T(0))
	{
		return Derived();
	}

	return other * (DotProd(other) / magnitude);
}

template <typename T>
T WP_Vec<T,2>::CrossProd(const WP_Vec<T, 2>& other) const
{
	return this->x * other.y - this->y * other.x;
}

template <typename T>
WP_Vec<T, 2> WP_Vec<T, 2>::Normal() const
{
	return WP_Vec<T, 2>(-this->y, this->x);
}

template <typename T>
WP_Vec<T, 2>& WP_Vec<T, 2>::Rotate(double radians)
	requires std::floating_point<T>
{
	*this = GetRotatedOrigin(radians);
	return *this;
}

template <typename T>
WP_Vec<T, 2> WP_Vec<T, 2>::GetRotatedOrigin(double radians) const
	requires std::floating_point<T>
{
	return WP_Vec<T, 2>(this->x * cos(radians) - this->y * sin(radians),
		this->x * sin(radians) + this->y * cos(radians));
}

template <typename T>
double WP_Vec<T, 2>::Angle() const
{
	return atan2(this->y, this->x);
}

template <typename T>
double WP_Vec<T, 2>::Angle(const WP_Vec<T,2>& other) const
{
	return atan2(CrossProd(other), this->DotProd(other));
}
template <typename T>
WP_Vec<T, 3> WP_Vec<T, 3>::CrossProd(const WP_Vec<T, 3>& other) const
{
	WP_Vec<T, 3> result;
	result. x = this->y * other. z - this->z * other.y;
	result. y = this->z * other. x - this->x * other.z;
	result. z = this->x * other. y - this->y * other.x;
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