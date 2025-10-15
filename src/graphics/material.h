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

	void SetDiffuseMap(const std::shared_ptr<Texture>& diffuse_map);
	void SetSpecularMap(const std::shared_ptr<Texture>& specular_map);
	void SetNormalMap(const std::shared_ptr<Texture>& normal_map);
	void SetHeightMap(const std::shared_ptr<Texture>& height_map);

	inline const std::shared_ptr<Texture>& GetDiffuseMap() const { return diffuse_map_; }
	inline const std::shared_ptr<Texture>& GetSpecularMap() const { return specular_map_; }
	inline const std::shared_ptr<Texture>& GetNormalMap() const { return normal_map_; }
	inline const std::shared_ptr<Texture>& GetHeightMap() const { return height_map_; }

	inline void SetProgramHandle(bgfx::ProgramHandle program) { program_handle_ = program; }
	inline bgfx::ProgramHandle GetProgramHandle() const { return program_handle_; }

private:
	bgfx::ProgramHandle program_handle_;

	// Diffuse
	bgfx::UniformHandle diffuse_sampler_;
	std::shared_ptr<Texture> diffuse_map_;

	// Specular
	bgfx::UniformHandle specular_sampler_;
	std::shared_ptr<Texture> specular_map_;

	// Normal
	bgfx::UniformHandle normal_sampler_;
	std::shared_ptr<Texture> normal_map_;

	// Height
	bgfx::UniformHandle height_sampler_;
	std::shared_ptr<Texture> height_map_;
};

#endif // !MATERIAL_H_
