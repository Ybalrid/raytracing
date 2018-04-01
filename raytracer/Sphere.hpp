#pragma once
#include "Object.hpp"
#include <tuple>
#include "MathTools.hpp"

class Sphere : public Object
{
	float radius;
	float sqRadius;

public:
	Sphere(Vector3d pos, float r) :
	 Object(pos),
	 radius(r),
	 sqRadius(r * r)
	{
		std::cerr << "Created sphere of radius " << r << " at position " << pos << '\n';
	}

	HitResult hit(const Rayd& r) override
	{
		double x0, x1;

		//Using the analitycal solution for the ray/sphere interect problem
		Vector3d L = r.origin - position;
		double a   = r.direction.dotProduct(r.direction);
		double b   = 2 * r.direction.dotProduct(L);
		double c   = L.dotProduct(L) - sqRadius;

		if(!MathTools::solveQuadratic(a, b, c, x0, x1)) return Rayd::nullHit();

		//we want x0 to be the bigger solution
		if(x0 > x1) std::swap(x0, x1);

		if(x0 < 0)
			x0 = x1;
		if(x0 < 0) return Rayd::nullHit();

		return Rayd::goodhit(r, x0);
	}
};
