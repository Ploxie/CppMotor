#pragma once
#include "Vector2.h"

namespace Math
{
	class Matrix3f
	{
	public:
		inline Matrix3f();

		inline float& operator[](const int index);
		inline float operator[](const int index) const;

		inline void SetTranslation(const Vector3f &translation);
		inline void SetTranslation(const float x, const float y, const float z);
		inline const Vector3f GetTranslation() const;

		inline const Vector3f GetRight() const;
		inline const Vector3f GetUp() const;
		inline const Vector3f GetForward() const;

		inline const Matrix3f GetInverse() const;
		inline const Matrix3f GetTransposed() const;
		inline void Transpose();

		inline void Rotate(const Vector3f& axis, const float rad);

		inline const std::string ToString() const;

	private:
		inline void LoadIdentity();

		float matrix[16];
	};

	inline Matrix3f::Matrix3f()
	{
		LoadIdentity();
	}
	
	inline void Matrix3f::LoadIdentity()
	{
		matrix[0] = 1;	matrix[1] = 0;  matrix[2] = 0; 
		matrix[3] = 0;	matrix[4] = 1;  matrix[5] = 0; 
		matrix[6] = 0;	matrix[7] = 0;	matrix[8] = 1; 
	}

	inline float& Matrix3f::operator[](const int index)
	{
		return matrix[index];
	}

	inline float Matrix3f::operator[](const int index) const
	{
		return matrix[index];
	}

	inline const Vector3f operator*= (const Vector3f &vector, Matrix3f &matrix)
	{
		Vector3f res = Vector3f();
		res.x = vector.Dot(Vector3f(matrix[0], matrix[1], matrix[2]));
		res.y = vector.Dot(Vector3f(matrix[3], matrix[4], matrix[5]));
		res.z = vector.Dot(Vector3f(matrix[6], matrix[7], matrix[8]));
		return res;
	}

	inline const Vector2f operator*= (const Vector2f &vector, Matrix3f &matrix)
	{
		Vector3f res = Vector3f(vector.x, vector.y, 1.0f);
		res *= matrix;
		return Vector2f(res.x, res.y);
	}

	inline const Matrix3f operator* (const Matrix3f &a, const Matrix3f &b)
	{
		Matrix3f m;
		m[0] = (a[0] * b[0]) + (a[1] * b[3]) + (a[2] * b[6]);
		m[1] = (a[0] * b[1]) + (a[1] * b[4]) + (a[2] * b[7]);
		m[2] = (a[0] * b[2]) + (a[1] * b[5]) + (a[2] * b[8]);

		m[3] = (a[3] * b[0]) + (a[4] * b[3]) + (a[5] * b[6]);
		m[4] = (a[3] * b[1]) + (a[4] * b[4]) + (a[5] * b[7]);
		m[5] = (a[3] * b[2]) + (a[4] * b[5]) + (a[5] * b[8]);

		m[6] = (a[6] * b[0]) + (a[7] * b[3]) + (a[8] * b[6]);
		m[7] = (a[6] * b[1]) + (a[7] * b[4]) + (a[8] * b[7]);
		m[8] = (a[6] * b[2]) + (a[7] * b[5]) + (a[8] * b[8]);
		return m;
	}

	inline const Matrix3f operator*= (Matrix3f &a, const Matrix3f &b)
	{
		a = a * b;
		return a;
	}

	inline void Matrix3f::SetTranslation(const Vector3f &translation)
	{
		SetTranslation(translation.x, translation.y, translation.z);
	}

	inline void Matrix3f::SetTranslation(const float x, const float y, const float z)
	{
		matrix[6] = x;
		matrix[7] = y;
		matrix[8] = z;
	}

	inline const Vector3f Matrix3f::GetTranslation() const
	{
		return Vector3f(matrix[6], matrix[7], matrix[8]);
	}

	inline const Vector3f Matrix3f::GetRight() const
	{
		return Vector3f(matrix[0], matrix[1], matrix[2]);
	}

	inline const Vector3f Matrix3f::GetUp() const
	{
		return Vector3f(matrix[3], matrix[4], matrix[5]);
	}
	inline const Vector3f Matrix3f::GetForward() const
	{
		return Vector3f(matrix[6], matrix[7], matrix[8]);
	}

	//MIGHT NOT WORK
	inline const Matrix3f Matrix3f::GetInverse() const
	{
		Matrix3f temp(*this);
		Vector3f translation = temp.GetTranslation();
		temp.SetTranslation(0.f, 0.f, 0.f);
		translation *= -1.f;
		translation.z = 1.f;
		temp.Transpose();
		translation *= temp;
		temp.SetTranslation(translation);
		return temp;
	}

	inline const Matrix3f Matrix3f::GetTransposed() const
	{
		Matrix3f tmp(*this);
		Matrix3f res;
		res[0] = tmp[0]; res[1] = tmp[3]; res[2] = tmp[6];
		res[3] = tmp[1]; res[4] = tmp[4]; res[5] = tmp[7]; 
		res[6] = tmp[2]; res[7] = tmp[5]; res[8] = tmp[8];
		return res;
	}

	inline void Matrix3f::Transpose()
	{
		*this = GetTransposed();
	}

	// MIGHT WANT TO FIX
	inline void Matrix3f::Rotate(const Vector3f& axis, const float rad)
	{
		float xRad = axis.x * rad;
		Matrix3f mx;
		mx[4] =  cos(xRad);
		mx[5] =  sin(xRad);
		mx[7] = -sin(xRad);
		mx[8] =  cos(xRad);

		float yRad = axis.y * rad;
		Matrix3f my;
		my[0] =  cos(yRad);
		my[2] =  -sin(yRad);
		my[6] =  sin(yRad);
		my[8] =  cos(yRad);

		float zRad = axis.z * rad;
		Matrix3f mz;
		mz[0] =  cos(zRad);
		mz[1] =  sin(zRad);
		mz[3] = -sin(zRad);
		mz[4] =  cos(zRad);

		*this *= mx * my * mz;
	}

	inline const std::string Matrix3f::ToString() const
	{
		std::string res = "(";
		res += std::to_string(matrix[0]) + ", " + std::to_string(matrix[1]) + ", " + std::to_string(matrix[2]) + "\n ";
		res += std::to_string(matrix[3]) + ", " + std::to_string(matrix[4]) + ", " + std::to_string(matrix[5]) + "\n ";
		res += std::to_string(matrix[6]) + ", " + std::to_string(matrix[7]) + ", " + std::to_string(matrix[8]) + ")";
		return res;
	}

	/*----------------------------------------------Operations---------------------------------------------------*/

	inline std::ostream& operator<< (std::ostream& os, const Matrix3f& matrix) {
		return os << matrix.ToString();
	}

	inline const bool operator== (Matrix3f &a, Matrix3f &b)
	{
		for (unsigned int i = 0; i < 9; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}

	
}