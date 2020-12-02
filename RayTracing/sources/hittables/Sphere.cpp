#include "hittables\Sphere.h"

#include <cmath>

namespace rt
{
	bool Sphere::hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		maths::Vec3 oc = r.origin - center;
		float a = r.direction.magnitude_squared();
		float halfB = maths::dot(oc, r.direction);
		float c = oc.magnitude_squared() - radius * radius;
		float discriminant = halfB * halfB - a * c;

		if (discriminant < 0.f)
			return false;

		float sqrtDiscriminiant = std::sqrtf(discriminant);
		float root = (-halfB - sqrtDiscriminiant) / a;
		if (root < tMin || root > tMax)
		{
			root = (-halfB + sqrtDiscriminiant) / a;

			if (root < tMin || root > tMax)
				return false;
		}

		rec.t = root;
		rec.point = r.at(root);
		rec.normal = (rec.point - center) / radius;
		return true;
	}
}