#ifndef BS_TYPES_H
#define BS_TYPES_H

#include <stdint.h>

#include "bs_define.h"

//define exact size types
typedef uint8_t				ui8;
typedef uint8_t				byte;
typedef uint16_t			ui16;
typedef uint32_t			ui32;
typedef uint64_t			ui64;

typedef int8_t				i8;
typedef int16_t				i16;
typedef int32_t				i32;
typedef int64_t				i64;

//just for consistency
typedef float				f32;
typedef double				f64;

//variable float (for physics etc)
typedef BS_REAL				real;

typedef size_t				ptrsize;

//for variadic templates
struct nothing{ };

#endif