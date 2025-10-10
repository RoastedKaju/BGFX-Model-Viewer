#include "resource_manager.h"

void ResourceManager::LoadShaders()
{
	// Read all the shaders from folder and create them.

	std::shared_ptr<Shader> shader_ptr;
	const std::string& name = "basic";

	if (shaders_map_.find(name) != shaders_map_.cend())
	{
		shaders_map_[name] = shader_ptr;

		// Create and assign
		const bgfx::ShaderHandle vsh = Shader::CreateShader("resources/shaders/vs.bin");
		const bgfx::ShaderHandle fsh = Shader::CreateShader("resources/shaders/fs.bin");
		const bgfx::ProgramHandle program = Shader::CreateProgram(vsh, fsh);
		shader_ptr->SetHandle(program);
	}
	else
	{
		SDL_Log("Shader %s is already loaded\n", name);
	}
}
