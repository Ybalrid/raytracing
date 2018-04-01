#pragma once

#include "Vector3.hpp"
#include "Ray.hpp"
#include <memory>

class Object
{
public:
	explicit Object(Vector3d pos);
	Vector3d position;
	virtual ~Object()					   = default;
	virtual HitResult hit(const Rayd& ray) = 0;
};

using ObjectUptr = std::unique_ptr<Object>;
