#include "textures/NoiseTexture.h"

namespace rt
{
	maths::Vec3 NoiseTexture::Value(float u, float v, const maths::Vec3& point) const
	{
		return maths::Vec3(1.f) * 0.5f * (1.f + noise.Sample(point * frequency));
	}
}