#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <bgfx/bgfx.h>
#include <SDL3/SDL.h>
#include <string>
#include <bimg/decode.h>
#include <fstream>
#include <bx/allocator.h>
#include <vector>

class Texture
{
public:
	static const bgfx::TextureHandle CreateTexture(const char* path);
	static const bgfx::TextureHandle TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

	Texture();
	Texture(const std::string& path, const std::string& type = "");
	~Texture();

	inline const bgfx::TextureHandle& GetHandle() const { return handle_; }
	inline const std::string& GetType() const { return type_; }
	inline const std::string& GetPath() const { return path_; }

	inline void SetHandle(const bgfx::TextureHandle& handle) { handle_ = handle; }
	inline void SetType(const std::string& type) { type_ = type; }
	inline void SetPath(const std::string& path) { path_ = path; }

private:
	bgfx::TextureHandle handle_;
	std::string type_;
	std::string path_;
};

#endif