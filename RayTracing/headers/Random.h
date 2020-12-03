#ifndef RT_RANDOM_H
#define RT_RANDOM_H

#include <random>

#include "maths/Vec3.h"

namespace rt
{
	class Random
	{
	public:
		Random();

		float Rand01();
		maths::Vec3 RandInUnitSphere();

	private:
		std::random_device randDevice;
		std::default_random_engine randEngine;// (randDevice());
		std::uniform_real_distribution<float> randDistribution; // (0.f, 1.f);
	};
}

#endif RT_RANDOM_H