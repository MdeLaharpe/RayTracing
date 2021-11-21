#ifndef RT_SOLIDCOLOR_H
#define RT_SOLIDCOLOR_H

#include "textures/Texture.h"

namespace rt
{
	class SolidColor : public Texture
	{
	public:
		constexpr SolidColor() : color() { }
		constexpr SolidColor(const maths::Vec3& color) : color(color) { }

		virtual ~SolidColor() { }

		virtual maths::Vec3 Value(float u, float v, const maths::Vec3& point) const override;

	private:
		maths::Vec3 color;
	};
}

#endif RT_SOLIDCOLOR_H