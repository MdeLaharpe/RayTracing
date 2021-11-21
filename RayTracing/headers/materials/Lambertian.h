#ifndef RT_LAMBERTIAN_H
#define RT_LAMBERTIAN_H

#include "materials/Material.h"
#include "maths/Vec3.h"

#include <memory>

namespace rt
{
	class Lambertian : public Material
	{
	public:
		constexpr Lambertian() : albedo() { };
		constexpr Lambertian(const maths::Vec3& albedo) : albedo(albedo) { };

		virtual bool Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const override;

	private:
		maths::Vec3 albedo;
	};
}

#endif RT_LAMBERTIAN_H