#ifndef _BS_PRIMITIVE_H_
#define	_BS_PRIMITIVE_H_

#include "bs_Vertex.h"
namespace bs
{
	template<class VertexType>
	struct Quad
	{
		struct
		{
			VertexType topLeft;
			VertexType bottomLeft;
			VertexType bottomRight;
			VertexType topRight;
		};

		VertexType& operator[](ui32 index)
		{
			VertexType* v = reinterpret_cast<VertexType*>(this);
			return *(v + index);
		}

		const	VertexType& operator[](ui32 index) const
		{
			VertexType* v = reinterpret_cast<VertexType*>(this);
			return *(v + index);
		}
	};
}

#endif // !_BS_PRIMITIVE_H_