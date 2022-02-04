#include "textures/SolidColorTexture.h"

namespace rt
{
	maths::Vec3 SolidColorTexture::Value(float u, float v, const maths::Vec3& point) const
	{
		return color;
	}
}