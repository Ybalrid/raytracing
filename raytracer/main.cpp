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
	//Sphere are origin, radius
	s.addObject<Sphere>(Vector3d(0, 0, 4), 1);
	s.addObject<Sphere>(Vector3d(2, 0, 4), 0.25);
	s.addObject<Sphere>(Vector3d(-1, 0, 6), 2);

	//Plane are point, normal vect
	s.addObject<Plane>(Vector3d(0, 0, 5), Vector3d(0, 1, -1));

	//Lamp are position, power
	s.addLamp<Lamp>(Vector3d(-1, 2, 1), 0.5);
	s.addLamp<Lamp>(Vector3d(4, 2, 4), 0.25);
	s.addLamp<Lamp>(Vector3d(0, 5, 0), 0.25);

	s.render();
	s.writeRenderTo("output.png");

	hang();
	return 0;
}
