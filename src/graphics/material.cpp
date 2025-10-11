#include "material.h"

Material::Material(const bgfx::ProgramHandle& program)
	: program_handle_(program)
{
	diffuse_sampler_ = bgfx::createUniform("texture_diffuse0", bgfx::UniformType::Sampler);
	diffuse_map_ = nullptr;
}

Material::~Material()
{
	if (bgfx::isValid(diffuse_sampler_))
	{
		bgfx::destroy(diffuse_sampler_);
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
