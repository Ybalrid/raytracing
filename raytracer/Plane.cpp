#include "Plane.hpp"

Plane::Plane(const Vector3d& pos, const Vector3d norm) :
 Object(pos), normal(norm.normalizedCopy())
{
	std::cout << "plane created passing by point " << position << " With normal " << normal << '\n';
}

Vector3d Plane::normalAt(const Vector3d&) const
{
	return normal;
}

HitResult Plane::hit(const Rayd& ray)
{
	const auto normalDot = normal.normalizedCopy().dotProduct(ray.direction.normalizedCopy());

	if(std::abs(normalDot) > std::numeric_limits<double>::epsilon())
	{
		const auto p	= position - ray.origin;
		const auto dist = p.dotProduct(normal) / normalDot;
		if(dist > 0)
			return Rayd::goodhit(ray, dist);
	}

	return Rayd::nullHit();
}
