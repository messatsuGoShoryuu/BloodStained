#ifndef _BS_SHAPE2D_
#define _BS_SHAPE2D_

#include <Math/bs_Vector.h>
namespace bs
{
#define	BS_SHAPE_VERTEX_COUNT 8


	class Shape2D
	{
	public:
		Shape2D();
		Shape2D(const Shape2D& s);
		~Shape2D();

	public:
		bool addVertex(const Vector2& vertex);
		bool addVertex(real x, real y);

		inline	Vector2* getVertices()	{ return m_vertices; }
		inline	Vector2* getNormals()	{ return m_normals; }

		inline	const	Vector2* getVertices() const { return m_vertices; }
		inline	const	Vector2* getNormals() const	{ return m_normals; }

		inline ui32 vertexCount() const { return m_vertexCount; }

		void	calculateNormals();
		void	calculateCenter();

		inline const Vector2& center() { return m_center; }
		

	private:
		Vector2 m_vertices[BS_SHAPE_VERTEX_COUNT];
		Vector2 m_normals[BS_SHAPE_VERTEX_COUNT];
		Vector2 m_center;
		ui32 m_vertexCount;
	};


	
}

#endif // !_BS_SHAPE2D_