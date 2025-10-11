#ifndef LAYOUT_H_
#define LAYOUT_H_

#include <bgfx/bgfx.h>
#include <string>

struct VertexData
{
	float x, y, z;
	uint32_t abgr;
	float u, v;

	static bgfx::VertexLayout layout;

	static void Init()
	{
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

};

inline bgfx::VertexLayout VertexData::layout;

struct TextureData
{
	bgfx::TextureHandle handle;
	std::string type;
	std::string path;
};

#endif // !LAYOUT_H_
