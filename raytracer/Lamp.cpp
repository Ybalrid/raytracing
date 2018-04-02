#include "Lamp.hpp"

Lamp::Lamp(const Vector3d& pos, double p) :
 value(p), position(pos)
{
	std::cout << "Created point lamp with value " << value << " and position " << position << '\n';
}

double Lamp::attenuation(const Vector3d& hitPoint) const
{
	const auto distance = (position - hitPoint).length();
	return 1.0 / distance;
}
