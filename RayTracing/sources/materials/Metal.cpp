#include "materials/Metal.h"

#include "Random.h"

namespace rt
{
	bool Metal::Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const
	{
		maths::Vec3 reflected = maths::Reflected(maths::Normalized(rayIn.direction), rec.normal);
		scattered = maths::Ray(rec.point, reflected + fuzz * RandInUnitSphere());
		attenuation = albedo;
		return maths::Dot(reflected, rec.normal) > 0.f;
	}
}