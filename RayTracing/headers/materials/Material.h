#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include "maths/Ray.h"
#include "hittables/Hittable.h"

namespace rt
{
	class Material
	{
	public:
		virtual ~Material() { }

		virtual bool Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const = 0;

		virtual maths::Vec3 Emit(float u, float v, const maths::Vec3& point) const;
	};
}

#endif RT_MATERIAL_H