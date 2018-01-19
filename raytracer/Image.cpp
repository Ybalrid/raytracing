#include "Image.hpp"
#include <cassert>

Image::Image(int width, int height, int depth) : bitmap(nullptr)
{
	bitmap = FreeImage_Allocate(width, height, depth);

	if (!bitmap) throw ImageCantAllocateExcept();
	std::cout << "Allocated a " << width << 'x' << height << 'x' << depth << " bitmap image\n";
}

Image::Image(const std::string& path, FREE_IMAGE_FORMAT fif, int flags) : bitmap(nullptr)
{
	bitmap = FreeImage_Load(fif, path.c_str(), flags);

	if (!bitmap) throw ImageCantLoadExept(path);
	std::cout << "Loaded " << path << " as " << FreeImage_GetFormatFromFIF(fif) << " format\n";
}

Image::Image(Image&& other) noexcept: bitmap(other.bitmap)
{
	other.bitmap = nullptr;
}

Image& Image::operator=(Image&& other) noexcept
{
	//Steal guts of other object
	bitmap = other.bitmap;
	//Prevent other::~Image() from blowing up
	other.bitmap = nullptr;
	return *this;
}

Image::~Image()
{
	if (bitmap)
	{
		FreeImage_Unload(bitmap);
		std::cout << "Unloaded image\n";
	}
}

void Image::save(const std::string& path, FREE_IMAGE_FORMAT fif, int flags) const
{
	std::cout << "Saving image into filepath : " << path << '\n';
	FreeImage_Save(fif, bitmap, path.c_str(), flags);
}

FREE_IMAGE_TYPE Image::type() const
{
	assert(bitmap);
	return FreeImage_GetImageType(bitmap);
}

FREE_IMAGE_COLOR_TYPE Image::colorType() const
{
	assert(bitmap);
	return FreeImage_GetColorType(bitmap);
}

size_t Image::depth() const
{
	assert(bitmap);
	return FreeImage_GetBPP(bitmap);
}

size_t Image::width() const
{
	assert(bitmap);
	return FreeImage_GetWidth(bitmap);
}

size_t Image::height() const
{
	assert(bitmap);
	return FreeImage_GetHeight(bitmap);
}

size_t Image::pitch() const
{
	assert(bitmap);
	return FreeImage_GetPitch(bitmap);
}

RGBQUAD Image::pixelColor(size_t x, size_t y) const
{
	assert(bitmap);
	assert(x < width());
	assert(y < height());
	RGBQUAD color;
	FreeImage_GetPixelColor(bitmap, x, y, &color);
	return color;
}

void Image::setPixelColor(size_t x, size_t y, const RGBQUAD& value)
{
	assert(bitmap);
	assert(x < width());
	assert(y < height());
	FreeImage_SetPixelColor(bitmap, x, y, const_cast<RGBQUAD*>(&value));
}

BYTE* Image::bits()
{
	assert(bitmap);
	return FreeImage_GetBits(bitmap);
}

Image::ColorMask Image::colorMask() const
{
	return
	{
		FreeImage_GetRedMask(bitmap),
		FreeImage_GetGreenMask(bitmap),
		FreeImage_GetBlueMask(bitmap)
	};
}
