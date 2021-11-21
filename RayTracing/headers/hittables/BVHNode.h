#ifndef RT_BVHNODE_H
#define RT_BVHNODE_H

#include "Hittable.h"

#include <vector>

namespace rt
{
	class BVHNode : public Hittable
	{
	public:
		constexpr BVHNode() : left(nullptr), right(nullptr), aabb() { }
		BVHNode(std::vector<std::shared_ptr<Hittable>>& list, size_t start, size_t end, float time0, float time1);

		virtual bool BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const override;
		virtual bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

	private:
		std::shared_ptr<Hittable> left, right;
		maths::AABB aabb;
	};
}

#endif RT_BVHNODE_H