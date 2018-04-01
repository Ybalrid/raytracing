#include "Lamp.hpp"

Lamp::Lamp() :
 value(1), position(4, 0, 4)
{
	std::cout << "Created point lamp with value " << value << " and position " << position << '\n';
}
