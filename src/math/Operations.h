#pragma once

#include "Vectors.h"
#include "Matrix.h"

#include <numeric>

namespace Math {
	template<_dimType N, typename T>
	inline T sum(const Vec<N, T>& v) {
		return std::reduce(v.values, v.values + N);
	}

	template<typename T>
	inline T det(const Mat<2, 2, T>& mat) {
		return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
	}

	template<_dimType N, typename T>
	inline T len(const Vec<N, T>& v) {
		T idk = 0;
		for (_dimType i = 0; i < N; i++) {
			idk += v[i] * v[i];
		}
		return (T)sqrt(idk);
	}

	template<_dimType N, typename T>
	inline Vec<N, T> normalize(const Vec<N, T>& v) {
		T l = len(v);
		Vec<N, T> r;
		for (_dimType i = 0; i < N; i++) {
			r[i] = v[i] / l;
		}
		return r;
	}

	template<typename T>
	Vec<3, T> cross(const Vec<3, T>& v1, const Vec<3, T>& v2) {
		//Mat<3, 3, T> mat = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
		//Mat<2, 2, T> mi = { v1.y(), v1.z(), v2.y(), v2.z() };
		//Mat<2, 2, T> mj = { v1.x(), v1.z(), v2.x(), v2.z() };
		//Mat<2, 2, T> mk = { v1.x(), v1.y(), v2.x(), v2.y() };
		//return (mat[0] * mi.det()) - (mat[1] * mj.det()) + (mat[2] * mk.det());
		return {
			v1.y() * v2.z() - v1.z() * v2.y(),
			v1.z() * v2.x() - v1.x() * v2.z(),
			v1.x() * v2.y() - v1.y() * v2.x()
		};
	}

	template<_dimType N, typename T>
	T dot(const Vec<N, T>& v1, const Vec<N, T>& v2) {
		return sum(v1 * v2);
	}

	template<_dimType Rows, _dimType Cols, typename T>
	Mat<Rows, Cols, T> transpose(const Mat<Rows, Cols, T>& m) {
		Mat<Rows, Cols, T> copy = m;
		const T* t = &m[0][0];
		int c = 0;
		for (_dimType i = 0; i < Rows; i++) {
			for (_dimType j = 0; j < Cols; j++) {
				copy.columns[j][i] = t[c++];
			}
		}
		return copy;
	}
}
