#pragma once

#include <iostream>
#include <cmath>
#include "MathExcept.hpp"

template <typename T>
struct Vector3
{
	T x, y, z;

	//Ctors
	Vector3()
	{
	}

	Vector3(T _x, T _y, T _z) : x{ _x }, y{ _y }, z{ _z }
	{
	}

	Vector3(const T* _array)
	{
		x = _array[0];
		y = _array[1];
		z = _array[2];
	}

	Vector3(const Vector3& other) : x{ other.x }, y{ other.y }, z{ other.z }
	{
	}

	Vector3(Vector3&& other) noexcept : x{ other.x }, y{ other.y }, z{ other.z }
	{
	}

	///Assign content of new vector to this one. Return a ref to itself as a result
	T& operator=(const Vector3& other) noexcept
	{
		if (this != other)
		{
			x = other.x();
			y = other.y();
			z = other.z();
		}

		return *this;
	}

	///Multiply all members by a sclar
	Vector3& operator*=(T scaler) noexcept
	{
		x *= scaler;
		y *= scaler;
		z *= scaler;

		return *this;
	}

	///Multiply vector by a scaler
	Vector3 operator*(T scaler) const noexcept
	{
		auto v{ *this };
		return v *= scaler;
	}

	///Add vector to this vector
	Vector3& operator+=(const Vector3& vect) noexcept
	{
		x += vect.x;
		y += vect.y;
		z += vect.z;

		return *this;
	}

	Vector3& operator-=(const Vector3& vect) noexcept
	{
		x -= vect.x;
		y -= vect.y;
		z -= vect.z;

		return *this;
	}

	Vector3 operator-(const Vector3& b) const noexcept
	{
		auto vect{ *this };
		return vect -= b;
	}

	///Add vector to vector and return the result
	Vector3 operator+(const Vector3& b) const noexcept
	{
		auto vect{ *this };
		return vect += b;
	}

	///Return true if the two vectors are the same
	bool operator==(const Vector3& vect) const noexcept
	{
		return x == vect.x && y == vect.y && z == vect.z;
	}

	///Return true if the two vectors are differents
	bool operator!=(const Vector3& vect) const noexcept
	{
		return !(*this == vect);
	}

	///Return the squared
	T squaredLenght() const noexcept
	{
		return (x * x) + (y * y) + (z * z);
	}

	///Return the lenght of the vector
	T length() const noexcept
	{
		return std::sqrt(squaredLenght());
	}

	///Normalize this vector. Will not work on a null vector
	void normalize()
	{
		const auto len = length();
		if (len == 0) throw DivideByZeroExcept("Can't normalize a null vector");
		x /= len;
		y /= len;
		z /= len;
	}

	///Normalize a copy of the vector and return it
	Vector3 normalizedCopy() const
	{
		Vector3 vect = *this;
		vect.normalize();
		return vect;
	}

	///dot product
	T dotProduct(const Vector3<T>& v) const
	{
		return
		{
			(x * v.x) +
			(y * v.y) +
			(z * v.z)
		};
	}

	T scalarProduct(const Vector3<T>& v) const
	{
		return dotProduct(v);
	}

	T innerProduct(const Vector3<T>& v) const
	{
		return dotProduct(v);
	}

	///Cross product
	Vector3 crossProduct(const Vector3<T>& v) const
	{
		return
		{
			(y * v.z) - (z * v.y),
			(z * v.x) - (x * v.z),
			(x * v.y) - (y * v.x)
		};
	}

	Vector3 vectorialProduct(const Vector3<T>& v) const
	{
		return crossProduct(v);
	}

	///Reflect this vector from a normal one;
	Vector3 reflected(const Vector3<T>& normal) const
	{
		auto vect{ *this };
		const auto normalizedNormal{ normal.normalizedCopy() };

		return (normalizedNormal * vect.dotProduct(normalizedNormal) * T(2)) - vect;
	}

	bool isNull() const
	{
		return squaredLenght() == T(0);
	}
};

///Handle the scalar*vector operation
template <typename T>
Vector3<T> operator*(T scalar, const Vector3<T>& vector)
{
	Vector3<T> v{ vector };
	v *= scalar;
	return v;
}

///Print the vector's content
template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector3<T> vect)
{
	out << "Vector3("
		<< vect.x << ", "
		<< vect.y << ", "
		<< vect.z << ")";
	return out;
}

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3ld = Vector3<long double>;
