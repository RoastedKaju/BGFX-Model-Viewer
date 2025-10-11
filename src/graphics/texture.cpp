#include "texture.h"

const bgfx::TextureHandle Texture::CreateTexture(const char* path)
{
	// Open and read the texture file
	std::ifstream file(path, std::ios::binary | std::ios::ate);

	if (!file.is_open())
	{
		SDL_Log("Failed to open texture file: %s\n", path);
		return BGFX_INVALID_HANDLE;
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<uint8_t> buffer(size);
	if (!file.read((char*)buffer.data(), size))
	{
		SDL_Log("Failed to read texture file: %s\n", path);
		return BGFX_INVALID_HANDLE;
	}

	// Decode the image file
	static bx::DefaultAllocator allocator;
	bimg::ImageContainer* image = bimg::imageParse(&allocator, buffer.data(), (uint32_t)size);

	if (!image)
	{
		SDL_Log("Failed to decode image: %s\n", path);
		return BGFX_INVALID_HANDLE;
	}

	const uint16_t width = (uint16_t)image->m_width;
	const uint16_t height = (uint16_t)image->m_height;

	// Create texture handle
	bgfx::TextureHandle handle = bgfx::createTexture2D(
		width,
		height,
		image->m_numMips > 1,
		image->m_numLayers,
		(bgfx::TextureFormat::Enum)image->m_format,
		0,
		bgfx::copy(image->m_data, image->m_size));

	bimg::imageFree(image);

	if (!bgfx::isValid(handle))
	{
		SDL_Log("Failed to create texture handle\n");
		return BGFX_INVALID_HANDLE;
	}

	return handle;
}

const bgfx::TextureHandle Texture::TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	return CreateTexture(filename.c_str());
}

Texture::Texture()
	: handle_(BGFX_INVALID_HANDLE),
	type_(),
	path_()
{

}

Texture::Texture(const std::string& path, const std::string& type)
{
	path_ = path;
	type_ = type;
	handle_ = CreateTexture(path_.c_str());
}

Texture::~Texture()
{
	if (bgfx::isValid(handle_))
	{
		const std::string filename = path_.substr(path_.find_last_of("/") + 1);
		SDL_Log("Destroying texture: %s\n", filename.c_str());
		bgfx::destroy(handle_);
	}
}
