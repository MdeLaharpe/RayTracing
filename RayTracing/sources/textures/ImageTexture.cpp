#include "textures/ImageTexture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace rt
{
	ImageTexture::ImageTexture(const std::filesystem::path& filePath)
		: data(nullptr), width(0), height(0), bytesPerPixel(0), bytesPerScanline(0)
	{
		data = stbi_load(filePath.string().c_str(), &width, &height, &bytesPerPixel, channels);
		if (!data)
		{
			std::cerr << "ERROR: Could not load texture image file '" << filePath << "'" << std::endl;
			width = height = bytesPerPixel = 0;
		}

		bytesPerScanline = width * bytesPerPixel;
	}

	ImageTexture::~ImageTexture()
	{
		if (data)
			stbi_image_free(data);
	}

	maths::Vec3 ImageTexture::Value(float u, float v, const maths::Vec3& point) const
	{
		// If image loading failed and we have no data, return magenta as debugging aid
		if (!data)
			return maths::Vec3(1.f, 0.f, 1.f);

		// Clamp input UVs to [0, 1] and flip v
		u = std::clamp(u, 0.f, 1.f);
		v = 1.f - std::clamp(v, 0.f, 1.f);

		int32_t i = std::min(static_cast<int32_t>(u * width), width - 1);
		int32_t j = std::min(static_cast<int32_t>(v * height), height - 1);

		constexpr float colorScale = 1.f / 255.f;
		uint8_t* pixel = data + j * bytesPerScanline + i * bytesPerPixel;
		return maths::Vec3(pixel[0] * colorScale, pixel[1] * colorScale, pixel[2] * colorScale);
	}
}