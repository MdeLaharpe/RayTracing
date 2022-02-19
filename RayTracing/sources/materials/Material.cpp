#include "materials/Material.h"

namespace rt
{
	maths::Vec3 Material::Emit(float u, float v, const maths::Vec3& point) const
	{
		return { 0.f, 0.f, 0.f };
	}
}