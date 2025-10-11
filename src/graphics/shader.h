#ifndef SHADER_H_
#define SHADER_H_

#include <fstream>
#include <string>
#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>

class Shader
{
public:
	static const bgfx::ShaderHandle CreateShader(const char* path);
	static bgfx::ProgramHandle CreateProgram(const bgfx::ShaderHandle& vsh, const bgfx::ShaderHandle& fsh);

	Shader(const char* name);
	~Shader();

	inline void SetHandle(const bgfx::ProgramHandle handle) { handle_ = handle; }
	inline const bgfx::ProgramHandle GetHandle() const { return handle_; }
private:
	bgfx::ProgramHandle handle_;
	const std::string name_;
};

#endif // !SHADER_H_
