#pragma once
#include <string>
#include <ostream>
#include "FastMath.h"

namespace Math
{
	template<typename T>
	class Vector4
	{
	public:
		inline Vector4<T>();
		inline Vector4<T>(const T x, const T y, const T z, const T w);

		inline const T Length() const;
		inline const T LengthSquared() const;

		inline const Vector4<T> GetNormalized() const;
		inline void Normalize();

		inline const T Dot(const Vector4<T> &vector) const;

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

		union
		{
			T w;
			T a;
		};
	};

	template<typename T>
	inline Vector4<T>::Vector4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	template<typename T>
	inline Vector4<T>::Vector4(const T x, const T y, const T z, const T w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	template<typename T>
	inline const T Vector4<T>::Length() const
	{
		return Dot(*this);
	}

	template<typename T>
	inline const T Vector4<T>::LengthSquared() const
	{
		return sqrt(Length());
	}

	template<typename T>
	inline const Vector4<T> Vector4<T>::GetNormalized() const
	{
		const T length = Length();
		Vector4<T> vec = Vector4<T>(*this);
		vec.x /= length;
		vec.y /= length;
		vec.z /= length;
		vec.w /= length;
		return vec;
	}

	template<typename T>
	inline void Vector4<T>::Normalize()
	{
		*this = GetNormalized();
	}

	template<typename T>
	inline const T Vector4<T>::Dot(const Vector4<T> &vector) const
	{
		return (x * vector.x) + (y * vector.y) + (z * vector.z) + (w * vector.w);
	}
	
	template<typename T>
	inline const std::string Vector4<T>::ToString() const
	{
		std::string res = "(";
		res += std::to_string(x) + ", ";
		res += std::to_string(y) + ", ";
		res += std::to_string(z) + ", ";
		res += std::to_string(w) + ")";
		return res;
	}

	/*----------------------------------------------------------------------------------------------Operations----------------------------------------------------------------------------------------------*/

	template<typename T>
	inline std::ostream& operator<< (std::ostream& os, const Vector4<T>& vec) {
		return os << vec.ToString();
	}

	template<typename T>
	inline const Vector4<T> operator+(const Vector4<T> &a, const Vector4<T> &b)
	{
		return Vector4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	template<typename T>
	inline const Vector4<T> operator+(const Vector4<T> &a, const T s)
	{
		return Vector4<T>(a.x + s, a.y + s, a.z + s, a.w + s);
	}

	template<typename T>
	inline const Vector4<T>& operator+=(Vector4<T> &a, const Vector4<T> &b)
	{
		a = a + b;
		return a;
	}

	template<typename T>
	inline const Vector4<T>& operator+=(Vector4<T> &a, const T b)
	{
		a = a + b;
		return a;
	}

	template<typename T>
	inline const Vector4<T> operator-(const Vector4<T> &a, const Vector4<T> &b)
	{
		return Vector4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	template<typename T>
	inline const Vector4<T> operator-(const Vector4<T> &a, const T s)
	{
		return Vector4<T>(a.x - s, a.y - s, a.z - s, a.w - s);
	}

	template<typename T>
	inline const Vector4<T>& operator-=(Vector4<T> &a, const Vector4<T> &b)
	{
		a = a - b;
		return a;
	}

	template<typename T>
	inline const Vector4<T>& operator-=(Vector4<T> &a, const T b)
	{
		a = a - b;
		return a;
	}

	template<typename T>
	inline const Vector4<T> operator*(const Vector4<T> &a, const Vector4<T> &b)
	{
		return Vector4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	template<typename T>
	inline const Vector4<T> operator*(const Vector4<T> &a, const T s)
	{
		return Vector4<T>(a.x * s, a.y * s, a.z * s, a.w * s);
	}

	template<typename T>
	inline const Vector4<T>& operator*=(Vector4<T> &a, const Vector4<T> &b)
	{
		a = a * b;
		return a;
	}

	template<typename T>
	inline const Vector4<T>& operator*=(Vector4<T> &a, const T b)
	{
		a = a * b;
		return a;
	}

	template<typename T>
	inline const Vector4<T> operator/(const Vector4<T> &a, const Vector4<T> &b)
	{
		return Vector4<T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	template<typename T>
	inline const Vector4<T> operator/(const Vector4<T> &a, const T s)
	{
		return Vector4<T>(a.x / s, a.y / s, a.z / s, a.w / s);
	}

	template<typename T>
	inline const Vector4<T>& operator/=(Vector4<T> &a, const Vector4<T> &b)
	{
		a = a / b;
		return a;
	}

	template<typename T>
	inline const Vector4<T>& operator/=(Vector4<T> &a, const T b)
	{
		a = a / b;
		return a;
	}

	typedef Vector4<float> Vector4f;
	typedef Vector4<int> Vector4i;
	typedef Vector4<unsigned int> Vector4ui;
}