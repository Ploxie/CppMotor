#include "Vector4f.h"



inline Vector4f::Vector4f()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

inline Vector4f::Vector4f(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline const float Vector4f::Length() const
{
	return Dot(*this);
}

inline const float Vector4f::LengthSquared() const
{
	return 0.0f;
	//return sqrt(Length());
}

inline const Vector4f Vector4f::GetNormalized() const
{
	return Vector4f();
	//return (*this / LengthSquared());
}

inline void Vector4f::Normalize()
{
	*this = GetNormalized();
}

inline const float Vector4f::Dot(const Vector4f &vector) const
{
	return (x * vector.x) + (y * vector.y) + (z * vector.z) + (w * vector.w);
}

inline const float Vector4f::X() const
{
	return x;
}

inline const float Vector4f::Y() const
{
	return y;
}

inline const float Vector4f::Z() const
{
	return z;
}

inline const float Vector4f::W() const
{
	return w;
}