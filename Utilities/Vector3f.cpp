#include "Vector3f.h"


inline Vector3f::Vector3f()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

inline Vector3f::Vector3f(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline const float Vector3f::Length()
{
	return Dot(*this);
}

inline const float Vector3f::LengthSquared()
{
	return 0.0f;
	//return sqrt(Length());
}

inline const Vector3f Vector3f::GetNormalized() const
{
	return Vector3f();
	//return (*this / LengthSquared());
}

inline void Vector3f::Normalize()
{
	*this = GetNormalized();
}

inline const float Vector3f::Dot(const Vector3f& vector) const
{
	return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

inline const float Vector3f::X() const
{
	return x;
}

inline const float Vector3f::Y() const
{
	return y;
}

inline const float Vector3f::Z() const
{
	return z;
}