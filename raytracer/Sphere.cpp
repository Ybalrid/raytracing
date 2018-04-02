#include "Sphere.hpp"

Sphere::Sphere(Vector3d pos, double r) :
 Object(pos),
 radius(r),
 sqRadius(r * r)
{
	std::cerr << "Created sphere of radius " << r << " at position " << pos << '\n';
}

HitResult Sphere::hit(const Rayd& r)
{
	double x0, x1;

	//Using the analitycal solution for the ray/sphere interect problem
	const auto L = r.origin - position;
	const auto a = r.direction.dotProduct(r.direction);
	const auto b = 2 * r.direction.dotProduct(L);
	const auto c = L.dotProduct(L) - sqRadius;

	if(!MathTools::solveQuadratic(a, b, c, x0, x1)) return Rayd::nullHit();

	//we want x0 to be the bigger solution
	if(x0 > x1) std::swap(x0, x1);

	if(x0 < 0)
		x0 = x1;
	if(x0 < 0) return Rayd::nullHit();

	return Rayd::goodhit(r, x0);
}

Vector3d Sphere::normalAt(const Vector3d& point) const
{
	return (point - position).normalizedCopy();
}
