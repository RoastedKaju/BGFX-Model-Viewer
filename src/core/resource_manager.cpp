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
	// Texture '0' is always going to be the default missing
	textures_.push_back(std::make_shared<Texture>("../../../resources/textures/missing_1k.png"));
	textures_.push_back(std::make_shared<Texture>("../../../resources/textures/metal_2k.jpg"));

	// Make material and assign texture and shader
	const Shader& shader = *shaders_map_.begin()->second;
	materials_.push_back(std::make_shared<Material>(shader.GetHandle()));
	materials_.begin()->get()->SetDiffuseMap(*textures_.begin());

	// Import teapot model
	models_.push_back(std::make_shared<Model>("../../../resources/models/teapot/scene.gltf"));

	// Create camera
	camera_ = std::make_shared<Camera>();

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
	models_.at(0)->GetMaterials().at(0)->SetProgramHandle(shader.GetHandle());
	models_.at(0)->GetMaterials().at(0)->Bind();

	// Draw mesh
	//meshes_.begin()->get()->Draw(shader.GetHandle());
	models_.at(0)->Draw(shader.GetHandle());
}
