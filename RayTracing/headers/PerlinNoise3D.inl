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
		float u = point.x - std::floor(point.x);
		float v = point.y - std::floor(point.y);
		float w = point.z - std::floor(point.z);

		size_t i = static_cast<size_t>(std::floor(point.x));
		size_t j = static_cast<size_t>(std::floor(point.y));
		size_t k = static_cast<size_t>(std::floor(point.z));

		float c[2][2][2];

		for (size_t di = 0; di < 2; di++)
			for (size_t dj = 0; dj < 2; dj++)
				for (size_t dk = 0; dk < 2; dk++)
					c[di][dj][dk] = values[
						permX[(i + di) & 255] ^
						permY[(j + dj) & 255] ^
						permZ[(k + dk) & 255]
					];

		float acc = 0.f;
		for (size_t ii = 0; ii < 2; ii++)
			for (size_t jj = 0; jj < 2; jj++)
				for (size_t kk = 0; kk < 2; kk++)
					acc +=
						(ii * u + (1.f - ii) * (1.f - u)) *
						(jj * v + (1.f - jj) * (1.f - v)) *
						(kk * w + (1.f - kk) * (1.f - w)) *
						c[ii][jj][kk]
					;

		return acc;
	}
}