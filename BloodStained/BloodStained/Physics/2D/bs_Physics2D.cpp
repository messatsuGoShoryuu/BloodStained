#include "bs_Physics2D.h"


namespace bs
{
	Shape2D attachShapeToBasis(const Transform2D& transform, const Shape2D& shape)
	{
		const	Basis2D* basis = &transform.basis();

		Vector2 position = transform.position();
		Vector2 scale = transform.scale();

		ui32 count = shape.vertexCount();
		const Vector2* sourceVertices = shape.getVertices();

		Shape2D result;


		for (ui32 i = 0; i < count; i++)
		{
			Vector2 vertex = sourceVertices[i];

			vertex.x = sourceVertices[i].x * basis->cos() + sourceVertices[i].y * basis->sin();
			vertex.y = -sourceVertices[i].x * basis->sin() + sourceVertices[i].y* basis->cos();

			vertex.x *= scale.x;
			vertex.y *= scale.y;

			vertex += position;

			result.addVertex(vertex);
		}

		result.calculateNormals();
		result.calculateCenter();

		return result;
	}

	Shape2D makeShapeRelativeToBasis(const Transform2D & transform, const Shape2D & shape)
	{
		const	Basis2D* basis = &transform.basis();

		Vector2 position = transform.position();
		Vector2 scale = transform.scale();

		ui32 count = shape.vertexCount();
		const Vector2* sourceVertices = shape.getVertices();

		Shape2D result;

		for (ui32 i = 0; i < count; i++)
		{
			Vector2 vertex = sourceVertices[i];

			Vector2 relVertex = sourceVertices[i] - position;

			vertex.x = basis->x().dot(relVertex);
			vertex.y = basis->y().dot(relVertex);

			vertex.x *= scale.x;
			vertex.y *= scale.y;

			result.addVertex(vertex);
		}

		result.calculateNormals();
		result.calculateCenter();

		return result;
	}

	Shape2D makeShapeRelativeToBasis(const Transform2D & basisTransform,
		const Transform2D & shapeTransform,
		const Shape2D & shape)
	{
		Transform2D transform;
		transform.setPosition(shapeTransform.position() - basisTransform.position());
		transform.setOrientation(shapeTransform.orientation() - basisTransform.orientation());

		return makeShapeRelativeToBasis(transform, shape);
	}
	Vector2 makeVector2RelativeToBasis(const Transform2D & transform, const Vector2 & v)
	{
		Vector2 position = transform.position();
		Vector2 result = v;
		Vector2 vertex = v;
		real cos = math::cos(-transform.orientation());
		real sin = math::sin(-transform.orientation());

		vertex -= position;
		vertex.x /= transform.scale().x;
		vertex.y /= transform.scale().y;

		result.x = vertex.x *  cos + vertex.y * sin;
		result.y = -vertex.x * sin + vertex.y * cos;


		return result;
	}
}