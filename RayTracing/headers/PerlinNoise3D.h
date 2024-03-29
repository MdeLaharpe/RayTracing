#ifndef RT_PERLINNOISE_H
#define RT_PERLINNOISE_H

#include <array>

#include "maths/Vec3.h"

namespace rt
{
	template<size_t size>
	class PerlinNoise3D
	{
	public:
		PerlinNoise3D();
		~PerlinNoise3D() = default;

		float Sample(const maths::Vec3& point) const;
		float Sample(const maths::Vec3& point, size_t turbulenceDepth) const;

	private:
		static constexpr size_t volume = size * size * size;

		std::array<maths::Vec3, volume> values;
		std::array<int32_t, volume> permX;
		std::array<int32_t, volume> permY;
		std::array<int32_t, volume> permZ;

		static void GeneratePermutation(std::array<int32_t, volume>& perm);
	};

}

#endif RT_PERLINNOISE_H