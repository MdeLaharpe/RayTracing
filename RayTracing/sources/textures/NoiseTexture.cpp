#include "textures/NoiseTexture.h"

namespace rt
{
	maths::Vec3 NoiseTexture::Value(float u, float v, const maths::Vec3& point) const
	{
		switch (castMethod)
		{
		default:
		case CastMethod::Remap:
			return maths::Vec3(1.f) * 0.5f * (1.f + noise.Sample(point * frequency, turbulenceDepth));

		case CastMethod::Abs:
			return maths::Vec3(1.f) * std::abs(noise.Sample(point * frequency, turbulenceDepth));
		}
	}
}