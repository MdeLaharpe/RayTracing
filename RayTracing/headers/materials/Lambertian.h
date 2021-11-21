#ifndef RT_LAMBERTIAN_H
#define RT_LAMBERTIAN_H

#include "materials/Material.h"

#include <memory>

#include "maths/Vec3.h"
#include "textures/Texture.h"
#include "textures/SolidColor.h"

namespace rt
{
	class Lambertian : public Material
	{
	public:
		Lambertian() : albedo(std::make_shared<SolidColor>()) { }
		Lambertian(const maths::Vec3& albedo) : albedo(std::make_shared<SolidColor>(albedo)) { }
		Lambertian(std::shared_ptr<Texture> albedo) : albedo(std::move(albedo)) { }

		virtual bool Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const override;

	private:
		std::shared_ptr<Texture> albedo;
	};
}

#endif RT_LAMBERTIAN_H