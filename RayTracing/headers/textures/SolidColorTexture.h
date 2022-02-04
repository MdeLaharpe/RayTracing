#ifndef RT_SOLIDCOLOR_H
#define RT_SOLIDCOLOR_H

#include "textures/Texture.h"

namespace rt
{
	class SolidColorTexture : public Texture
	{
	public:
		constexpr SolidColorTexture() : color() { }
		constexpr SolidColorTexture(const maths::Vec3& color) : color(color) { }

		virtual ~SolidColorTexture() { }

		virtual maths::Vec3 Value(float u, float v, const maths::Vec3& point) const override;

	private:
		maths::Vec3 color;
	};
}

#endif RT_SOLIDCOLOR_H