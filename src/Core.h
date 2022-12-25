#pragma once
#include <stdint.h>
#include <string>

using uint = uint32_t;
using sint = int32_t;
using ulong = uint64_t;
using slong = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

#define ASSERT(x)\
if (!(x)) {\
    __builtin_debugtrap()\
}\

using String = std::string;