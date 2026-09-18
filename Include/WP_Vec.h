#pragma once
#include <concepts>

template <typename T, size_t elements>
struct WP_VecData
{
	T data[elements];
};

template <typename T>
struct WP_VecData<T, 2>
{
	union
	{
		struct
		{
			T x, y;
		};
		T data[2];
	};
};

template <typename T>
struct WP_VecData<T, 3>
{
	union
	{
		struct
		{
			T x, y, z;
		};
		struct
		{
			T r, g, b;
		};
		T data[3];
	};
};

template <typename T>
struct WP_VecData<T, 4>
{
	union
	{
		struct
		{
			T x, y, z, w;
		};
		struct
		{
			T r, g, b, a;
		};
		T data[4];
	};
};

template <typename Derived,typename T, size_t elements>
struct WP_VecBase : public WP_VecData<T, elements>
{
	template <typename... Args>
	WP_VecBase(Args... values)
		requires (sizeof...(Args) <= elements);

	T& operator[](size_t index);

	const T& operator[](size_t index) const;

	Derived& operator+=(const Derived& other);
	Derived operator+(const Derived& other) const;
	Derived& operator-= (const Derived& other);
	Derived operator-(const Derived& other) const;

	template <typename Scalar>
	Derived& operator/=(const Scalar& other);
	template <typename Scalar>
	Derived operator/(const Scalar& other) const;
	template <typename Scalar>
	Derived& operator*=(const Scalar& other);
	template <typename Scalar>
	Derived operator*(const Scalar& other) const;

	bool operator==(const Derived& other) const;
	bool operator!=(const Derived& other) const;

	T SqDistance(const Derived& other) const;
	T Distance(const Derived& other) const
		requires std::floating_point<T>;

	T DotProd(const Derived& other) const;

	T SqMagnitude() const;
	T Magnitude() const
		requires std::floating_point<T>;;

	Derived GetNormalized() const
		requires std::floating_point<T>;

	//project this vector onto the other vector
	Derived Project(const Derived& other) const;
};

template <typename T, size_t elements>
struct WP_Vec : WP_VecBase<WP_Vec<T, elements>,T, elements>
{
	using Base = WP_VecBase<WP_Vec<T,elements>,T, elements>;

	using Base::Base;
};

template <typename T>
struct WP_Vec<T, 2> : WP_VecBase<WP_Vec<T,2>,T, 2>
{
	using Base = WP_VecBase<WP_Vec<T, 2>, T, 2>;

	using Base::Base;

	T CrossProd(const WP_Vec<T,2>& other) const;
	WP_Vec<T,2> Normal() const;

	//Rotation of point with respect to origin
	WP_Vec<T, 2>& Rotate(double radians)
		requires std::floating_point<T>;

	WP_Vec<T, 2> GetRotatedOrigin(double radians) const
		requires std::floating_point<T>;

	//Angle in radians of vector with respect to origin
	double Angle() const;
	//Angle in radians from a point to another point
	double Angle(const WP_Vec<T,2>& other) const;
};

template <typename T>
struct WP_Vec<T,3> : WP_VecBase<WP_Vec<T, 3>,T, 3>
{
	using Base = WP_VecBase<WP_Vec<T, 3>, T, 3>;

	using Base::Base;

	WP_Vec<T, 3> CrossProd(const WP_Vec<T, 3>& other) const;

	WP_Vec<T, 3> Normal() const;

	// Rotate around an axis passing through the origin
	WP_Vec<T, 3>& Rotate(
		const WP_Vec<T, 3>& axis,
		double radians)
		requires std::floating_point<T>;

	WP_Vec<T, 3> GetRotatedOrigin(
		const WP_Vec<T, 3>& axis,
		double radians) const
		requires std::floating_point<T>;

};

using WP_Vec2f = WP_Vec<float, 2>;
using WP_Vec3f = WP_Vec<float, 3>;
using WP_Vec4f = WP_Vec<float, 4>;