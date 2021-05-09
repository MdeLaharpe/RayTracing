#include "materials/Dielectric.h"

#include <cmath>

#include "Random.h"

namespace rt
{
	float SchlickReflectance(float cosTheta, float refIndex)
	{
		float r0 = (1.f - refIndex) / (1.f + refIndex);
		r0 = r0 * r0;
		return r0 + (1.f - r0) * std::powf((1.f - cosTheta), 5.f);
	}

	bool Dielectric::Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const
	{
		attenuation = maths::Vec3(1.f, 1.f, 1.f);

		float refIndicesRatio = rec.frontFace ? 1.f / refIndex : refIndex;

		maths::Vec3 inDirection = maths::Normalized(rayIn.direction);
		float cosTheta = std::min(maths::Dot(-inDirection, rec.normal), 1.f);
		float sinTheta = std::sqrtf(1.f - cosTheta * cosTheta);

		bool mustReflect = refIndicesRatio * sinTheta > 1.f;

		maths::Vec3 outDirection;
		if (mustReflect || rt::Rand01() < SchlickReflectance(cosTheta, refIndicesRatio))
			outDirection = maths::Reflected(inDirection, rec.normal);
		else
			outDirection = maths::Refracted(inDirection, rec.normal, cosTheta, refIndicesRatio);

		scattered = maths::Ray(rec.point, outDirection, rayIn.time);
		return true;
	}
}