#include "materials/Dielectric.h"

namespace rt
{
	bool Dielectric::Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const
	{
		attenuation = maths::Vec3(1.f, 1.f, 1.f);

		float refIndicesRatio = rec.frontFace ? 1.f / refIndex : refIndex;
		maths::Vec3 refracted = maths::Refract(maths::Normalized(rayIn.direction), rec.normal, refIndicesRatio);

		scattered = maths::Ray(rec.point, refracted);
		return true;
	}
}