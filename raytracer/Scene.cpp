#include "Scene.hpp"

Scene::Scene(size_t img_w, size_t img_h, float fov) :
 cam(img_w, img_h, fov)
{
}

void Scene::addObject(ObjectUptr&& obj)
{
	sceneContent.push_back(std::move(obj));
}

void Scene::addLamp(LampUptr&& lamp)
{
	sceneLighting.push_back(std::move(lamp));
}

void Scene::render()
{
	RGBQUAD good, bad, actual;
	good.rgbBlue  = 255;
	good.rgbGreen = 255;
	good.rgbRed   = 255;
	memset(&bad, 128, sizeof bad);

	auto& backplane = cam.getBackplane();
	for(size_t y(0); y < backplane.height(); ++y)
	{
		for(size_t x(0); x < backplane.width(); ++x)
		{
			//std::cout << "Rendering pixel " << x << ", " << y << '\n';

			auto ray		= cam.getRayForPixel(x, y);
			double lastDist = INFINITY;
			double value	= 0;

			for(auto& obj : sceneContent)
			{
				auto hit = obj->hit(ray);
				if(Rayd::checkHit(hit))
				{
					auto hitpoint = Rayd::getHitPoint(hit);

					if(hitpoint.length() < lastDist)
					{
						lastDist = hitpoint.length();
					}
					else
					{
						continue;
					}

					for(auto& lamp : sceneLighting)
					{
						Rayd shadowRay;
						shadowRay.origin.x = hitpoint.x;
						shadowRay.origin.y = hitpoint.y;
						shadowRay.origin.z = hitpoint.z;

						auto direction = lamp->position - shadowRay.origin;
						direction.normalize();

						shadowRay.direction.x = direction.x;
						shadowRay.direction.y = direction.y;
						shadowRay.direction.z = direction.z;

						auto hack		   = shadowRay.along(1.0 + 2 * std::numeric_limits<double>::epsilon());
						shadowRay.origin.x = hack.x;
						shadowRay.origin.y = hack.y;
						shadowRay.origin.z = hack.z;

						bool blocked = false;
						for(auto& shadowObj : sceneContent)
						{
							if(Rayd::checkHit(shadowObj->hit(shadowRay)))
							{
								blocked = true;
								break;
							}
						}

						if(!blocked)
						{
							//TODO calculate true surface normal
							Vector3d normal = (hitpoint - obj->position).normalizedCopy();

							double dot = std::max(0.0, normal.dotProduct(shadowRay.direction) * lamp->value);
							//std::cout << "dot prouct value : " << value << '\n';
							value += dot;
						}
						else
						{
						}
					}
					memset(&actual, int(255 * std::min(1.0, value)), sizeof(actual));
					backplane.setPixelColor(x, y, actual);
				}
			}
		}
	}
}

void Scene::writeRenderTo(const std::string& path) const
{
	cam.writeImage(path);
}
