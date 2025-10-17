#ifndef MODEL_H_
#define MODEL_H_

#include <SDL3/SDL.h>
#include <string>
#include <bgfx/bgfx.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "material.h"

struct MeshSection
{
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
};

class Model
{
	using TextureList = std::vector<std::shared_ptr<Texture>>;

public:
	Model(const std::string& path, bool gamma_correction = false);
	~Model();

	void Draw(uint8_t view_id = 0) const;

	inline const std::vector<std::shared_ptr<Texture>>& GetTextures() const { return textures_; }
	inline const std::vector<MeshSection>& GetMeshSections() const { return mesh_sections_; }

private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	TextureList LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
	std::shared_ptr<Material> CreateMaterials(const TextureList& diffuse_list, const TextureList& specular_list, const TextureList& normal_list, const TextureList& height_list);

	std::vector<std::shared_ptr<Texture>> textures_;
	std::vector<MeshSection> mesh_sections_;
	std::string directory_;
	bool gamma_correction_;
};

#endif // !MODEL_H_
