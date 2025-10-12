#include "model.h"

#include "bx/math.h"
#include "utils/layout.h"

Model::Model(const std::string& path, bool gamma_correction)
	:meshes_{},
	materials_{},
	directory_{},
	gamma_correction_{ gamma_correction }
{
	LoadModel(path);
}

Model::~Model()
{

}

void Model::Draw(const bgfx::ProgramHandle& program, uint8_t view_id) const
{
	for (const auto& mesh : meshes_)
	{
		mesh->Draw(program, view_id);
	}
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		SDL_Log("%s\n", importer.GetErrorString());
		return;
	}

	// retrieve the directory path of the filepath
	directory_ = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(ProcessMesh(mesh, scene));
	}

	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	// data to fill
	std::vector<VertexData> vertices;
	std::vector<uint16_t> indices;
	std::vector<std::shared_ptr<Texture>> textures;

	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		VertexData vertex;

		// positions
		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;

		// normals
		if (mesh->HasNormals())
		{
			vertex.nx = mesh->mNormals[i].x;
			vertex.ny = mesh->mNormals[i].y;
			vertex.nz = mesh->mNormals[i].z;
		}

		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vertex.u = mesh->mTextureCoords[0][i].x;
			vertex.v = mesh->mTextureCoords[0][i].y;

			// tangent
			vertex.tx = mesh->mTangents[i].x;
			vertex.ty = mesh->mTangents[i].y;
			vertex.tz = mesh->mTangents[i].z;

			// bitangent
			vertex.bx = mesh->mBitangents[i].x;
			vertex.by = mesh->mBitangents[i].y;
			vertex.bz = mesh->mBitangents[i].z;
		}
		else
		{
			vertex.u = 0.0f;
			vertex.v = 0.0f;
		}

		vertices.push_back(vertex);
	}

	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// 1. diffuse maps
	std::vector<std::shared_ptr<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//// 2. specular maps
	//std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	//// 3. normal maps
	//std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	//// 4. height maps
	//std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_DISPLACEMENT, "texture_height");
	//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// Create material and assign it to model
	std::shared_ptr<Material> material_obj = std::make_shared<Material>();
	material_obj->SetDiffuseMap(diffuseMaps.at(0));
	materials_.push_back(material_obj);

	// return a mesh object created from the extracted mesh data
	return std::make_shared<Mesh>(vertices, indices);
}

std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName)
{
	std::vector <std::shared_ptr<Texture>> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_.size(); j++)
		{
			if (std::strcmp(textures_[j]->GetPath().data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			std::shared_ptr<Texture> texture = std::make_shared<Texture>();
			texture->SetHandle(Texture::TextureFromFile(str.C_Str(), this->directory_));
			texture->SetType(typeName);
			texture->SetPath(str.C_Str());
			textures.push_back(texture);
			textures_.push_back(texture);
		}
	}
	return textures;
}
