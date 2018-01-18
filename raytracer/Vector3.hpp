#pragma once

#include <iostream>

template <typename T>
struct Vector3
{
	T x, y, z;

	Vector3()
	{}

	Vector3(T _x, T _y, T _z) : x{ _x }, y{ _y }, z{ _z }
	{}

	Vector3(const T* _array)
	{
		x = _array[0];
		y = _array[1];
		z = _array[2];
	}

	Vector3(const Vector3& other) : x{ other.x }, y{ other.y }, z{ other.z }
	{}

	Vector3(Vector3&& other) noexcept : x{ other.x }, y{ other.y }, z{ other.z }
	{}

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

	Vector3& operator*=(T scaler) noexcept
	{
		x *= scaler;
		y *= scaler;
		z *= scaler;

		return *this;
	}

	Vector3 operator*(T scaler) const noexcept
	{
		auto v{ *this };
		return v *= scaler;
	}

	Vector3& operator+=(const Vector3& vect) noexcept
	{
		x += vect.x;
		y += vect.y;
		z += vect.z;

		return *this;
	}

	Vector3 operator+(const Vector3& b) const noexcept
	{
		auto vect{ *this };
		return vect += b;
	}

	bool operator==(const Vector3& vect) const noexcept
	{
		return x == vect.x && y == vect.y && z == vect.z;
	}

	bool operator!=(const Vector3& vect) const noexcept
	{
		return !(*this == vect);
	}
};

template<typename T>
Vector3<T> operator*(T scalar, const Vector3<T>& vector)
{
	Vector3<T> v{ vector };
	v *= scalar;
	return v;
}

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