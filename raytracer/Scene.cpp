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
	RGBQUAD diffuseCol, specularCol, emissiveCol;
	RGBQUAD output;

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
					memset(&output, 0, sizeof output);
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

						//Add a small amount of bias
						auto originWithBias = shadowRay.along(4096 * std::numeric_limits<double>::epsilon());
						shadowRay.origin.x  = originWithBias.x;
						shadowRay.origin.y  = originWithBias.y;
						shadowRay.origin.z  = originWithBias.z;

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
							const auto normal	 = obj->normalAt(hitpoint);
							auto reflectionVector = shadowRay.direction.reflected(normal);
							auto viewVector		  = -1.0 * ray.direction;

							auto h = (shadowRay.direction + viewVector) *= 1.0 / (shadowRay.direction + viewVector).length();

							//TODO add atenuation
							double diffuse  = (normal.dotProduct(shadowRay.direction) * lamp->attenuation(hitpoint) * lamp->value);
							double specular = (std::pow(normal.dotProduct(h), obj->shinyness) * lamp->attenuation(hitpoint) * lamp->value);

							specularCol.rgbBlue  = std::max(0, int(255 * specular * obj->specularColor.z));
							specularCol.rgbGreen = std::max(0, int(255 * specular * obj->specularColor.y));
							specularCol.rgbRed   = std::max(0, int(255 * specular * obj->specularColor.x));

							diffuseCol.rgbBlue  = std::max(0, int(255 * diffuse * obj->diffuseColor.z));
							diffuseCol.rgbGreen = std::max(0, int(255 * diffuse * obj->diffuseColor.y));
							diffuseCol.rgbRed   = std::max(0, int(255 * diffuse * obj->diffuseColor.x));

							emissiveCol.rgbBlue  = 255 * obj->emissiveColor.z;
							emissiveCol.rgbGreen = 255 * obj->emissiveColor.y;
							emissiveCol.rgbRed   = 255 * obj->emissiveColor.x;

							output.rgbBlue  = std::min(255, output.rgbBlue + specularCol.rgbBlue + diffuseCol.rgbBlue + emissiveCol.rgbBlue);
							output.rgbGreen = std::min(255, output.rgbGreen + specularCol.rgbGreen + diffuseCol.rgbGreen + emissiveCol.rgbGreen);
							output.rgbRed   = std::min(255, output.rgbRed + specularCol.rgbRed + diffuseCol.rgbRed + emissiveCol.rgbRed);
						}
					}

					backplane.setPixelColor(x, y, output);
				}
			}
		}
	}
}

void Scene::writeRenderTo(const std::string& path) const
{
	cam.writeImage(path);
}
