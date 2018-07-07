#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3f.h"

namespace Math
{
	class Matrix4f
	{

	public:
		inline Matrix4f();
		inline Matrix4f(const Matrix3f& matrix);

		inline float& operator[](const int index);
		inline float operator[](const int index) const;

		inline const Matrix3f ToRotationMatrix() const;

		inline void SetTranslation(const Vector4f &translation);
		inline void SetTranslation(const float x, const float y, const float z, const float w);
		inline void SetTranslation(const Vector3f &translation);
		inline void SetTranslation(const float x, const float y, const float z);
		inline const Vector4f GetTranslation() const;

		inline const Vector4f GetRight() const;
		inline const Vector4f GetUp() const;
		inline const Vector4f GetForward() const;

		inline void SetScale(const Vector3f& scale);
		inline const Vector3f GetScale() const;

		inline const Matrix4f GetInverse() const;
		inline const Matrix4f GetTransposed() const;
		inline void Invert();
		inline void Transpose();

		inline void Rotate(const Vector3f& axis, const float rad);

		inline const std::string ToString() const;

	private:
		inline void LoadIdentity();

		float matrix[16];

	};

	inline Matrix4f::Matrix4f()
	{
		LoadIdentity();
	}

	inline Matrix4f::Matrix4f(const Matrix3f& matrix)
	{
		LoadIdentity();
		this->matrix[0]  = matrix[0];
		this->matrix[1]  = matrix[1];
		this->matrix[2]  = matrix[2];

		this->matrix[4]  = matrix[3];
		this->matrix[5]  = matrix[4];
		this->matrix[6]  = matrix[5];

		this->matrix[8]  = matrix[6];
		this->matrix[9]  = matrix[7];
		this->matrix[10] = matrix[8];
	}
	
	inline void Matrix4f::LoadIdentity()
	{
		matrix[0]  = 1;	matrix[1]  = 0; matrix[2]  = 0; matrix[3]  = 0;
		matrix[4]  = 0;	matrix[5]  = 1; matrix[6]  = 0; matrix[7]  = 0;
		matrix[8]  = 0;	matrix[9]  = 0;	matrix[10] = 1; matrix[11] = 0;
		matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
	}

	inline float& Matrix4f::operator[](const int index)
	{
		return matrix[index];
	}

	inline float Matrix4f::operator[](const int index) const
	{
		return matrix[index];
	}

	inline const Matrix3f Matrix4f::ToRotationMatrix() const
	{
		Matrix3f res;
		res[0] = matrix[0];
		res[1] = matrix[1];
		res[2] = matrix[2];
		res[3] = matrix[4];
		res[4] = matrix[5];
		res[5] = matrix[6];
		res[6] = matrix[8];
		res[7] = matrix[9];
		res[8] = matrix[10];
		return res;
	}

	inline const Vector4f operator*= (const Vector4f &vector, Matrix4f &matrix)
	{
		Vector4f res = Vector4f();
		res.x = vector.Dot(Vector4f(matrix[0], matrix[1], matrix[2], matrix[3]));
		res.y = vector.Dot(Vector4f(matrix[4], matrix[5], matrix[6], matrix[7]));
		res.z = vector.Dot(Vector4f(matrix[8], matrix[9], matrix[10], matrix[11]));
		res.w = vector.Dot(Vector4f(matrix[12], matrix[13], matrix[14], matrix[15]));
		return res;
	}

	inline void Matrix4f::SetTranslation(const Vector4f &translation)
	{
		SetTranslation(translation.x, translation.y, translation.z, translation.w);
	}

	inline void Matrix4f::SetTranslation(const float x, const float y, const float z, const float w)
	{
		matrix[12] = x;
		matrix[13] = y;
		matrix[14] = z;
		matrix[15] = w;
	}

	inline void Matrix4f::SetTranslation(const Vector3f &translation)
	{
		SetTranslation(translation.x, translation.y, translation.z);
	}

	inline void Matrix4f::SetTranslation(const float x, const float y, const float z)
	{
		matrix[12] = x;
		matrix[13] = y;
		matrix[14] = z;
	}

	inline const Vector4f Matrix4f::GetTranslation() const
	{
		return Vector4f(matrix[12], matrix[13], matrix[14], matrix[15]);
	}

	inline const Vector4f Matrix4f::GetRight() const
	{
		return Vector4f(matrix[0], matrix[1], matrix[2], matrix[3]);
	}

	inline const Vector4f Matrix4f::GetUp() const
	{
		return Vector4f(matrix[4], matrix[5], matrix[6], matrix[7]);
	}
	inline const Vector4f Matrix4f::GetForward() const
	{
		return Vector4f(matrix[8], matrix[9], matrix[10], matrix[11]);
	}
	
	inline void Matrix4f::SetScale(const Vector3f& scale)
	{
		matrix[0] = scale.x;
		matrix[5] = scale.y;
		matrix[10] = scale.z;
	}

	inline const Vector3f Matrix4f::GetScale() const
	{
		return Vector3f(matrix[0], matrix[5], matrix[10]);
	}

	inline const Matrix4f Matrix4f::GetInverse() const
	{
		float fA0 = matrix[0]  * matrix[5] - matrix[1] * matrix[4];
		float fA1 = matrix[0]  * matrix[6]  - matrix[2]  * matrix[4];
		float fA2 = matrix[0]  * matrix[7]  - matrix[3]  * matrix[4];
		float fA3 = matrix[1]  * matrix[6]  - matrix[2]  * matrix[5];
		float fA4 = matrix[1]  * matrix[7]  - matrix[3]  * matrix[5];
		float fA5 = matrix[2]  * matrix[7]  - matrix[3]  * matrix[6];
		float fB0 = matrix[8]  * matrix[13] - matrix[9]  * matrix[12];
		float fB1 = matrix[8]  * matrix[14] - matrix[10] * matrix[12];
		float fB2 = matrix[8]  * matrix[15] - matrix[11] * matrix[12];
		float fB3 = matrix[9]  * matrix[14] - matrix[10] * matrix[13];
		float fB4 = matrix[9]  * matrix[15] - matrix[11] * matrix[13];
		float fB5 = matrix[10] * matrix[15] - matrix[11] * matrix[14];
		float fDet = fA0 * fB5 - fA1 * fB4 + fA2 * fB3 + fA3 * fB2 - fA4 * fB1 + fA5 * fB0;

		if (abs(fDet) <= F_EPSILON) {
			return Matrix4f();
		}

		float f00 = +matrix[5]  * fB5 - matrix[6]  * fB4 + matrix[7]  * fB3;
		float f10 = -matrix[4]  * fB5 + matrix[6]  * fB2 - matrix[7]  * fB1;
		float f20 = +matrix[4]  * fB4 - matrix[5]  * fB2 + matrix[7]  * fB0;
		float f30 = -matrix[4]  * fB3 + matrix[5]  * fB1 - matrix[6]  * fB0;
		float f01 = -matrix[1]  * fB5 + matrix[2]  * fB4 - matrix[3]  * fB3;
		float f11 = +matrix[0]  * fB5 - matrix[2]  * fB2 + matrix[3]  * fB1;
		float f21 = -matrix[0]  * fB4 + matrix[1]  * fB2 - matrix[3]  * fB0;
		float f31 = +matrix[0]  * fB3 - matrix[1]  * fB1 + matrix[2]  * fB0;
		float f02 = +matrix[13] * fA5 - matrix[14] * fA4 + matrix[15] * fA3;
		float f12 = -matrix[12] * fA5 + matrix[14] * fA2 - matrix[15] * fA1;
		float f22 = +matrix[12] * fA4 - matrix[13] * fA2 + matrix[15] * fA0;
		float f32 = -matrix[12] * fA3 + matrix[13] * fA1 - matrix[14] * fA0;
		float f03 = -matrix[9]  * fA5 + matrix[10] * fA4 - matrix[11] * fA3;
		float f13 = +matrix[8]  * fA5 - matrix[10] * fA2 + matrix[11] * fA1;
		float f23 = -matrix[8]  * fA4 + matrix[9]  * fA2 - matrix[11] * fA0;
		float f33 = +matrix[8]  * fA3 - matrix[9]  * fA1 + matrix[10] * fA0;

		float fInvDet = 1.0f / fDet;
		Matrix4f matrix;
		matrix[0]  = f00 * fInvDet;
		matrix[1]  = f01 * fInvDet;
		matrix[2]  = f02 * fInvDet;
		matrix[3]  = f03 * fInvDet;
		matrix[4]  = f10 * fInvDet;
		matrix[5]  = f11 * fInvDet;
		matrix[6]  = f12 * fInvDet;
		matrix[7]  = f13 * fInvDet;
		matrix[8]  = f20 * fInvDet;
		matrix[9]  = f21 * fInvDet;
		matrix[10] = f22 * fInvDet;
		matrix[11] = f23 * fInvDet;
		matrix[12] = f30 * fInvDet;
		matrix[13] = f31 * fInvDet;
		matrix[14] = f32 * fInvDet;
		matrix[15] = f33 * fInvDet;

		return matrix;
	}

	inline const Matrix4f Matrix4f::GetTransposed() const
	{
		Matrix4f tmp(*this);
		Matrix4f res;
		res[0] =  tmp[0]; res[1] =  tmp[4];  res[2] =  tmp[8];  res[3] =  tmp[12];
		res[4] =  tmp[1]; res[5] =  tmp[5];  res[6] =  tmp[9];  res[7] =  tmp[13];
		res[8] =  tmp[2]; res[9] =  tmp[6];  res[10] = tmp[10]; res[11] = tmp[14];
		res[12] = tmp[3]; res[13] = tmp[7];  res[14] = tmp[11];  res[15] = tmp[15];
		return res;
	}

	inline void Matrix4f::Invert()
	{
		*this = GetInverse();
	}

	inline void Matrix4f::Transpose()
	{
		*this = GetTransposed();
	}

	inline void Matrix4f::Rotate(const Vector3f& axis, const float rad)
	{
		Matrix3f rotation = ToRotationMatrix();
		rotation.Rotate(axis, rad);
		*this = Matrix4f(rotation);
	}

	inline const std::string Matrix4f::ToString() const
	{
		std::string res = "(";
		res += std::to_string(matrix[0]) + ", " + std::to_string(matrix[1]) + ", " + std::to_string(matrix[2]) + ", " + std::to_string(matrix[3]) + "\n ";
		res += std::to_string(matrix[4]) + ", " + std::to_string(matrix[5]) + ", " + std::to_string(matrix[6]) + ", " + std::to_string(matrix[7]) + "\n ";
		res += std::to_string(matrix[8]) + ", " + std::to_string(matrix[9]) + ", " + std::to_string(matrix[10]) + ", " + std::to_string(matrix[11]) + "\n ";
		res += std::to_string(matrix[12]) + ", " + std::to_string(matrix[13]) + ", " + std::to_string(matrix[14]) + ", " + std::to_string(matrix[15]) + ")";
		return res;
	}

	/*----------------------------------------------Operations---------------------------------------------------*/

	inline std::ostream& operator<< (std::ostream& os, const Matrix4f& matrix) {
		return os << matrix.ToString();
	}

	inline const bool operator== (Matrix4f &a, Matrix4f &b)
	{
		for (unsigned int i = 0; i < 16; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}

	inline const Matrix4f operator* (const Matrix4f &a, const Matrix4f &b)
	{
		Matrix4f m;
		m[0] = (a[0] * b[0]) + (a[1] * b[4]) + (a[2] * b[8])  + (a[3] * b[12]);
		m[1] = (a[0] * b[1]) + (a[1] * b[5]) + (a[2] * b[9])  + (a[3] * b[13]);
		m[2] = (a[0] * b[2]) + (a[1] * b[6]) + (a[2] * b[10]) + (a[3] * b[14]);
		m[3] = (a[0] * b[3]) + (a[1] * b[7]) + (a[2] * b[11]) + (a[3] * b[15]);

		m[4] = (a[4] * b[0]) + (a[5] * b[4]) + (a[6] * b[8])  + (a[7] * b[12]);
		m[5] = (a[4] * b[1]) + (a[5] * b[5]) + (a[6] * b[9])  + (a[7] * b[13]);
		m[6] = (a[4] * b[2]) + (a[5] * b[6]) + (a[6] * b[10]) + (a[7] * b[14]);
		m[7] = (a[4] * b[3]) + (a[5] * b[7]) + (a[6] * b[11]) + (a[7] * b[15]);

		m[8]  = (a[8] * b[0]) + (a[9] * b[4]) + (a[10] * b[8])  + (a[11] * b[12]);
		m[9]  = (a[8] * b[1]) + (a[9] * b[5]) + (a[10] * b[9])  + (a[11] * b[13]);
		m[10] = (a[8] * b[2]) + (a[9] * b[6]) + (a[10] * b[10]) + (a[11] * b[14]);
		m[11] = (a[8] * b[3]) + (a[9] * b[7]) + (a[10] * b[11]) + (a[11] * b[15]);

		m[12] = (a[12] * b[0]) + (a[13] * b[4]) + (a[14] * b[8])  + (a[15] * b[12]);
		m[13] = (a[12] * b[1]) + (a[13] * b[5]) + (a[14] * b[9])  + (a[15] * b[13]);
		m[14] = (a[12] * b[2]) + (a[13] * b[6]) + (a[14] * b[10]) + (a[15] * b[14]);
		m[15] = (a[12] * b[3]) + (a[13] * b[7]) + (a[14] * b[11]) + (a[15] * b[15]);
		return m;
	}

	inline const Matrix4f operator*= (Matrix4f &a, const Matrix4f &b)
	{
		a = a * b;
		return a;
	}
	
}