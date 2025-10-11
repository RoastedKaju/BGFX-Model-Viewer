#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <memory>

#include "texture.h"

class Material
{
public:
	Material(const bgfx::ProgramHandle& program);
	~Material();

	void Bind() const;

	inline void SetDiffuseMap(const std::shared_ptr<Texture>& diffuse_map) { diffuse_map_ = diffuse_map; }

private:
	bgfx::UniformHandle diffuse_sampler_;
	const bgfx::ProgramHandle& program_handle_;

	std::shared_ptr<Texture> diffuse_map_;
};

#endif // !MATERIAL_H_
