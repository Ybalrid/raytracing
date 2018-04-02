#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

#define M_TAU 2 * M_PI
#define RIGHT_ANGLE M_TAU / 4

void hang()
{
	std::cout << "Press RETURN to continue...";
	std::cin.get();
	std::cin.clear();
}

int main()
{
	Scene s(1024, 768, float(RIGHT_ANGLE));

	s.addObject<Sphere>(Vector3d(0, 0, 4), 1);
	s.addObject<Sphere>(Vector3d(2, 0, 4), 0.25);
	s.addObject<Sphere>(Vector3d(-1, 0, 6), 2);
	s.addObject<Plane>(Vector3d(0, 0, 5), Vector3d(0, 1, -1));
	auto lamp = std::make_unique<Lamp>();

	lamp->position.y = 1;
	lamp->position.z = 2;
	lamp->position.x = -1;
	lamp->value		 = 0.5;
	s.addLamp(std::move(lamp));

	lamp		= std::make_unique<Lamp>();
	lamp->value = 0.5;
	s.addLamp(std::move(lamp));

	s.render();

	s.writeRenderTo("output.png");

	hang();
	return 0;
}
