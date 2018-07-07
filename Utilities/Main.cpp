
#include <iostream>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3f.h"
#include "Matrix4f.h"

typedef Math::Vector2f Vector2f;
typedef Math::Vector3f Vector3f;
typedef Math::Vector4f Vector4f;
typedef Math::Matrix3f Matrix3f;
typedef Math::Matrix4f Matrix4f;

int main()
{
	Math::Vector2i v;
	/*Matrix3f m = Matrix3f();
	m[0] = 1.0f; m[1] = 2.0f; m[2] = 3.0f;
	m[3] = 1.0f; m[4] = 2.0f; m[5] = 3.0f;
	m[6] = 1.0f; m[7] = 2.0f; m[8] = 3.0f;*/

	Matrix4f m = Matrix4f();
	m[0]  = 1.0f; m[1]  = 2.0f; m[2]  = 3.0f;  m[3] = 4.0f;
	m[4]  = 2.0f; m[5]  = 2.0f; m[6]  = 3.0f;  m[7] = 4.0f;
	m[8]  = 3.0f; m[9]  = 3.0f; m[10] = 3.0f; m[11] = 4.0f;
	m[12] = 4.0f; m[13] = 4.0f; m[14] = 4.0f; m[15] = 4.0f;

	Matrix4f m2(m);

	std::cout << m.GetInverse() << "\n\n";

	system("pause");
	return 0;
}