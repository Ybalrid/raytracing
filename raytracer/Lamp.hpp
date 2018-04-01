#pragma once

#include "Vector3.hpp"

struct Lamp
{
	float value;
	Vector3d position;

	Lamp() :
	 value(1), position(4, 0, 4)
	{
		std::cout << "Created point lamp with value " << value << " and position " << position << '\n';
	}
};

using LampUptr = std::unique_ptr<Lamp>;
