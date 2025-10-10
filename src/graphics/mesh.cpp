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

Mesh::~Mesh()
{
	if (!bgfx::isValid(vbh_))
		bgfx::destroy(vbh_);

	if (!bgfx::isValid(ibh_))
		bgfx::destroy(ibh_);
}

void Mesh::Draw(const bgfx::ProgramHandle& program, uint8_t view_id) const
{
	bgfx::setVertexBuffer(0, vbh_);
	bgfx::setIndexBuffer(ibh_);
	bgfx::submit(view_id, program);
}
