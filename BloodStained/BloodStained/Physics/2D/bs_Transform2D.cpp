#include "bs_Transform2D.h"


namespace bs
{
	Basis2D::Basis2D()
		:m_x(Vector2::right),
		m_y(Vector2::up)
	{
		
	}
	Basis2D::Basis2D(const Transform2D & t)
	{
		calculate(t);
	}
	Basis2D::Basis2D(const Basis2D & b)
	{
	}
	Basis2D::~Basis2D()
	{
	}
	Vector2 Basis2D::transform(const Vector2 & absoluteCenter, const Vector2 & target) const
	{
		return Vector2();
	}
	void Basis2D::calculate(const Transform2D & t)
	{
		real cos = math::cos(t.m_orientation);
		real sin = math::sin(t.m_orientation);		

		m_x.x = cos;
		m_x.y = -sin;

		m_y.x = sin;
		m_y.y = cos;
	}

	Transform2D::Transform2D()
		:m_orientation(0.0f),
		m_scale(Vector2::unit),
		m_position(Vector2::zero)
	{
	}
	Transform2D::Transform2D(const Transform2D & t)
		:m_basis(t.m_basis),
		m_orientation(t.m_orientation),
		m_position(t.m_position),
		m_scale(t.m_scale)
	{
	}
	Transform2D::~Transform2D()
	{
	}
	void Transform2D::setOrientation(real newOrientation)
	{
		m_orientation = newOrientation;
		m_basis.calculate(SELF);
	}
	void Transform2D::rotate(real amount)
	{
		setOrientation(m_orientation + amount);
	}
	void Transform2D::setPosition(const Vector2 & newPosition)
	{
		m_position = newPosition;
	}
	void Transform2D::translate(const Vector2 & amount)
	{
		m_position += amount;
	}
	void Transform2D::setScale(const Vector2 & newScale)
	{
		m_scale = newScale;
	}
	void Transform2D::multScale(const Vector2 & amount)
	{
		m_scale.x *= amount.x;
		m_scale.y *= amount.y;
	}
}