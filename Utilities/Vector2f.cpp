
#include "Vector2f.h"

Vector2f::Vector2f()
{
	x = 0;
	y = 0;
}

inline Vector2f::Vector2f(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

inline const float Vector2f::Length()
{
	return Dot(*this);
}

inline const float Vector2f::LengthSquared()
{
	return 0.0f;
	//return sqrt(Length());
}

inline const Vector2f& Vector2f::GetNormalized() const
{
	return Vector2f();
	//return (*this / LengthSquared());
}

inline void Vector2f::Normalize() 
{
	*this = GetNormalized();
}

inline const float Vector2f::Dot(const Vector2f& vector)
{
	return (x * vector.x) + (y * vector.y);
}

inline const float Vector2f::X() const
{
	return x;
}

inline const float Vector2f::Y() const
{
	return y;
}