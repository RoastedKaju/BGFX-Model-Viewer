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

class Model
{
public:
	Model(const std::string& path, bool gamma_correction = false);
	~Model();

	void Draw(const bgfx::ProgramHandle& program, uint8_t view_id = 0) const;

	inline const std::vector<std::shared_ptr<Mesh>>& GetMeshes() const { return meshes_; }
	inline const std::vector<std::shared_ptr<Texture>>& GetTextures() const { return textures_; }
	inline const std::vector<std::shared_ptr<Material>>& GetMaterials() const { return materials_; }

private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);

	std::vector<std::shared_ptr<Mesh>> meshes_;
	std::vector<std::shared_ptr<Texture>> textures_;
	std::vector<std::shared_ptr<Material>> materials_;
	std::string directory_;
	bool gamma_correction_;
};

#endif // !MODEL_H_
