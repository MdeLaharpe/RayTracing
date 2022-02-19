#include "hittables/AARect.h"

namespace rt
{
	bool XYRect::BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const
	{
		outAABB = maths::AABB{ { x0, y0, z - planeAxisAABBHalfThickness }, { x1, y1, z + planeAxisAABBHalfThickness } };
		return true;
	}

	bool XYRect::Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		float t = (z - r.origin.z) / r.direction.z;

		if (t < tMin || t > tMax)
			return false;

		maths::Vec3 point = r.At(t);
		if (point.x < x0 || point.x > x1 || point.y < y0 || point.y > y1)
			return false;

		rec.point = point;
		rec.SetFaceNormal(r, { 0.f, 0.f, 1.f });
		rec.t = t;
		rec.u = (point.x - x0) / (x1 - x0);
		rec.v = (point.y - y0) / (y1 - y0);
		rec.material = material;

		return true;
	}

	bool XZRect::BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const
	{
		outAABB = maths::AABB{ { x0, y - planeAxisAABBHalfThickness, z0 }, { x1, y + planeAxisAABBHalfThickness, z1 } };
		return true;
	}

	bool XZRect::Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		float t = (y - r.origin.y) / r.direction.y;

		if (t < tMin || t > tMax)
			return false;

		maths::Vec3 point = r.At(t);
		if (point.x < x0 || point.x > x1 || point.z < z0 || point.z > z1)
			return false;

		rec.point = point;
		rec.SetFaceNormal(r, { 0.f, 1.f, 0.f });
		rec.t = t;
		rec.u = (point.x - x0) / (x1 - x0);
		rec.v = (point.z - z0) / (z1 - z0);
		rec.material = material;

		return true;
	}

	bool YZRect::BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const
	{
		outAABB = maths::AABB{ { x - planeAxisAABBHalfThickness, y0, z0 }, { x + planeAxisAABBHalfThickness, y1, z1 } };
		return true;
	}

	bool YZRect::Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		float t = (x - r.origin.x) / r.direction.x;

		if (t < tMin || t > tMax)
			return false;

		maths::Vec3 point = r.At(t);
		if (point.y < y0 || point.y > y1 || point.z < z0 || point.z > z1)
			return false;

		rec.point = point;
		rec.SetFaceNormal(r, { 1.f, 0.f, 0.f });
		rec.t = t;
		rec.u = (point.y - y0) / (y1 - y0);
		rec.v = (point.z - z0) / (z1 - z0);
		rec.material = material;

		return true;
	}
}