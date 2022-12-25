#pragma once

#include "Vectors.h"

namespace Math {




	template<_dimType Rows, _dimType Cols, typename T>
	struct Mat {
		static const constexpr inline _dimType N = Rows;
		static const constexpr inline _dimType M = Cols;

		using ColType = Vec<Rows, T>;
		using RowType = Vec<Cols, T>;
		using DataType = T;

		ColType columns[Cols];


		inline Vec<Cols - 1, T> operator*(const Vec<Cols - 1, T>& v) const {
			RowType k;
			k.setVec(v);
			k[Cols - 1] = 1;
			k = *this * k;
			Vec<Cols - 1, T> r;
			r.setVec(k);
			return r;
		}

		inline ColType operator*(const RowType& v) const {
			ColType r = {};
			for (_dimType i = 0; i < Cols; i++) {
				r += columns[i] * v[i];
			}
			return r;
		}

		template<_dimType N>
		inline Mat<Cols, N, T> operator*(const Mat<Cols, N, T>& m) const {
			Mat<Cols, N, T> r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = *this * m[i];
			}
			return r;
		}

		inline Mat& operator*=(const Mat& m) {
			*this = *this * m;
			return *this;
		}

		inline ColType& operator[](_dimType i) {
			return columns[i];
		}

		inline const ColType& operator[](_dimType i) const {
			return columns[i];
		}

		inline T* data() {
			return columns->data();
		}

		inline const T* data() const {
			return columns->data();
		}

	};

	template<typename T>
	Vec<3, T> getPosition(const Mat<4, 4, T>& m) {
		return {m[3][0], m[3][1], m[3][2]};
	}

}
