#pragma once

#include <cstring>

#include "Operations.h"
#include "MathUtils.h"

namespace Math {

	template<typename T, _dimType N, _dimType M = N>
	inline Mat<N, N, T> standard(const T& t = 1) {
		Mat<N, M, T > m = {};
		for (_dimType i = 0; i < _MIN(N, M); i++) {
			m[i][i] = t;
		}
		m[N - 1][M - 1] = 1;
		return m;
	}

	template<typename T, typename I = typename T::DataType, typename L = int>
	inline Mat<T::N, T::M, I> standard(const L& t = 1) {
		return standard<I, T::N, T::M>((I)t);
	}

	template<typename TT, _dimType N, typename T>
	Vec<N, TT> changeType(const Vec<N, T>& v) {
		Vec<N, TT> r;
		for (_dimType i = 0; i < N; i++) {
			r[i] = static_cast<TT>(v[i]);
		}
		return r;
	}

	template<typename TT, _dimType Rows, _dimType Cols, typename T>
	Mat<Rows, Cols, TT> changeType(const Mat<Rows, Cols, T>& mat) {
		Mat<Rows, Cols, TT> re;
		for (int c = 0; c < Cols; c++) {
			for (int r = 0; r < Rows; r++) {
				re[c][r] = (TT)mat[c][r];
			}
		}
		return re;
	}

	template<_dimType NewRows, _dimType NewCols, _dimType Rows, _dimType Cols, typename T>
	Mat<NewRows, NewCols, T> convertDim(const Mat<Rows, Cols, T>& mat) {
		Mat<NewRows, NewCols, T> re = standard<T, NewRows, NewCols>();
		for (_dimType c = 0; c < _MIN(Cols, NewCols); c++) {
			for (_dimType r = 0; r < _MIN(Rows, NewRows); r++) {
				re[c][r] = mat[c][r];
			}
		}
		return re;
	}

	template<typename To, _dimType Rows, _dimType Cols, typename T>
	inline Mat<To::N, To::M, T> convertDim(const Mat<Rows, Cols, T>& mat) {
		return convertDim<To::N, To::M>(mat);
	}

	template<_dimType N, _dimType E, typename T>
	inline Vec<N, T> convertDim(const Vec<E, T>& v) {
		Vec<N, T> re {};
		for (_dimType i = 0; i < _MIN(E, N); i++) {
			re[i] = v[i];
		}
		return re;
	}

	template<typename To, _dimType N, typename T>
	inline Vec<To::E, T> convertDim(const Vec<N, T>& v) {
		return convertDim<To::E>(v);
	}

	template<typename T>
	inline Mat<4, 4, T> ortho(T left, T right, T bottom, T top, T near, T far) {
		//return {
		//	2 / (right - left), 0, 0, -(right + left) / (right - left),
		//	0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
		//	0, 0, 1, 0,
		//	0, 0, 0, 1
		//};
//		return {
//			2 / (right - left), 0, 0, 0,
//			0, 2 / (top - bottom), 0, 0,
//			0, 0, 1, 0,
//			(-(right + left) / (right - left)), (-(top + bottom) / (top - bottom)), -1, 1
//		};

		Mat<4, 4, T> r;
		r[0] = {2 / (right - left), 0, 0, 0};
		r[1] = {0, 2 / (top - bottom), 0, 0};
		r[2] = {0, 0, -2 / (far - near), 0};
		r[3] = {(-(right + left) / (right - left)), (-(top + bottom) / (top - bottom)), -((far + near) / (far - near)), 1};
		return r;
	}

	template<typename T>
	inline Mat<4, 4, T> ortho(T width, T height, T near, T far) {
		return ortho<T>(0, width, 0, height, near, far);
	}

	template<typename T>
	inline Mat<4, 4, T> perspective(T fov, T aspect, T near, T far) {
		T th = tan(fov / 2);

		Mat<4, 4, T> m;
		m[0] = {1 / (aspect * th), 0, 0, 0};
		m[1] = {0, 1 / th, 0, 0};
		m[2] = {0, 0, -far / (far - near), -1};
		m[3] = {0, 0, (1 * -far * near) / (far - near), 0};

		return m;
//		return transpose<4, 4, T>({
//			1 / (aspect * th), 0, 0, 0,
//			0, 1 / th, 0, 0,			//2 * : glm
//			0, 0, -far / (far - near), (1 * -far * near) / (far - near),
//			0, 0, -1, 0
//		});
	}

	template<typename T, _dimType V, _dimType N = V + 1>
	inline Mat<N, N, T> translate(const Vec<V, T>& v) {
		Mat<N, N, T> m = standard<T, N>();
		memcpy(m[V].data(), v.data(), V * sizeof(T));
		return m;
	}

	template<typename T>
	inline Mat<4, 4, T> lookAt(Vec<3, T> pos, Vec<3, T> target, Vec<3, T> up) {
		Vec<3, T> dir = normalize(pos - target);
		Vec<3, T> right = normalize(cross(up, dir));
		Vec<3, T> camup = cross(dir, right);

//		Mat<4, 4, T> r = {
//			right.x(), camup.x(), dir.x(), 0,
//			right.y(), camup.y(), dir.y(), 0,
//			right.z(), camup.z(), dir.z(), 0,
//			0, 0, 0, 1
//		};
		Mat<4, 4, T> r;
		r[0] = {right.x(), camup.x(), dir.x(), 0};
		r[1] = {right.y(), camup.y(), dir.y(), 0};
		r[2] = {right.z(), camup.z(), dir.z(), 0};
		r[3] = {0, 0, 0, 1};
		r *= translate(-pos);

		return r;
	}

	template<typename T>
	inline Mat<3, 3, T> rotateX(T r) {
		Mat<3, 3, T> mat;
		mat[0] = {1, 0, 0};
		mat[1] = {0, cos(r), sin(r)};
		mat[2] = {0, -sin(r), cos(r)};
		return mat;
	}

	template<typename T>
	inline Mat<3, 3, T> rotateY(T r) {
		Mat<3, 3, T> mat;
		mat[0] = {cos(r), 0, -sin(r)};
		mat[1] = {0, 1, 0};
		mat[2] = {sin(r), 0, cos(r)};
		return mat;
	}

	template<typename T>
	inline Mat<3, 3, T> rotateZ(T r) {
		Mat<3, 3, T> mat;
		mat[0] = {cos(r), sin(r), 0};
		mat[1] = {-sin(r), cos(r), 0};
		mat[2] = {0, 0, 1};
		return mat;
	}

	template<typename T>
	inline Mat<4, 4, T> rotateD(const Vec<3, T>& v) {
		return convertDim<Mat<4, 4, T>>(rotateX(radians(v.x())) * rotateY(radians(v.y())) * rotateZ(radians(v.z())));
	}

}
