#include "materials/Lambertian.h"

#include "Random.h"

namespace rt
{
	bool Lambertian::Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const
	{
		maths::Vec3 target = rec.point + rec.normal + RandInUnitSphere();
		scattered = maths::Ray(rec.point, target - rec.point, rayIn.time);
		attenuation = albedo;
		return true;
	}
}