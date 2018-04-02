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
	Sphere* s0 = s.addObject<Sphere>(Vector3d(0, 1, 4), 1.0);
	Sphere* s1 = s.addObject<Sphere>(Vector3d(2, 0, 4), 0.25);
	Sphere* s2 = s.addObject<Sphere>(Vector3d(-3, 0, 6), 2.0);

	s0->diffuseColor.x = 1;
	s0->diffuseColor.y = 0;
	s0->diffuseColor.z = 0;
	s0->shinyness	  = 100;

	s1->diffuseColor.x = 0;
	s1->diffuseColor.y = 1;
	s1->diffuseColor.z = 0;

	s2->diffuseColor.x = 0;
	s2->diffuseColor.y = 0;
	s2->diffuseColor.z = 1;

	//Plane are point, normal vect
	Plane* p = s.addObject<Plane>(Vector3d(0, 0, 5), Vector3d(0, 1, -1));

	p->diffuseColor.x = 1;
	p->diffuseColor.y = 1;
	p->diffuseColor.z = 0;

	//Lamp are position, power
	s.addLamp<Lamp>(Vector3d(-2, 2, 1), 2);
	s.addLamp<Lamp>(Vector3d(2, 1, 0), 0.5);
	s.addLamp<Lamp>(Vector3d(0, 1, 0), 0.5);

	s.render();
	s.writeRenderTo("output.png");

	hang();
	return 0;
}
