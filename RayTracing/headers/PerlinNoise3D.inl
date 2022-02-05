#include "Random.h"

namespace rt
{
	template<size_t size>
	PerlinNoise3D<size>::PerlinNoise3D()
	{
		for (size_t i = 0; i < volume; i++)
			values[i] = Rand01();

		GeneratePermutation(permX);
		GeneratePermutation(permY);
		GeneratePermutation(permZ);
	}

	template<size_t size>
	void PerlinNoise3D<size>::GeneratePermutation(std::array<int32_t, volume>& perm)
	{
		for (int32_t i = 0; i < volume; i++)
			perm[i] = i;

		for (int32_t i = volume - 1; i > 0; i--)
		{
			size_t targetIndex = Rand(0, i);
			int32_t tmp = perm[i];
			perm[i] = perm[targetIndex];
			perm[targetIndex] = tmp;
		}
	}

	template<size_t size>
	float PerlinNoise3D<size>::Sample(const maths::Vec3& point) const
	{
		size_t i = static_cast<size_t>(4 * point.x) & 255;
		size_t j = static_cast<size_t>(4 * point.y) & 255;
		size_t k = static_cast<size_t>(4 * point.z) & 255;

		return values[permX[i] ^ permY[j] ^ permZ[k]];
	}
}