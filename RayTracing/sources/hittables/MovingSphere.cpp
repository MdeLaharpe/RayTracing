#include "hittables/MovingSphere.h"

#include "maths/Utils.h"

namespace rt
{
	bool MovingSphere::BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const
	{
		maths::Vec3 minCenter = CenterAt(tMin);
		maths::AABB minAABB{ minCenter - maths::Vec3(radius), minCenter + maths::Vec3(radius) };
		maths::Vec3 maxCenter = CenterAt(tMax);
		maths::AABB maxAABB{ maxCenter - maths::Vec3(radius), maxCenter + maths::Vec3(radius) };

		outAABB = Bound(minAABB, maxAABB);
		return true;
	}

	bool MovingSphere::Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		maths::Vec3 center = CenterAt(r.time);

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
		float theta, phi;
		maths::SphereSurfaceNormalToPolarCoordinates(outwardNormal, theta, phi);
		rec.u = phi / (2.f * maths::pi);
		rec.v = theta / maths::pi;
		rec.material = material;
		return true;
	}

	maths::Vec3 MovingSphere::CenterAt(float t) const
	{
		float lerpFactor = (t - time0) / (time1 - time0);
		return maths::Lerp(center0, center1, lerpFactor);
	}
}