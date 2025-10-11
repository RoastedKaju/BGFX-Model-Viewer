#include "mesh.h"

Mesh::Mesh(const std::vector<VertexData>& vertices, const std::vector<uint16_t>& indices)
{
	vbh_ = BGFX_INVALID_HANDLE;
	ibh_ = BGFX_INVALID_HANDLE;

	const bgfx::Memory* vb_mem = bgfx::copy(vertices.data(), vertices.size() * sizeof(VertexData));
	const bgfx::Memory* ib_mem = bgfx::copy(indices.data(), indices.size() * sizeof(uint16_t));

	vbh_ = bgfx::createVertexBuffer(vb_mem, VertexData::layout);
	ibh_ = bgfx::createIndexBuffer(ib_mem);
}

Mesh::Mesh(const std::vector<VertexData>& vertices, const std::vector<uint16_t>& indices, const std::vector<TextureData> textures)
	: Mesh(vertices, indices)
{
	textures_ = textures;
}

Mesh::~Mesh()
{
	if (!bgfx::isValid(vbh_))
		bgfx::destroy(vbh_);

	if (!bgfx::isValid(ibh_))
		bgfx::destroy(ibh_);
}

void Mesh::Draw(const bgfx::ProgramHandle& program, uint8_t view_id) const
{
	unsigned int diffuse_num = 1;

	for (unsigned int i = 0; i < textures_.size(); i++)
	{
		std::string name = textures_[i].type;
		std::string number;

		if (name == "texture_diffuse")
			number = std::to_string(diffuse_num++);
		// Specular
		// Normal
		// Height

		std::string uniformName = name + number;

		// Retrieve uniform handle
		bgfx::UniformHandle sampler = bgfx::createUniform(uniformName.c_str(), bgfx::UniformType::Sampler);

		// Bind texture to uniform slot
		bgfx::setTexture(i, sampler, textures_[i].handle);
	}

	bgfx::setVertexBuffer(0, vbh_);
	bgfx::setIndexBuffer(ibh_);

	bgfx::setState(BGFX_STATE_DEFAULT);
	
	bgfx::submit(view_id, program);
}
