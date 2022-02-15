#ifndef RT_IMAGETEXTURE_H
#define RT_IMAGETEXTURE_H

#include "textures/Texture.h"

#include <filesystem>

namespace rt
{
	class ImageTexture : public Texture
	{
	public:
		ImageTexture(const std::filesystem::path& filePath);
		virtual ~ImageTexture();

		virtual maths::Vec3 Value(float u, float v, const maths::Vec3& point) const override;

	private:
		static constexpr int32_t channels = 3;

		uint8_t* data;
		int32_t width, height;
		int32_t bytesPerPixel;
		int32_t bytesPerScanline;
	};
}

#endif RT_IMAGETEXTURE_H