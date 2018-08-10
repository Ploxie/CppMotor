#pragma once
#include "FastMath.h"

namespace Math
{
	inline const float ToRadians(const float& angleDegrees)
	{
		return angleDegrees * F_DEG2RAD;
	}

	inline const float ToDegrees(const float& angleRadians)
	{
		return angleRadians * F_RAD2DEG;
	}

	inline const float sin(const float& f)
	{
		return std::sinf(f);
	}

	inline const float cos(const float& f)
	{
		return std::cosf(f);
	}

	inline const float tan(const float& f)
	{
		return sin(f) / cos(f);
	}

	inline const int clamp(const int& value, const int& min, const int& max)
	{
		return value < min ? min : value > max ? max : value;
	}

	inline const float clamp(const float& value, const float& min, const float& max)
	{
		return value < min ? min : value > max ? max : value;
	}

	inline const float min(const float& a, const float& b)
	{
		return (a <= b) ? a : b;
	}

	inline const int min(const int& a, const int& b)
	{
		return (a <= b) ? a : b;
	}

	inline const float max(const float& a, const float& b)
	{
		return (a <= b) ? b : a;
	}

	inline const int max(const int& a, const int& b)
	{
		return (a <= b) ? b : a;
	}

	inline const float lerp(const float& a, const float& b, const float& p)
	{
		return a * (1.0f - p) + b * p;
	}

	inline const float pow(const float& b, const float& e)
	{
		return std::powf(b, e);
	}

	inline const float sqrt(const float& f)
	{
		return std::sqrtf(f);
	}

	inline const float invSqrt(const float& f)
	{
		return (1.0f / std::sqrtf(f));
	}

	inline const float abs(const float& f)
	{
		return f < 0 ? -f : f;
	}

	inline const int abs(const int& i)
	{
		return (i >= 0) ? i : -i;
	}

	inline const int floor(const float& f)
	{
		int i = (int)f;
		return (f < 0 && f != i) ? i - 1 : i;
	}

	inline const int ceil(const float& f)
	{
		return floor(f + 1.0f);
	}

	inline const float acos(const float& f)
	{
		if (-1.0f < f)
		{
			if (f < 1.0f)
			{
				return std::acosf(f);
			}
			return 0.0f;
		}
		return F_PI;
	}

	inline const int round(const float& f)
	{
		return floor(f + 0.5f);
	}

	inline const float atan2(const float& b, const float& a)
	{
		return std::atan2f(b, a);
	}

	inline unsigned int countBitsSet(unsigned int x) {
		x = x - ((x >> 1) & 0x55555555);
		x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
		x = (x + (x >> 4)) & 0x0F0F0F0F;
		x = x + (x >> 8);
		x = x + (x >> 16);
		return x & 0x0000003F;
	}
}