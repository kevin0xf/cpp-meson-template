#pragma once

#include <stdint.h>

using _dimType = uint_fast32_t;

namespace Math {

	#define _PI 3.14159265358979323846   // pi
	#define _MIN(x, y) (x < y ? x : y)
	#define _MAX(x, y) (x > y ? x : y)
	#define MASK(x) ((1 << x) - 1)

	template<typename T>
	inline T radians(T i) {
		return (T)(i * _PI / 180);
	}

}

