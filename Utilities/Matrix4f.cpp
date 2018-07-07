#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix4f.h"


namespace Math
{
	Matrix4f::Matrix4f()
	{

	}

	inline void Matrix4f::LoadIdentity()
	{
		matrix[0] = 1;	matrix[1] = 0; matrix[2] = 0; matrix[3] = 0;
		matrix[4] = 0;	matrix[5] = 1; matrix[6] = 0; matrix[7] = 0;
		matrix[8] = 0;	matrix[9] = 0;	matrix[10] = 1; matrix[11] = 0;
		matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
	}


	inline void Matrix4f::SetTranslation(const Vector4f &translation)
	{
		SetTranslation(translation.X(), translation.Y(), translation.Z(), translation.W());
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
		SetTranslation(translation.X(), translation.Y(), translation.Z());
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

	/*----------------------------------------------Operations---------------------------------------------------*/



}