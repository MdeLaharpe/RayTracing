#ifndef RT_TEXTURE_H
#define RT_TEXTURE_H

#include "maths/Vec3.h"

namespace rt
{
	class Texture
	{
	public:
		virtual ~Texture() { }

		virtual maths::Vec3 Value(float u, float v, const maths::Vec3& point) const = 0;
	};
}

#endif RT_TEXTURE_H