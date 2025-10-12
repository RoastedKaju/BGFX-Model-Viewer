#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <memory>

#include "texture.h"

class Material
{
public:
	Material();
	Material(bgfx::ProgramHandle program);
	~Material();

	void Bind() const;

	inline void SetDiffuseMap(const std::shared_ptr<Texture>& diffuse_map) { diffuse_map_ = diffuse_map; }

	inline void SetProgramHandle(bgfx::ProgramHandle program) { program_handle_ = program; }
	inline bgfx::ProgramHandle GetProgramHandle() const { return program_handle_; }

private:
	bgfx::UniformHandle diffuse_sampler_;
	bgfx::ProgramHandle program_handle_;

	std::shared_ptr<Texture> diffuse_map_;
};

#endif // !MATERIAL_H_
