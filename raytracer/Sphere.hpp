#pragma once
#include "Object.hpp"
#include <tuple>
#include "MathTools.hpp"

class Sphere : public Object
{
	double radius;
	double sqRadius;

public:
	Sphere(Vector3d pos, double r);

	HitResult hit(const Rayd& r) override;

	Vector3d normalAt(const Vector3d& point) const override;
};
