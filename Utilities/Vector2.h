#pragma once
#include <string>
#include <ostream>
#include "Math.h"



namespace Math
{
	template<typename T>
	class Vector2
	{
	public:
		inline Vector2();
		inline Vector2(const T x, const T y);

		inline const T Length() const;
		inline const T LengthSquared() const;

		inline const Vector2<T> GetNormalized() const;
		inline void Normalize();

		inline const T Dot(const Vector2<T>& vector) const;
		
		inline const std::string ToString() const;

		union
		{
			T x;
			T u;
		};

		union
		{
			T y;
			T v;
		};
	};

	template<typename T>
	inline Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}

	template<typename T>
	inline Vector2<T>::Vector2(const T x, const T y)
	{
		this->x = x;
		this->y = y;
	}

	template<typename T>
	inline const T Vector2<T>::Length() const
	{
		return Dot(*this);
	}

	template<typename T>
	inline const T Vector2<T>::LengthSquared() const
	{
		return sqrt(Length());
	}

	template<typename T>
	inline const Vector2<T> Vector2<T>::GetNormalized() const
	{
		const T length = Length();
		Vector2<T> vec = Vector2<T>(*this);		
		vec.x /= length;
		vec.y /= length;
		return vec;
	}

	template<typename T>
	inline void Vector2<T>::Normalize()
	{
		*this = GetNormalized();
	}

	template<typename T>
	inline const T Vector2<T>::Dot(const Vector2<T>& vector) const
	{
		return (x * vector.x) + (y * vector.y);
	}

	template<typename T>
	inline const std::string Vector2<T>::ToString() const
	{
		std::string res = "(";
		res += std::to_string(x) + ", ";
		res += std::to_string(y) + ")";
		return res;
	}

	/*----------------------------------------------------------------------------------------------Operations----------------------------------------------------------------------------------------------*/

	template<typename T>
	inline std::ostream& operator<< (std::ostream& os, const Vector2<T>& vec) {
		return os << vec.ToString();
	}

	template<typename T>
	inline const Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b)
	{
		return Vector2<T>(a.x + b.x, a.y + b.y);
	}

	template<typename T>
	inline const Vector2<T> operator+(const Vector2<T> &a, const T s)
	{
		return Vector2<T>(a.x + s, a.y + s);
	}

	template<typename T>
	inline const Vector2<T>& operator+=(Vector2<T> &a, const Vector2<T> &b)
	{
		a = a + b;
		return a;
	}

	template<typename T>
	inline const Vector2<T>& operator+=(Vector2<T> &a, const T b)
	{
		a = a + b;
		return a;
	}

	template<typename T>
	inline const Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b)
	{
		return Vector2<T>(a.x - b.x, a.y - b.y);
	}

	template<typename T>
	inline const Vector2<T> operator-(const Vector2<T> &a, const T s)
	{
		return Vector2<T>(a.x - s, a.y - s);
	}

	template<typename T>
	inline const Vector2<T>& operator-=(Vector2<T> &a, const Vector2<T> &b)
	{
		a = a - b;
		return a;
	}

	template<typename T>
	inline const Vector2<T>& operator-=(Vector2<T> &a, const T b)
	{
		a = a - b;
		return a;
	}

	template<typename T>
	inline const Vector2<T> operator*(const Vector2<T> &a, const Vector2<T> &b)
	{
		return Vector2<T>(a.x * b.x, a.y * b.y);
	}

	template<typename T>
	inline const Vector2<T> operator*(const Vector2<T> &a, const T s)
	{
		return Vector2<T>(a.x * s, a.y * s);
	}

	template<typename T>
	inline const Vector2<T>& operator*=(Vector2<T> &a, const Vector2<T> &b)
	{
		a = a * b;
		return a;
	}

	template<typename T>
	inline const Vector2<T>& operator*=(Vector2<T> &a, const T b)
	{
		a = a * b;
		return a;
	}

	template<typename T>
	inline const Vector2<T> operator/(const Vector2<T> &a, const Vector2<T> &b)
	{
		return Vector2<T>(a.x / b.x, a.y / b.y);
	}

	template<typename T>
	inline const Vector2<T> operator/(const Vector2<T> &a, const T s)
	{
		return Vector2<T>(a.x / s, a.y / s);
	}
	
	template<typename T>
	inline const Vector2<T>& operator/=(Vector2<T> &a, const Vector2<T> &b)
	{
		a = a / b;
		return a;
	}

	template<typename T>
	inline const Vector2<T>& operator/=(Vector2<T> &a, const T b)
	{
		a = a / b;
		return a;
	}

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2ui;
}



