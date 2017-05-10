#include "bs_Transform2D.h"

namespace bs
{
	Transform2D::Transform2D()
		:Component<Transform2D>()
	{

	}

	Transform2D::Transform2D(const Transform2D& t)
		: Component<Transform2D>(t),
		m_position(t.m_position),
		m_scale(t.m_scale),
		m_orientation(t.m_orientation),
		m_modelMatrix(t.m_modelMatrix)
	{

	}

	Transform2D::~Transform2D()
	{

	}

	void	Transform2D::translate(const Vector2& amount)
	{
		m_position += amount;

		m_modelMatrix[3][0] = m_position.x;
		m_modelMatrix[3][1] = m_position.y;
	}

	void	Transform2D::translate(real x, real y)
	{
		m_position.x += x;
		m_position.y += y;

		m_modelMatrix[3][0] = m_position.x;
		m_modelMatrix[3][1] = m_position.y;
	}

	void	Transform2D::rotate(real	degrees)
	{
		m_orientation += degrees;
	}


	void	Transform2D::setPosition(const Vector2& newPosition)
	{
		m_position = newPosition;

		m_modelMatrix[3][0] = m_position.x;
		m_modelMatrix[3][1] = m_position.y;
	}

	void	Transform2D::setPosition(real x, real y)
	{
		m_position.x = x;
		m_position.y = y;

		m_modelMatrix[3][0] = m_position.x;
		m_modelMatrix[3][1] = m_position.y;
	}

	void	Transform2D::setOrientation(real newOrientation)
	{
		m_orientation = newOrientation;
	}


	void	Transform2D::setScale(const Vector2& newScale)
	{
		m_scale = newScale;
	}

	void	Transform2D::setScale(real x, real y)
	{
		m_scale.x = x;
		m_scale.y = y;
	}

	void	Transform2D::scaleBy(real value)
	{
		m_scale *= value;
	}
}