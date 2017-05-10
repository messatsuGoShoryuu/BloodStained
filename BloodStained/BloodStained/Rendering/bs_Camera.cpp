#include "bs_Camera.h"
#include "../Globals/bs_globals.h"

namespace bs
{
	Camera::Camera()
		:m_nearPlane(0.01f),
		m_farPlane(1000.0f)
	{

	}

	Camera::Camera(const Camera& c)
		:m_nearPlane(c.m_nearPlane),
		m_farPlane(c.m_farPlane),
		m_aspectRatio(c.m_aspectRatio),
		m_projection(c.m_projection),
		m_view(c.m_view)
	{

	}

	Camera::~Camera()
	{

	}

	void	Camera::setNearPlane(f32 nearPlane)
	{
		m_nearPlane = nearPlane;
		_constructProjectionMatrix();
	}

	void	Camera::setFarPlane(f32 farPlane)
	{
		m_farPlane = farPlane;
		_constructProjectionMatrix();
	}

	void	Camera::setViewport(const Rectf32& r)
	{
		m_viewPort = r;
		_calculateAspectRatio();
		_constructProjectionMatrix();
	}

	void Camera::_updateViewMatrix()
	{

	}

	void	Camera::_constructProjectionMatrix()
	{

	}

	void	Camera::_calculateAspectRatio()
	{
		m_aspectRatio = m_viewPort.w / m_viewPort.h;
	}
}