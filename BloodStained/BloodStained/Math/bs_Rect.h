#ifndef BS_RECT_H
#define BS_RECT_H

#include "bs_math.h"

namespace bs
{
	class Vector2;
	class Rectf32
	{
	public:
		Rectf32();
		Rectf32(f32 x, f32 y, f32 w, f32 h);
		Rectf32(const Rectf32& r);
		~Rectf32();

		bool	contains(const Vector2& point);

		void operator=(const Rectf32& r)
		{
			x = r.x;
			y = r.y;
			w = r.w;
			h = r.h;
		}

		f32	x;
		f32 y;
		f32 w;
		f32 h;
	};
}

#endif // !BS_RECT_H
