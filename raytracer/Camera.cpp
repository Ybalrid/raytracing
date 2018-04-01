
#include "Camera.hpp"

Camera::Camera(size_t backplaneW, size_t backplaneH, float fov, size_t colordepth) :
 backplane(backplaneW, backplaneH, colordepth), radFov(fov), position(0, 0, 0), direction(0, 0, 1), up(0, 1, 0), right(1, 0, 0)
{
	std::cout << "Creating camera object that render at "
			  << backplaneW
			  << 'x'
			  << backplaneH
			  << 'x'
			  << colordepth
			  << " with a fov of "
			  << fov
			  << "rad\n";
}

Rayd Camera::getRayForPixel(size_t x, size_t y)
{
	Rayd ray;
	//TODO fix the vector class
	ray.origin.x = position.x;
	ray.origin.y = position.y;
	ray.origin.z = position.z;

	double px = tan(radFov / 2) * backplane.getRatio() * (2 * ((float(x) + 0.5f) / float(backplane.width())) - 1);
	double py = tan(radFov / 2) * 2 * ((float(y) + 0.5f) / float(backplane.height())) - 1; //maybe flip this one

	auto dir		= Vector3d(px, py, 1).normalizedCopy();
	ray.direction.x = dir.x;
	ray.direction.y = dir.y;
	ray.direction.z = dir.z;

	return ray;
}
