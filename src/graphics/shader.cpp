#include "shader.h"

bgfx::ProgramHandle Shader::CreateProgram(const bgfx::ShaderHandle& vsh, const bgfx::ShaderHandle& fsh)
{
	if (!bgfx::isValid(vsh))
	{
		SDL_Log("Failed to create vertex shader\n");
		return BGFX_INVALID_HANDLE;
	}
	if (!bgfx::isValid(fsh))
	{
		SDL_Log("Failed to create fragment shader\n");
		return BGFX_INVALID_HANDLE;
	}

	return bgfx::createProgram(vsh, fsh, true);
}

const bgfx::ShaderHandle Shader::CreateShader(const char* path)
{
	std::ifstream file(path, std::ios::binary | std::ios::ate);

	if (!file.is_open())
	{
		SDL_Log("Failed to open file: %s\n", path);
		return BGFX_INVALID_HANDLE;
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	const bgfx::Memory* mem = bgfx::alloc(uint32_t(size + 1));
	if (!file.read((char*)mem->data, size))
	{
		SDL_Log("Failed to read file: %s\n", path);
		return BGFX_INVALID_HANDLE;
	}

	mem->data[size] = '\0';

	bgfx::ShaderHandle out_handle = bgfx::createShader(mem);

	if (!bgfx::isValid(out_handle))
	{
		SDL_Log("Failed to create shader %s\n", path);
		return BGFX_INVALID_HANDLE;
	}

	return out_handle;
}

Shader::Shader(const char* name) : name_(name)
{
	handle_ = BGFX_INVALID_HANDLE;
}

Shader::~Shader()
{
	if (bgfx::isValid(handle_))
	{
		SDL_Log("Destroying Shader: %s\n", name_.c_str());
		bgfx::destroy(handle_);
	}
}