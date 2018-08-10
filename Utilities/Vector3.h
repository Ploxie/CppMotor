#pragma once
#include <string>
#include <ostream>
#include "FastMath.h"

namespace Math
{
	template<typename T>
	class Vector3
	{
	public:
		inline Vector3<T>();
		inline Vector3<T>(const T x, const T y, const T z);

		inline const T Length() const;
		inline const T LengthSquared() const;

		inline const Vector3<T> GetNormalized() const;
		inline void Normalize();

		inline const T Dot(const Vector3<T>& vector) const;
		
		inline const std::string ToString() const;

		union
		{
			T x;
			T r;
		};

		union
		{
			T y;
			T g;
		};

		union
		{
			T z;
			T b;
		};

	};

	template<typename T>
	inline Vector3<T>::Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	template<typename T>
	inline Vector3<T>::Vector3(const T x, const T y, const T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	template<typename T>
	inline const T Vector3<T>::Length() const
	{
		return Dot(*this);
	}

	template<typename T>
	inline const T Vector3<T>::LengthSquared() const
	{
		return sqrt(Length());
	}

	template<typename T>
	inline const Vector3<T> Vector3<T>::GetNormalized() const
	{
		const T length = Length();
		Vector3<T> vec = Vector3<T>(*this);
		vec.x /= length;
		vec.y /= length;
		vec.z /= length;
		return vec;
	}

	template<typename T>
	inline void Vector3<T>::Normalize()
	{
		*this = GetNormalized();
	}

	template<typename T>
	inline const T Vector3<T>::Dot(const Vector3<T>& vector) const
	{
		return (x * vector.x) + (y * vector.y) + (z * vector.z);
	}

	template<typename T>
	inline const std::string Vector3<T>::ToString() const
	{
		std::string res = "(";
		res += std::to_string(x) + ", ";
		res += std::to_string(y) + ", ";
		res += std::to_string(z) + ")";
		return res;
	}

	/*----------------------------------------------------------------------------------------------Operations----------------------------------------------------------------------------------------------*/

	template<typename T>
	inline std::ostream& operator<< (std::ostream& os, const Vector3<T>& vec) {
		return os << vec.ToString();
	}

	template<typename T>
	inline const Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b)
	{
		return Vector3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	template<typename T>
	inline const Vector3<T> operator+(const Vector3<T> &a, const T s)
	{
		return Vector3<T>(a.x + s, a.y + s, a.z + s);
	}

	template<typename T>
	inline const Vector3<T>& operator+=(Vector3<T> &a, const Vector3<T> &b)
	{
		a = a + b;
		return a;
	}

	template<typename T>
	inline const Vector3<T>& operator+=(Vector3<T> &a, const T b)
	{
		a = a + b;
		return a;
	}

	template<typename T>
	inline const Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b)
	{
		return Vector3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	template<typename T>
	inline const Vector3<T> operator-(const Vector3<T> &a, const T s)
	{
		return Vector3<T>(a.x - s, a.y - s, a.z - s);
	}

	template<typename T>
	inline const Vector3<T>& operator-=(Vector3<T> &a, const Vector3<T> &b)
	{
		a = a - b;
		return a;
	}

	template<typename T>
	inline const Vector3<T>& operator-=(Vector3<T> &a, const T b)
	{
		a = a - b;
		return a;
	}

	template<typename T>
	inline const Vector3<T> operator*(const Vector3<T> &a, const Vector3<T> &b)
	{
		return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	template<typename T>
	inline const Vector3<T> operator*(const Vector3<T> &a, const T s)
	{
		return Vector3<T>(a.x * s, a.y * s, a.z * s);
	}

	template<typename T>
	inline const Vector3<T>& operator*=(Vector3<T> &a, const Vector3<T> &b)
	{
		a = a * b;
		return a;
	}

	template<typename T>
	inline const Vector3<T>& operator*=(Vector3<T> &a, const T b)
	{
		a = a * b;
		return a;
	}

	template<typename T>
	inline const Vector3<T> operator/(const Vector3<T> &a, const Vector3<T> &b)
	{
		return Vector3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	template<typename T>
	inline const Vector3<T> operator/(const Vector3<T> &a, const T s)
	{
		return Vector3<T>(a.x / s, a.y / s, a.z / s);
	}

	template<typename T>
	inline const Vector3<T>& operator/=(Vector3<T> &a, const Vector3<T> &b)
	{
		a = a / b;
		return a;
	}

	template<typename T>
	inline const Vector3<T>& operator/=(Vector3<T> &a, const T b)
	{
		a = a / b;
		return a;
	}

	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3ui;
}