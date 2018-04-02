#pragma once

#include "Vector3.hpp"
#include <memory>

struct Lamp
{
	double value;
	Vector3d position;

	Lamp(const Vector3d& pos, double powerFactor);
	double attenuation(const Vector3d& hitPoint) const;
};

using LampUptr = std::unique_ptr<Lamp>;
