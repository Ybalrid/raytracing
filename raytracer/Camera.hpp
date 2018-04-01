#pragma once

#include "Image.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

class Camera
{
private:
	Image backplane;
	float radFov;

	Vector3d position, direction, up, right;

public:
	Camera(size_t backplaneW, size_t backplaneH, float fov, size_t colordepth = 24);
	void writeImage(const std::string& path) const { backplane.save(path, FIF_PNG); }

	Rayd getRayForPixel(size_t x, size_t y);

	Image& getBackplane() { return backplane; }
};
