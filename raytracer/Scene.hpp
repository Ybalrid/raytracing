#pragma once

#include "Camera.hpp"
#include <memory>
#include <vector>
#include <utility>
#include "Object.hpp"
#include "Lamp.hpp"
#include <algorithm>

class Scene
{
	Camera cam;

	std::vector<std::unique_ptr<Object>> sceneContent;
	std::vector<std::unique_ptr<Lamp>> sceneLighting;

public:
	Scene(size_t img_w, size_t img_h, float fov);

	void addObject(ObjectUptr&& obj);

	template <class ObjectType, typename... Args>
	decltype(auto) addObject(Args... args)
	{
		auto objPtr = std::make_unique<ObjectType>(args...);
		auto raw	= objPtr.get();
		addObject(std::move(objPtr));
		return raw;
	}

	void addLamp(LampUptr&& lamp);

	template <class LampType, typename... Args>
	decltype(auto) addLamp(Args... args)
	{
		auto lmpPtr = std::make_unique<LampType>(args...);
		auto raw	= lmpPtr.get();
		addLamp(std::move(lmpPtr));
		return raw;
	}

	void render();

	void writeRenderTo(const std::string& path) const;
};
