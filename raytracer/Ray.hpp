#pragma once

#include "Vector3.hpp"

using HitResult = std::pair<bool, Vector3d>;

template <typename T>
struct Ray
{
	Vector3<T> origin, direction;

	Vector3<T> along(T t) const
	{
		return origin + (direction * t);
	}

	static bool checkHit(const HitResult& result)
	{
		return std::get<0>(result);
	}

	static Vector3d getHitPoint(const HitResult& result)
	{
		return std::get<1>(result);
	}

	static HitResult nullHit()
	{
		return std::make_pair(false, Vector3d(0, 0, 0));
	}

	static HitResult goodhit(const Ray<T>& r, T distance)
	{
		return std::make_pair(true, r.along(distance));
	}
};

using Rayf = Ray<float>;
using Rayd = Ray<double>;
