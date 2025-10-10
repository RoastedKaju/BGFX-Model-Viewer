#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <bgfx/bgfx.h>
#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

#include "graphics/shader.h"

class ResourceManager
{
public:
	ResourceManager() = default;

	void LoadShaders();
	
private:
	std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_map_;
};

#endif // !RESOURCE_MANAGER_H_
