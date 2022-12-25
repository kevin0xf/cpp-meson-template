#pragma once

#include "Vectors.h"
#include "Matrix.h"

	template<typename I, _dimType N, typename T>
	I& operator<<(I& o, const Vec<N, T>& v) {
		o << '{';
		for (int i = 0; i < N; i++) {
			o << v[i];
			if (i != N - 1) {
				o << ", ";
			}
		}
		o << '}';
		return o;
	}

	template<typename I, _dimType Rows, _dimType Cols, typename T>
	I& operator<<(I& o, const Math::Mat<Rows, Cols, T>& mat) {
		for (int i = 0; i < Rows; i++) {
			o << '{';
			for (int j = 0; j < Cols; j++) {
				o << mat.columns[j][i];
				if (j != Cols - 1) {
					o << ", ";
				}
			}
			o << '}';
			if (i != Rows - 1) {
				o << '\n';
			}
		}
		return o;
	}

namespace Math {

}
