#include "hittables/MovingSphere.h"

namespace rt
{
	bool MovingSphere::Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		float lerpFactor = (r.time - time0) / (time1 - time0);
		const maths::Vec3 center = maths::Lerp(center0, center1, lerpFactor);

		maths::Vec3 oc = r.origin - center;
		float a = r.direction.MagnitudeSquared();
		float halfB = maths::Dot(oc, r.direction);
		float c = oc.MagnitudeSquared() - radius * radius;
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
		rec.point = r.At(root);
		maths::Vec3 outwardNormal = (rec.point - center) / radius;
		rec.SetFaceNormal(r, outwardNormal);
		rec.material = material;
		return true;
	}
}