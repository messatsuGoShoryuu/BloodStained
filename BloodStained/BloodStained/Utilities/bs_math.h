#ifndef BS_MATH_H
#define BS_MATH_H

#include <math.h>
#include <iostream>

#include "bs_types.h"


namespace bs
{
	inline ui32 nearestPowerOfTwo(ui32 value)
	{
		value--;
		value |= value >> 1;
		value |= value >> 2;
		value |= value >> 4;
		value |= value >> 8;
		value |= value >> 16;
		value++;

		return value;
	}


	inline bool isPair(ui32 value)
	{
		value = value ^ (value >> 1);
		value = value ^ (value >> 2);
		value = value ^ (value >> 4);
		value = value ^ (value >> 8);
		value = value ^ (value >> 16);

		return value & 1;
	}

	inline ui32 nearest2PowMultipleOf(ui32 value, ui32 multiple)
	{
		//only for 2^k multiples of value.
		ui32 mask = value & multiple - 1;
		return value - mask + ((mask + (multiple - 1)) & multiple);
	}

	inline f32 abs(f32 value)
	{
		if (value >= 0) return value;
		return -value;
	}

	inline f32 sin(f32 angle)
	{
		return std::sin(angle);
	}

	inline f32 cos(f32 angle)
	{
		return std::cos(angle);
	}

	inline f32 tan(f32 angle)
	{
		return std::tan(angle);
	}

	inline f32 asin(f32 angle)
	{
		return std::asin(angle);
	}

	inline f32 acos(f32 angle)
	{
		return std::acos(angle);
	}

	inline f32 atan(f32 angle)
	{
		return std::atan(angle);
	}

	inline f32 lerp(f32 first, f32 second, f32 weight)
	{
		return (1 - weight) * first + weight * second;
	}

	inline f32 sqrt(f32 value)
	{
		return std::sqrt(value);
	}

	inline f32 pow(f32 value, f32 power)
	{
		return std::powf(value, power);
	}

	inline void storeUi16ToByteArray(byte* array, ui16 value)
	{
		array[0] = value & 0xFF;
		array[1] = (value >> 8) & 0xFF;
	}

	inline void storeUi32ToByteArray(byte* array, ui32 value)
	{
		array[0] = value  & 0x000000FF;
		array[1] = (value & 0x0000FF00) >> 8;
		array[2] = (value & 0x00FF0000) >> 16;
		array[3] = (value & 0XFF000000) >> 24;
	}

	inline void endianSwap(byte* array, byte size)
	{
		ui8 start = 0;
		ui8 end = size - 1;

		byte temp = array[0];


		while (start <= end)
		{
			temp = array[start];
			array[start] = array[end];
			array[end] = temp;

			start++;
			end--;
		}
	}

	inline bool rangesOverlap(f32 min1, f32 max1, f32 min2, f32 max2)
	{
		return min1 <= max2 && min2 <= max1;
	}

	inline bool rangesOverlap(i32 min1, i32 max1, i32 min2, i32 max2)
	{
		return min1 <= max2 && min2 <= max1;
	}

	inline void extractOverlappingRange(f32 min1, f32 max1, f32 min2, f32 max2, f32& minOut, f32& maxOut)
	{
		minOut = min1 > min2 ? min1 : min2;
		maxOut = max1 < max2 ? max1 : max2;
	}

	inline bool rangeContains(f32 value, f32 min, f32 max)
	{
		return value >= min && value <= max;
	}

	inline bool rangeContainsExclusive(f32 value, f32 min, f32 max)
	{
		return value > min && value < max;
	}

	inline bool rangeContainsExclusive(f32 bigMin, f32 bigMax, f32 smallMin, f32 smallMax)
	{
		if (!rangeContainsExclusive(smallMin, bigMin, bigMax)) return false;
		if (!rangeContainsExclusive(smallMax, bigMin, bigMax)) return false;
		return true;

	}

	inline ui32 minimum(ui32 v1, ui32 v2)
	{
		return v1 < v2 ? v1 : v2;
	}

	inline ui32 maximum(ui32 v1, ui32 v2)
	{
		return v1 > v2 ? v1 : v2;
	}

	inline i32 minimum(i32 v1, i32 v2)
	{
		return v1 < v2 ? v1 : v2;
	}

	inline i32 maximum(i32 v1, i32 v2)
	{
		return v1 > v2 ? v1 : v2;
	}

	inline f32 minimum(f32 v1, f32 v2)
	{
		return v1 < v2 ? v1 : v2;
	}

	inline f32 maximum(f32 v1, f32 v2)
	{
		return v1 > v2 ? v1 : v2;
	}
}

#endif // !BS_MATH_H
