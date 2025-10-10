#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <bgfx/bgfx.h>
#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "utils/layout.h"

class ResourceManager
{
public:
	ResourceManager();

	void LoadShaders();
	const std::unordered_map<std::string, std::shared_ptr<Shader>>& GetShaders() const;
	inline const std::vector<std::shared_ptr<Mesh>>& GetMeshes() const { return meshes_; }

	void PrintLoadedShaders();
	void DrawDebugTriangle();
	
private:
	std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_map_;
	std::vector<std::shared_ptr<Mesh>> meshes_;
};

#endif // !RESOURCE_MANAGER_H_
