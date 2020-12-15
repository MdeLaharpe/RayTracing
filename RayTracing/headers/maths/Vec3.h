#ifndef MATHS_VEC3_H
#define MATHS_VEC3_H

#include <cmath>
#include <ostream>

namespace maths
{
	struct Vec3
	{
		constexpr Vec3() : val{ 0.f, 0.f, 0.f } { };
		constexpr Vec3(float f) : val{ f, f, f } { };
		constexpr Vec3(float x, float y, float z) : val{ x, y, z } { };

		Vec3(const Vec3& v) = default;
		Vec3(Vec3&& v) = default;

		~Vec3() = default;

		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			float val[3];
		};

		Vec3& operator =(const Vec3& v) = default;
		Vec3& operator =(Vec3&& v) = default;

		inline float operator [](size_t i) const { return val[i]; }
		inline float& operator [](size_t i) { return val[i]; }

		inline Vec3 operator -() const
		{
			return Vec3(-x, -y, -z);
		}

		inline Vec3& operator *=(const float f)
		{
			x *= f;
			y *= f;
			z *= f;

			return *this;
		}
		inline Vec3& operator /=(const float f)
		{
			*this *= (1.f / f);

			return *this;
		}

		inline Vec3& operator +=(const Vec3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}
		inline Vec3& operator -=(const Vec3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		inline float MagnitudeSquared() const
		{
			return x * x + y * y + z * z;
		}
		inline float Magnitude() const
		{
			return std::sqrtf(MagnitudeSquared());
		}

		inline void Apply(float (*func)(float))
		{
			x = func(x);
			y = func(y);
			z = func(z);
		}
	};

	inline Vec3 operator *(const Vec3& v, const float f)
	{
		return Vec3(v.x * f, v.y * f, v.z * f);
	}
	inline Vec3 operator *(const float f, const Vec3& v)
	{
		return v * f;
	}
	inline Vec3 operator /(const Vec3& v, const float f)
	{
		return v * (1.f / f);
	}

	inline Vec3 operator +(const Vec3& l, const Vec3& r)
	{
		return Vec3(l.x + r.x, l.y + r.y, l.z + r.z);
	}
	inline Vec3 operator -(const Vec3& l, const Vec3& r)
	{
		return Vec3(l.x - r.x, l.y - r.y, l.z - r.z);
	}
	inline Vec3 operator *(const Vec3& l, const Vec3& r)
	{
		return Vec3(l.x * r.x, l.y * r.y, l.z * r.z);
	}
	inline Vec3 operator /(const Vec3& l, const Vec3& r)
	{
		return Vec3(l.x / r.x, l.y / r.y, l.z / r.z);
	}

	inline Vec3 Normalized(const Vec3& v)
	{
		return v * (1.f / v.Magnitude());
	}
	inline float Dot(const Vec3& l, const Vec3& r)
	{
		return l.x * r.x + l.y * r.y + l.z * r.z;
	}
	inline Vec3 Cross(const Vec3& l, const Vec3& r)
	{
		return Vec3(
			l.y * r.z - l.z * r.y,
			l.z * r.x - l.x * r.z,
			l.x * r.y - l.y * r.x
		);
	}
	inline Vec3 Reflected(const Vec3& v, const Vec3& normal)
	{
		return v - 2.f * Dot(v, normal) * normal;
	}
	inline Vec3 Refract(const Vec3& v, const Vec3& normal, float refIndicesRatio)
	{
		float cosTheta = std::min(maths::Dot(-v, normal), 1.f);
		maths::Vec3 outPerp = refIndicesRatio * (v + cosTheta * normal);
		maths::Vec3 outPara = -std::sqrtf(std::fabs(1.f - outPerp.MagnitudeSquared())) * normal;
		return outPerp + outPara;
	}

	inline std::ostream& operator <<(std::ostream& out, const Vec3& v)
	{
		return out << v.x << ' ' << v.y << ' ' << v.z;
	}
}

#endif MATHS_VEC3_H