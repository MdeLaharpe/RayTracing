#ifndef RT_METAL_H
#define RT_METAL_H

#include "materials/Material.h"
#include "maths/Vec3.h"

namespace rt
{
	class Metal : public Material
	{
	public:
		constexpr Metal() : albedo(), fuzz(0.f) { }
		constexpr Metal(const maths::Vec3& albedo, float fuzz) : albedo(albedo), fuzz(fuzz) { }

		bool Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const override;

	private:
		maths::Vec3 albedo;
		float fuzz;
	};
}

#endif RT_METAL_H