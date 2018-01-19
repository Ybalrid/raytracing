#pragma once

#include "Vector3.hpp"

template <typename T>
struct Ray
{
	Vector3<T> origin, direction;
};