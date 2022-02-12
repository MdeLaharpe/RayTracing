#ifndef RT_NOISETEXTURE_H
#define RT_NOISETEXTURE_H

#include "textures/Texture.h"

#include "PerlinNoise3D.h"

namespace rt
{
	class NoiseTexture : public Texture
	{
	public:

		enum class CastMethod : int32_t
		{
			Remap,
			Abs
		};

		NoiseTexture() : noise(), frequency(1.f), turbulenceDepth(0), castMethod(CastMethod::Remap) { }
		NoiseTexture(float frequency, size_t turbulenceDepth, CastMethod remapMethod) : noise(), frequency(frequency), turbulenceDepth(turbulenceDepth), castMethod(remapMethod) { }
		virtual ~NoiseTexture() { }

		virtual maths::Vec3 Value(float u, float v, const maths::Vec3& point) const override;

	private:
		PerlinNoise3D<8> noise;
		float frequency;
		size_t turbulenceDepth;
		CastMethod castMethod;
	};
}

#include "PerlinNoise3D.inl"

#endif RT_NOISETEXTURE_H