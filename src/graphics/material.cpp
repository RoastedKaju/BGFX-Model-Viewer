#include "material.h"

#include "core/engine.h"

Material::Material()
{
	diffuse_sampler_ = bgfx::createUniform("texture_diffuse", bgfx::UniformType::Sampler);
	program_handle_ = BGFX_INVALID_HANDLE;
	diffuse_map_ = nullptr;
}

Material::Material(bgfx::ProgramHandle program)
	: program_handle_(program)
{
	diffuse_sampler_ = bgfx::createUniform("texture_diffuse", bgfx::UniformType::Sampler);
	diffuse_map_ = nullptr;
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
	if (!diffuse_map_ || !bgfx::isValid(diffuse_map_->GetHandle()))
	{
		SDL_Log("Diffuse map invalid.\n");
		return;
	}

	bgfx::setTexture(0, diffuse_sampler_, diffuse_map_->GetHandle());
}

void Material::SetDiffuseMap(const std::shared_ptr<Texture>& diffuse_map)
{
	if (diffuse_map)
	{
		diffuse_map_ = diffuse_map;
		return;
	}

	diffuse_map_ = Engine::GetResourceManager().GetTextures().at(0);
}
