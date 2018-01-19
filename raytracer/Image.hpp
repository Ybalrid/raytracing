#pragma once

#include <FreeImage.h>
#include <iostream>
#include "ImageExept.hpp"

class Image
{
	FIBITMAP* bitmap;

public:
	struct ColorMask
	{
		unsigned R, G, B;
	};
	///Construct an image into memory
	Image(int width, int height, int depth = 24);
	///Load image from file
	Image(const std::string& path, FREE_IMAGE_FORMAT fif, int flags = 0);

	///non copyable
	Image(const Image&) = delete;
	///non copy-asignable
	Image& operator=(const Image&) = delete;
	
	///Move constructor
	Image(Image&& other) noexcept;
	///Asignment-move operator
	Image& operator=(Image&& other) noexcept;
	///Destructor. Will FreeImage_Unload() the bitmap
	~Image();
	///Save image to file
	void save(const std::string& path, FREE_IMAGE_FORMAT fif, int flags = 0) const;
	///Return the type of the image
	FREE_IMAGE_TYPE type() const;
	///Return the color type of the pixels in the image
	FREE_IMAGE_COLOR_TYPE colorType() const;
	///Return the number of bit per pixels
	size_t depth() const;
	///Return the width of the image in pixels
	size_t width() const;
	///Return the height of the image in pixels
	size_t height() const;
	///Return the color at this position
	RGBQUAD pixelColor(size_t x, size_t y) const;
	///Set the color at this position 
	void setPixelColor(size_t x, size_t y, const RGBQUAD& value);
	///get the array of bits that this image does
	BYTE* bits();
	///Get the 3 color masks
	ColorMask colorMask() const;
};
