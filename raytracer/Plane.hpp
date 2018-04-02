#pragma once

#include "Object.hpp"

class Plane : public Object
{
	Vector3d normal;

public:
	Plane(const Vector3d& pos, const Vector3d norm) :
	 Object(pos), normal(norm.normalizedCopy())
	{
		std::cout << "plane created passing by point " << position << " With normal " << normal << '\n';
	}

	Vector3d normalAt(const Vector3d& /*point*/) const override
	{
		return normal;
	}

	HitResult hit(const Rayd& ray)
	{
		double normalDot = normal.normalizedCopy().dotProduct(ray.direction.normalizedCopy());

		if(std::abs(normalDot) > std::numeric_limits<double>::epsilon())
		{
			Vector3d p  = position - ray.origin;
			double dist = p.dotProduct(normal) / normalDot;
			if(dist > 0)
				return Rayd::goodhit(ray, dist);
		}

		return Rayd::nullHit();
	}
};
