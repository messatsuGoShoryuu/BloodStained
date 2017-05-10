#ifndef BS_VERTEX_H
#define BS_VERTEX_H



#include "bs_Color.h"
#include "../Math/bs_Vector.h"


namespace bs
{
	struct UVCoordinates
	{
		f32 u;
		f32 v;
	};

	struct Vertex3D_PU
	{
		Vector3			position;
		UVCoordinates	uv;
	};

	struct Vertex3D_PC
	{
		Vector3		position;
		ColorRGBAf	color;
	};

	struct Vertex2D_PUC
	{
		Vector2			position;
		UVCoordinates	uv;
		ColorRGBAf		color;
	};
}
#endif // !BS_VERTEX_H

