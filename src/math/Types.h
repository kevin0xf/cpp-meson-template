#pragma once

#include "Vectors.h"
#include "Matrix.h"

namespace Math {

	using NT = float;

	using Vector2 = Vec<2, NT>;
	using Vector3 = Vec<3, NT>;
	using Vector4 = Vec<4, NT>;

	using Vector2I = Vec<2, int>;
	using Vector3I = Vec<3, int>;
	using Vector4I = Vec<4, int>;

	using Vector2F = Vec<2, float>;
	using Vector3F = Vec<3, float>;
	using Vector4F = Vec<4, float>;

	using Vector2D = Vec<2, double>;
	using Vector3D = Vec<3, double>;
	using Vector4D = Vec<4, double>;

	using Vector2UI = Vec<2, unsigned int>;
	using Vector3UI = Vec<3, unsigned int>;
	using Vector4UI = Vec<4, unsigned int>;

	using Matrix2x2 = Mat<2, 2, NT>;
	using Matrix3x2 = Mat<3, 2, NT>;
	using Matrix3x3 = Mat<3, 3, NT>;
	using Matrix4x4 = Mat<4, 4, NT>;

	using Matrix2 = Matrix2x2;
	using Matrix3 = Matrix3x3;
	using Matrix4 = Matrix4x4;

}