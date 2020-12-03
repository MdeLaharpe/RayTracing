#include "Random.h"

namespace rt
{
	Random::Random()
		: randDevice(),
		randEngine(randDevice()),
		randDistribution(0.f, 1.f)
	{ }

	float Random::Rand01()
	{
		return randDistribution(randEngine);
	}

	maths::Vec3 Random::RandInUnitSphere()
	{
		maths::Vec3 point;
		do { point = 2.f * maths::Vec3(Rand01(), Rand01(), Rand01()) - maths::Vec3(-1.f); }
		while( point.MagnitudeSquared() > 1.f);
		return point;
	}
}