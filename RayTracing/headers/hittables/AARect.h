#ifndef RT_AARECT_H
#define RT_AARECT_H

#include "hittables/Hittable.h"

namespace rt
{
	class AARect : public Hittable
	{
	public:
		AARect(std::shared_ptr<Material> material) : material(std::move(material)) { }

		virtual ~AARect() { }

	protected:
		std::shared_ptr<Material> material;

		static constexpr float planeAxisAABBHalfThickness = 0.0001f;
	};

	class XYRect : public AARect
	{
	public:
		XYRect(float z, float x0, float x1, float y0, float y1, std::shared_ptr<Material> material)
			: AARect(std::move(material)), z(z), x0(std::min(x0, x1)), x1(std::max(x0, x1)), y0(std::min(y0, y1)), y1(std::max(y0, y1))
		{ }

		virtual ~XYRect() { }

		virtual bool BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const override;
		virtual bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

	private:
		float z, x0, x1, y0, y1;
	};

	class XZRect : public AARect
	{
	public:
		XZRect(float y, float x0, float x1, float z0, float z1, std::shared_ptr<Material> material)
			: AARect(std::move(material)), y(y), x0(std::min(x0, x1)), x1(std::max(x0, x1)), z0(std::min(z0, z1)), z1(std::max(z0, z1))
		{ }

		virtual ~XZRect() { }

		virtual bool BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const override;
		virtual bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

	private:
		float y, x0, x1, z0, z1;
	};

	class YZRect : public AARect
	{
	public:
		YZRect(float x, float y0, float y1, float z0, float z1, std::shared_ptr<Material> material)
			: AARect(std::move(material)), x(x), y0(std::min(y0, y1)), y1(std::max(y0, y1)), z0(std::min(z0, z1)), z1(std::max(z0, z1))
		{ }

		virtual ~YZRect() { }

		virtual bool BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const override;
		virtual bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

	private:
		float x, y0, y1, z0, z1;
	};
}

#endif RT_AARECT_H