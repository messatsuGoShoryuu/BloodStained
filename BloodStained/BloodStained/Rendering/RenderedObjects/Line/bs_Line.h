#ifndef BS_LINE_H
#define BS_LINE_H

#include "../../../Containers/bs_Array.h"
#include "../../bs_VertexBufferObject.h"
#include "../../../Math/bs_Vector.h"
namespace bs
{
	class Vector3;
	class Line3D
	{
	public:
		Line3D();
		Line3D(const Line3D& l);
		~Line3D();

		inline const	Array<Vector3>& points()	const	{ return m_points; }
		inline void		addPoint(const Vector3& point){ m_points.add(point); }
		inline void		clear(){ m_points.clear(); }
		inline void		setPoint(const Vector3& v, ui32 index){ m_points[index] = v; }
		inline const	Array<Vector3>& vertices()
		{
			_generateVerticesFromPoints();
			return m_vertices;
		}

	private:
		void	_generateVerticesFromPoints();
	private:
		real m_thickness;
		Array<Vector3> m_points;
		Array<Vector3> m_vertices;
	};
}

#endif // !BS_LINE_H
