#ifndef RT_DIFFUSELIGHT_H
#define RT_DIFFUSELIGHT_H

#include "materials/Material.h"

#include "textures/Texture.h"
#include "textures/SolidColorTexture.h"

namespace rt
{
	class DiffuseLight : public Material
	{
	public:
		DiffuseLight() : emissive(std::make_shared<SolidColorTexture>(maths::Vec3{ 1.f, 1.f, 1.f })) { }
		DiffuseLight(std::shared_ptr<Texture> emissive) : emissive(std::move(emissive)) { }

		virtual bool Scatter(const maths::Ray& rayIn, const HitRecord& rec, maths::Vec3& attenuation, maths::Ray& scattered) const override;

		virtual maths::Vec3 Emit(float u, float v, const maths::Vec3& point) const override;

	private:
		std::shared_ptr<Texture> emissive;
	};
}

#endif RT_DIFFUSELIGHT_H