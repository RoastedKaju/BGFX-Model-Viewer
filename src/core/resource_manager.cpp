#include "resource_manager.h"

ResourceManager::ResourceManager()
{
	VertexData::Init();
}

void ResourceManager::LoadShaders()
{
	// TODO: read the shaders folder, sub-folders and load shaders

	std::shared_ptr<Shader> shader_ptr = std::make_shared<Shader>();
	const std::string& name = "basic";

	if (shaders_map_.find(name) == shaders_map_.cend())
	{
		shaders_map_[name] = shader_ptr;

		// Create and assign
		const bgfx::ShaderHandle vsh = Shader::CreateShader("../../../resources/shaders/vs.bin");
		const bgfx::ShaderHandle fsh = Shader::CreateShader("../../../resources/shaders/fs.bin");
		const bgfx::ProgramHandle program = Shader::CreateProgram(vsh, fsh);
		shader_ptr->SetHandle(program);
	}
	else
	{
		SDL_Log("Shader %s is already loaded\n", name.c_str());
	}
}

const std::unordered_map<std::string, std::shared_ptr<Shader>>& ResourceManager::GetShaders() const
{
	return shaders_map_;
}

void ResourceManager::PrintLoadedShaders()
{
	SDL_Log("Loaded Shaders List:\n");
	for (const auto& [name, ptr] : shaders_map_)
	{
		SDL_Log("%s\n", name.c_str());
	}

	std::vector<VertexData> vertices = {
		{  0.0f,  0.5f, 0.0f, 0xffffffff, 0.0f, 0.0f }, // Top
		{ -0.5f, -0.5f, 0.0f, 0xffffffff, 0.0f, 0.0f }, // Left
		{  0.5f, -0.5f, 0.0f, 0xffffffff, 0.0f, 0.0f }  // Right
	};

	std::vector<uint16_t> indices = { 0, 1, 2 };

	meshes_.push_back(std::make_shared<Mesh>(vertices, indices));
}

void ResourceManager::DrawDebugTriangle()
{
	const Shader& shader = *shaders_map_.begin()->second;
	meshes_.begin()->get()->Draw(shader.GetHandle());
}
