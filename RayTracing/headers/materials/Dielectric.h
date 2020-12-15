#ifndef RT_DIELECTRIC_H
#define RT_DIELECTRIC_H

#include "materials/Material.h"
#include "maths/Vec3.h"
#include "maths/Ray.h"

namespace rt
{
	class Dielectric : public Material
	{
	public:
		constexpr Dielectric() : refIndex(1.f) { }
		Dielectric(float refIndex) : refIndex(refIndex) { }

		bool Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const override;

	private:
		float refIndex;
	};
}

#endif RT_DIELECTRIC_H