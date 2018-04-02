#pragma once
#include "Object.hpp"
#include <tuple>
#include "MathTools.hpp"

class Sphere : public Object
{
	float radius;
	float sqRadius;

public:
	Sphere(Vector3d pos, float r);

	HitResult hit(const Rayd& r) override;

	Vector3d normalAt(const Vector3d& point) const override;
};
