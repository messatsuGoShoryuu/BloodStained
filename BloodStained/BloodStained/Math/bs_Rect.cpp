#include "bs_Rect.h"
#include "bs_Vector.h"


namespace bs
{
	Rectf32::Rectf32()
		:x(0.0f),
		y(0.0f),
		w(1.0f),
		h(1.0f)
	{

	}

	Rectf32::Rectf32(f32 x, f32 y, f32 w, f32 h)
		:x(x),
		y(y),
		w(w),
		h(h)
	{

	}

	Rectf32::Rectf32(const Rectf32& r)
		:x(r.x),
		y(r.y),
		w(r.w),
		h(r.h)
	{

	}

	Rectf32::~Rectf32()
	{

	}

	bool	Rectf32::contains(const Vector2&  v)
	{
		f32 halfWidth = w / 2.0f;
		f32 halfHeight = h / 2.0f;
		if (!math::rangeContains(v.x, x - halfWidth, x + halfWidth)) return false;
		if (!math::rangeContains(v.y, y - halfHeight, y + halfHeight)) return false;
		return true;
	}
}