#ifndef MESH_H_
#define MESH_H_

#include <bgfx/bgfx.h>
#include <memory>
#include <vector>
#include <SDL3/SDL.h>

#include "utils/layout.h"

class Mesh
{
public:
	Mesh(const std::vector<VertexData>& vertices, const std::vector<uint16_t>& indices);
	Mesh(const std::vector<VertexData>& vertices, const std::vector<uint16_t>& indices, const std::vector<TextureData> textures);

	~Mesh();

	void Draw(const bgfx::ProgramHandle& program, uint8_t view_id = 0) const;

private:
	bgfx::VertexBufferHandle vbh_;
	bgfx::IndexBufferHandle ibh_;

	std::vector<TextureData> textures_;
};

#endif // !MESH_H_
