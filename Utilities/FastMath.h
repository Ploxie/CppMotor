#pragma once
#include <cmath>

namespace Math
{
	const float F_PI = 3.141592653589793f;
	const float F_DEG2RAD = F_PI / 180.0f;
	const float F_RAD2DEG = 180.0f / F_PI;
	const float F_EPSILON = 0.00001f;

	inline const float ToRadians(const float& angleDegrees);

	inline const float ToDegrees(const float& angleRadians);

	inline const float sin(const float& f);

	inline const float cos(const float& f);

	inline const float tan(const float& f);

	inline const int clamp(const int& value, const int& min, const int& max);

	inline const float clamp(const float& value, const float& min, const float& max);
	
	inline const float lerp(const float& a, const float& b, const float& p);

	inline const float pow(const float& b, const float& e);

	inline const float sqrt(const float& f);

	inline const float invSqrt(const float& f);

	inline const float abs(const float& f);

	inline const int abs(const int& i);

	inline const int floor(const float& f);

	inline const int ceil(const float& f);

	inline const float acos(const float& f);

	inline const int round(const float& f);

	inline const float atan2(const float& b, const float& a);

	inline unsigned int countBitsSet(unsigned int x);
}