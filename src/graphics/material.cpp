#include "material.h"

#include "core/engine.h"

Material::Material()
{
	program_handle_ = BGFX_INVALID_HANDLE;

	diffuse_sampler_ = bgfx::createUniform("texture_diffuse", bgfx::UniformType::Sampler);
	specular_sampler_ = bgfx::createUniform("texture_specular", bgfx::UniformType::Sampler);
	normal_sampler_ = bgfx::createUniform("texture_normal", bgfx::UniformType::Sampler);
	height_sampler_ = bgfx::createUniform("texture_height", bgfx::UniformType::Sampler);

	diffuse_map_ = nullptr;
	specular_map_ = nullptr;
	normal_map_ = nullptr;
	height_map_ = nullptr;
}

Material::Material(bgfx::ProgramHandle program)
	: program_handle_(program)
{
	diffuse_sampler_ = bgfx::createUniform("texture_diffuse", bgfx::UniformType::Sampler);
	specular_sampler_ = bgfx::createUniform("texture_specular", bgfx::UniformType::Sampler);
	normal_sampler_ = bgfx::createUniform("texture_normal", bgfx::UniformType::Sampler);
	height_sampler_ = bgfx::createUniform("texture_height", bgfx::UniformType::Sampler);

	diffuse_map_ = nullptr;
	specular_map_ = nullptr;
	normal_map_ = nullptr;
	height_map_ = nullptr;
}

Material::~Material()
{
	if (bgfx::isValid(diffuse_sampler_))
	{
		bgfx::destroy(diffuse_sampler_);
		diffuse_sampler_ = BGFX_INVALID_HANDLE;
	}
}

void Material::Bind() const
{
	auto& rm = Engine::GetResourceManager();

	bgfx::setTexture(0, diffuse_sampler_, diffuse_map_ ? diffuse_map_->GetHandle() : rm.GetTextures().at(0)->GetHandle());
	bgfx::setTexture(1, specular_sampler_, specular_map_ ? specular_map_->GetHandle() : rm.GetTextures().at(1)->GetHandle());
	bgfx::setTexture(2, normal_sampler_, normal_map_ ? normal_map_->GetHandle() : rm.GetTextures().at(2)->GetHandle());
	bgfx::setTexture(3, height_sampler_, height_map_ ? height_map_->GetHandle() : rm.GetTextures().at(3)->GetHandle());
}

void Material::SetDiffuseMap(const std::shared_ptr<Texture>& diffuse_map)
{
	diffuse_map_ = diffuse_map;
}

void Material::SetSpecularMap(const std::shared_ptr<Texture>& specular_map)
{
	specular_map_ = specular_map;
}

void Material::SetNormalMap(const std::shared_ptr<Texture>& normal_map)
{
	normal_map_ = normal_map;
}

void Material::SetHeightMap(const std::shared_ptr<Texture>& height_map)
{
	height_map_ = height_map;
}
