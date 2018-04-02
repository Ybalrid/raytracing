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
	RGBQUAD diffuseCol, specularCol, emissiveCol, output;
	auto blocked = true;

	//Get access to the image
	auto& backplane = cam.getBackplane();

	//For each pixel:
	for(size_t y(0); y < backplane.height(); ++y)
	{
		for(size_t x(0); x < backplane.width(); ++x)
		{
			//std::cout << "Rendering pixel " << x << ", " << y << '\n';

			//Compute the ray
			auto ray		= cam.getRayForPixel(x, y);
			double lastDist = INFINITY;

			//Check if that ray can touch each object
			for(auto& obj : sceneContent)
			{
				auto hit = obj->hit(ray);

				//If we can hit the object
				if(Rayd::checkHit(hit))
				{
					//get the position of the ray/object intersection
					const auto hitpoint = Rayd::getHitPoint(hit);

					//If this value is lower than the last time we hit something, calculate the pixel.
					if(hitpoint.length() < lastDist)
						lastDist = hitpoint.length();
					//Value not lower? try another object
					else
						continue;

					//Set to black the output corlor
					memset(&output, 0, sizeof output);

					//Calculate the contribution on the output collor of each light
					for(auto& lamp : sceneLighting)
					{
						//Ray between intersect and light source
						Rayd shadowRay;
						shadowRay.origin.x = hitpoint.x;
						shadowRay.origin.y = hitpoint.y;
						shadowRay.origin.z = hitpoint.z;

						const auto direction  = (lamp->position - shadowRay.origin).normalizedCopy();
						shadowRay.direction.x = direction.x;
						shadowRay.direction.y = direction.y;
						shadowRay.direction.z = direction.z;

						//Add a small amount of bias
						const auto originWithBias = shadowRay.along(4096 * std::numeric_limits<double>::epsilon());
						shadowRay.origin.x		  = originWithBias.x;
						shadowRay.origin.y		  = originWithBias.y;
						shadowRay.origin.z		  = originWithBias.z;

						//Check if no object block that light from us
						blocked = false;
						for(auto& shadowObj : sceneContent)
						{
							if(Rayd::checkHit(shadowObj->hit(shadowRay)))
							{
								blocked = true;
								break;
							}
						}

						//if light is visible
						if(!blocked)
						{
							//Get the normal and view vectors
							const auto normal	 = obj->normalAt(hitpoint);
							const auto viewVector = -1.0 * ray.direction;

							//Calculate the blinn-phong median vector (L+H / ||L+H||)
							const auto h = (shadowRay.direction + viewVector) *= 1.0 / (shadowRay.direction + viewVector).length();

							//Calculate teh diffuse and specular factor we should use
							const auto diffuse  = (normal.dotProduct(shadowRay.direction) * lamp->attenuation(hitpoint) * lamp->value);
							const auto specular = (std::pow(normal.dotProduct(h), obj->shinyness) * lamp->attenuation(hitpoint) * lamp->value);

							//Compute the specular, diffuse and emissive colors. The dot product may be negatives, so beware ;-)
							specularCol.rgbBlue  = std::max(0, int(255 * specular * obj->specularColor.z));
							specularCol.rgbGreen = std::max(0, int(255 * specular * obj->specularColor.y));
							specularCol.rgbRed   = std::max(0, int(255 * specular * obj->specularColor.x));

							diffuseCol.rgbBlue  = std::max(0, int(255 * diffuse * obj->diffuseColor.z));
							diffuseCol.rgbGreen = std::max(0, int(255 * diffuse * obj->diffuseColor.y));
							diffuseCol.rgbRed   = std::max(0, int(255 * diffuse * obj->diffuseColor.x));

							emissiveCol.rgbBlue  = 255 * obj->emissiveColor.z;
							emissiveCol.rgbGreen = 255 * obj->emissiveColor.y;
							emissiveCol.rgbRed   = 255 * obj->emissiveColor.x;

							//Set the bytes. Cut every overflow
							output.rgbBlue  = std::min(255, output.rgbBlue + specularCol.rgbBlue + diffuseCol.rgbBlue + emissiveCol.rgbBlue);
							output.rgbGreen = std::min(255, output.rgbGreen + specularCol.rgbGreen + diffuseCol.rgbGreen + emissiveCol.rgbGreen);
							output.rgbRed   = std::min(255, output.rgbRed + specularCol.rgbRed + diffuseCol.rgbRed + emissiveCol.rgbRed);
						}
					}

					//set the color of that pixel!
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
