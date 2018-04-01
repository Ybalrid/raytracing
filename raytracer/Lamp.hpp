#pragma once

#include "Vector3.hpp"
#include <memory>

struct Lamp
{
	float value;
	Vector3d position;

	Lamp();
};

using LampUptr = std::unique_ptr<Lamp>;
