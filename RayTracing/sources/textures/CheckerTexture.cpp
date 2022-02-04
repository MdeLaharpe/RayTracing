#include "textures/CheckerTexture.h"

#include <cmath>

namespace rt
{
	maths::Vec3 CheckerTexture::Value(float u, float v, const maths::Vec3& point) const
	{
		float sines = std::sin(piOverScale * point.x) * std::sin(piOverScale * point.y) * std::sin(piOverScale * point.z);
		if (sines < 0.f)
			return oddTexture->Value(u, v, point);
		else
			return evenTexture->Value(u, v, point);
	}
}