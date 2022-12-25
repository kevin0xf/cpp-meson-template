#pragma once

#include "MathUtils.h"

#include <tuple>
#include <stdint.h>
#include <math.h>
#include <functional>
#include <type_traits>

#define _MIN(x, y) (x < y ? x : y)
#define _MAX(x, y) (x > y ? x : y)

//namespace Math {

	template<_dimType N, typename T>
	struct Vec {

		T values[N];

		static constexpr inline _dimType E = N;

		inline T& x() noexcept requires (N >= 1) { return values[0]; }
		inline T& y() noexcept requires (N >= 2) { return values[1]; }
		inline T& z() noexcept requires (N >= 3) { return values[2]; }
		inline T& w() noexcept requires (N >= 4) { return values[3]; }

		inline const T& x() const noexcept requires (N >= 1) { return values[0]; }
		inline const T& y() const noexcept requires (N >= 2) { return values[1]; }
		inline const T& z() const noexcept requires (N >= 3) { return values[2]; }
		inline const T& w() const noexcept requires (N >= 3) { return values[3]; }

		inline T& operator[](_dimType i) {
			return values[i];
		}

		inline const T& operator[](_dimType i) const {
			return values[i];
		}

		inline Vec operator+(const Vec& v) const {
			Vec r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = values[i] + v[i];
			}
			return r;
		}
		inline Vec& operator+=(const Vec& v) {
			for (_dimType i = 0; i < N; i++) {
				values[i] += v[i];
			}
			return *this;
		}
		inline Vec& operator-=(const Vec& v) {
			for (_dimType i = 0; i < N; i++) {
				values[i] -= v[i];
			}
			return *this;
		}
	
		inline Vec operator-() const {
			Vec r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = -this->values[i];
			}
			return r;
		}

		inline Vec operator-(const Vec& v) const {
			Vec r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = values[i] - v[i];
			}
			return r;
		}
		inline Vec operator-(T scl) const {
			Vec r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = values[i] - scl;
			}
			return r;
		}
		inline Vec operator*(T scl) const {
			Vec r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = values[i] * scl;
			}
			return r;
		}
		inline Vec operator/(T scl) const {
			Vec r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = values[i] / scl;
			}
			return r;
		}
		inline void operator*=(T scl) {
			for (_dimType i = 0; i < N; i++) {
				values[i] *= scl;
			}
		}
		template<typename V>
		inline Vec operator*(const Vec<N, V>& t) const {
			Vec r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = values[i] * static_cast<T>(t[i]);
			}
			return r;
		}
		inline Vec& operator*=(const Vec& t) {
			for (_dimType i = 0; i < N; i++) {
				values[i] *= t[i];
			}
			return *this;
		}
		template<typename V>
		inline Vec operator/(const Vec<N, V>& t) const {
			Vec r;
			for (_dimType i = 0; i < N; i++) {
				r[i] = values[i] / static_cast<T>(t[i]);
			}
			return r;
		}
		inline Vec& operator/=(const Vec& t) {
			for (_dimType i = 0; i < N; i++) {
				values[i] /= t[i];
			}
			return *this;
		}

		inline bool operator==(const Vec& t) const {
			for (_dimType i = 0; i < N; i++) {
				if (t[i] != values[i]) {
					return false;
				}
			}
			return true;
		}

		inline bool operator!=(const Vec& t) const {
			return !(*this == t);
		}

		inline const T* data() const {
			return values;
		}

		inline T* data() {
			return values;
		}

		template<_dimType S>
		Vec& setVec(Vec<S, T> v) {
			for(_dimType i = 0; i < _MIN(S, N); i++) {
				values[i] = v[i];
			}
			return *this;
		}

		template<typename... V>
		requires(sizeof...(V) == N)
		inline Vec& set(const V&... v) {
			int i = 0;
			((values[i++] = (T)v), ...);
			return *this;
		}
		template<typename... V>
		requires(sizeof...(V) == N)
		inline Vec& add(const V&... v) {
			int i = 0;
			((values[i++] += (T)v), ...);
			return *this;
		}

		Vec& abs() {
			for(_dimType i = 0; i < N; i++) {
				values[i] = std::abs(values[i]);
			}
			return *this;
		}

		inline bool operator<(const Vec& v) const {
			return sum(*this) < sum(v);
		}
	};

	template<typename T, typename... Args>
	Vec<sizeof...(Args) + 1, T> createVector(T f, Args... args) {
		return { f, static_cast<T>(args)... };
	}

	//author eisi
	// template <_dimType N, typename T>
	// struct std::tuple_size<Vec<N, T>> : std::integral_constant<_dimType, N> {};

	// template <_dimType I, _dimType N, typename T>
	// struct std::tuple_element<I, Vec<N, T>> { using type = T; };

	// template <typename>
	// struct is_vec : std::false_type {};

	// template <_dimType N, typename T>
	// struct is_vec<Vec<N, T>> : std::true_type {};

	// template <typename T>
	// inline constexpr bool is_vec_v = is_vec<T>::value;

	// template <_dimType I, typename U>
	// requires (is_vec_v<std::remove_cvref_t<U>>&& I < std::tuple_size_v<std::remove_cvref_t<U>>)
	// constexpr decltype(auto) get(U&& v) noexcept {
	// 	return std::forward<U>(v).values[I];
	// }
	//

//}

namespace std {
	template<_dimType N, typename T>
	struct hash<Vec<N, T>> {
		std::size_t operator()(const Vec<N, T>& s) const noexcept {
			size_t idk = 0;
			for (_dimType i = 0; i < N; i++) {
				idk ^= std::hash<T>{}(s[i] << i) << i;
			}
			return idk;
		}
	};
}

