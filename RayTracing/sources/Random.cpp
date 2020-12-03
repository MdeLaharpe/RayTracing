#include "Random.h"

namespace rt
{
	std::random_device randDevice;
	std::default_random_engine randEngine(randDevice());
	std::uniform_real_distribution<float> randDistribution(0.f, 1.f);

	float Rand01()
	{
		return randDistribution(randEngine);
	}

	maths::Vec3 RandInUnitSphere()
	{
		maths::Vec3 point;
		do { point = 2.f * maths::Vec3(Rand01(), Rand01(), Rand01()) - maths::Vec3(-1.f); }
		while( point.MagnitudeSquared() > 1.f);
		return point;
	}
}