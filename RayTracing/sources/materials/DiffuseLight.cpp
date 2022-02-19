#include "materials/DiffuseLight.h"

namespace rt
{
	bool DiffuseLight::Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const
	{
		return false;
	}

	maths::Vec3 DiffuseLight::Emit(float u, float v, const maths::Vec3& point) const
	{
		return emissive->Value(u, v, point);
	}
}