#include "resource_manager.h"

ResourceManager::ResourceManager()
{
	VertexData::Init();
}

void ResourceManager::LoadShaders()
{
	// TODO: read the shaders folder, sub-folders and load shaders

	const std::string& name = "basic";
	std::shared_ptr<Shader> shader_ptr = std::make_shared<Shader>(name.c_str());

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
		{  0.0f,  0.5f, 0.0f, 0xffffffff, 0.5f, 0.0f }, // Top (center of texture top edge)
		{ -0.5f, -0.5f, 0.0f, 0xffffffff, 0.0f, 1.0f }, // Bottom Left (bottom-left of texture)
		{  0.5f, -0.5f, 0.0f, 0xffffffff, 1.0f, 1.0f }  // Bottom Right (bottom-right of texture)
	};

	std::vector<uint16_t> indices = { 0, 1, 2 };

	meshes_.push_back(std::make_shared<Mesh>(vertices, indices));

	// Load and push back texture
	textures_.push_back(std::make_shared<Texture>("../../../resources/textures/metal_2k.jpg"));

	// Import teapot model
	models_.push_back(std::make_shared<Model>("../../../resources/models/teapot/scene.gltf"));

	// Create camera
	camera_ = std::make_shared<Camera>();

}

void ResourceManager::CreateFallbackTextures()
{
	const uint8_t flat_normal[2 * 2 * 4] = {
		128, 128, 255, 255, 128, 128, 255, 255,
		128, 128, 255, 255, 128, 128, 255, 255
	};

	const uint8_t grey_specular[2 * 2 * 4] = {
		128, 128, 128, 255, 128, 128, 128, 255,
		128, 128, 128, 255, 128, 128, 128, 255
	};

	static const uint8_t flat_height[2 * 2 * 4] = {
		128, 128, 128, 255, 128, 128, 128, 255,
		128, 128, 128, 255, 128, 128, 128, 255
	};

	const bgfx::Memory* mem_normal = bgfx::copy(flat_normal, sizeof(uint8_t) * 2 * 2 * 4);
	const bgfx::TextureHandle normal_handle = bgfx::createTexture2D(2, 2, false, 1, bgfx::TextureFormat::RGBA8, 0, mem_normal);

	const bgfx::Memory* mem_spec = bgfx::copy(grey_specular, sizeof(uint8_t) * 2 * 2 * 4);
	const bgfx::TextureHandle spec_handle = bgfx::createTexture2D(2, 2, false, 1, bgfx::TextureFormat::RGBA8, 0, mem_spec);

	const bgfx::Memory* mem_height = bgfx::copy(flat_height, sizeof(uint8_t) * 2 * 2 * 4);
	const bgfx::TextureHandle height_handle = bgfx::createTexture2D(2, 2, false, 1, bgfx::TextureFormat::RGBA8, 0, mem_height);

	auto normal = std::make_shared<Texture>();
	normal->SetHandle(normal_handle);

	auto spec = std::make_shared<Texture>();
	spec->SetHandle(spec_handle);

	auto height = std::make_shared<Texture>();
	height->SetHandle(height_handle);

	textures_.push_back(std::make_shared<Texture>("../../../resources/textures/missing_1k.png"));
	textures_.push_back(spec);
	textures_.push_back(normal);
	textures_.push_back(height);
}

void ResourceManager::DrawDebugTriangle()
{
	const Shader& shader = *shaders_map_.begin()->second;

	// --- Camera setup ---
	bgfx::setViewTransform(0, camera_->GetViewMatrix(), camera_->GetProjectionMatrix());

	// --- Model transform ---
	float modelMtx[16];
	bx::mtxIdentity(modelMtx);

	// Move teapot forward (camera looks along +Z)
	bx::mtxTranslate(modelMtx, 0.0f, -1.0f, 8.0f);

	// Set transform for bgfx
	bgfx::setTransform(modelMtx);

	// Bind material
	//materials_.begin()->get()->Bind();
	//models_.at(0)->GetMaterials().at(0)->SetProgramHandle(shader.GetHandle());
	//models_.at(0)->GetMaterials().at(0)->Bind();

	// Draw mesh
	//meshes_.begin()->get()->Draw(shader.GetHandle());
	models_.at(0)->Draw();
}
