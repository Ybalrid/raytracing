#pragma once

#include "Vector3.hpp"
#include <memory>

struct Lamp
{
	double value;
	Vector3d position;

	Lamp(const Vector3d& pos, double powerFactor);
};

using LampUptr = std::unique_ptr<Lamp>;
