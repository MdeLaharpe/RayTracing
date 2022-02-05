#ifndef RT_NOISETEXTURE_H
#define RT_NOISETEXTURE_H

#include "textures/Texture.h"

#include "PerlinNoise3D.h"

namespace rt
{
	class NoiseTexture : public Texture
	{
	public:
		NoiseTexture() : noise() { }
		virtual ~NoiseTexture() { }

		virtual maths::Vec3 Value(float u, float v, const maths::Vec3& point) const override;

	private:
		PerlinNoise3D<8> noise;
	};
}

#include "PerlinNoise3D.inl"

#endif RT_NOISETEXTURE_H