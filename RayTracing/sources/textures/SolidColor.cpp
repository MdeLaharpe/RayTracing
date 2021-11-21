#include "textures/SolidColor.h"

namespace rt
{
	maths::Vec3 SolidColor::Value(float u, float v, const maths::Vec3& point) const
	{
		return color;
	}
}