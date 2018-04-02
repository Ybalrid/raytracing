#pragma once

#include "Object.hpp"

class Plane : public Object
{
	Vector3d normal;

public:
	Plane(const Vector3d& pos, const Vector3d norm);

	Vector3d normalAt(const Vector3d& /*point*/) const override;

	HitResult hit(const Rayd& ray) override;
};
