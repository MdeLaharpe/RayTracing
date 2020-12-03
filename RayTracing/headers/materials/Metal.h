#ifndef RT_METAL_H
#define RT_METAL_H

#include "materials/Material.h"
#include "maths/Vec3.h"

namespace rt
{
	class Metal : public Material
	{
	public:
		constexpr Metal() : albedo() { }
		constexpr Metal(const maths::Vec3& albedo) : albedo(albedo) { }

		bool Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const override;

	private:
		maths::Vec3 albedo;
	};
}

#endif RT_METAL_H