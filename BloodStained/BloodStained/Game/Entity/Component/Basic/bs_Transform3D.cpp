#include "bs_Transform3D.h"

namespace bs
{
	Transform3D::Transform3D()
		:Component<Transform3D>()
	{

	}

	Transform3D::Transform3D(const Transform3D& t)
		: Component<Transform3D>(t),
		m_position(t.m_position),
		m_scale(t.m_scale),
		m_orientation(t.m_orientation),
		m_modelMatrix(t.m_modelMatrix)
	{

	}

	Transform3D::~Transform3D()
	{

	}

	void	Transform3D::translate(const Vector3& amount)
	{
		m_position += amount;

		m_modelMatrix[3][0] = m_position.x;
		m_modelMatrix[3][1] = m_position.y;
		m_modelMatrix[3][2] = m_position.z;
	}

	void	Transform3D::translate(real x, real y, real z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;

		m_modelMatrix[3][0] = m_position.x;
		m_modelMatrix[3][1] = m_position.y;
		m_modelMatrix[3][2] = m_position.z;
	}

	//Rotate by degrees
	void	Transform3D::rotate(const Quaternion&	amount)
	{
		m_orientation *= amount;
		_updateBasis();
	}

	//Rotate by degrees
	void	Transform3D::rotate(const Vector3&	amount)
	{
		Quaternion q;
		q.fromEuler(amount);
		m_orientation *= q;
		_updateBasis();
	}

	//Rotate by degrees
	void	Transform3D::rotate(real right, real up, real forward)
	{
		Quaternion q;
		q.fromEuler(Vector3(right, up, forward));
		m_orientation *= q;
		_updateBasis();
	}


	void	Transform3D::setPosition(const Vector3& newPosition)
	{
		m_position = newPosition;

		m_modelMatrix[3][0] = m_position.x;
		m_modelMatrix[3][1] = m_position.y;
		m_modelMatrix[3][2] = m_position.z;
	}

	void	Transform3D::setPosition(real x, real y, real z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;

		m_modelMatrix[3][0] = m_position.x;
		m_modelMatrix[3][1] = m_position.y;
		m_modelMatrix[3][2] = m_position.z;
	}

	void	Transform3D::setOrientation(const Quaternion& newOrientation)
	{
		m_orientation = newOrientation;
		_updateBasis();
	}

	void	Transform3D::setOrientation(const Vector3& newOrientation)
	{
		m_orientation.fromEuler(newOrientation);
		_updateBasis();
	}

	void Transform3D::setOrientation(real right, real up, real forward)
	{
		m_orientation.fromEuler(Vector3(right, up, forward));
		_updateBasis();
	}

	void Transform3D::_updateBasis()
	{
		m_forward = m_orientation * m_forward;
		m_up = m_orientation * m_up;
		m_right = m_orientation * m_right;
		m_forward.normalize();
		m_up.normalize();
		m_right.normalize();
		m_orientation.toRotationMatrix(m_modelMatrix);
	}


	void	Transform3D::setScale(const Vector3& newScale)
	{
		m_scale = newScale;
	}

	void	Transform3D::setScale(real x, real y, real z)
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;
	}

	void	Transform3D::scaleBy(real value)
	{
		m_scale *= value;
	}
}