#include "bs_Camera2D.h"
#include "../Globals/bs_globals.h"

namespace bs
{
	Camera2D::Camera2D()
		:Camera(),
		m_orientation(0.0f),
		m_position(Vector2::zero),
		m_depth(-10.0)
	{
		m_viewPort.w = static_cast<f32>(g_screen.width());
		m_viewPort.h = static_cast<f32>(g_screen.height());
		m_aspectRatio = g_screen.aspectRatio();
		m_view.loadIdentity();
		_updateViewMatrix();
		_constructProjectionMatrix();
	}

	Camera2D::Camera2D(const Camera2D& c)
		:Camera(c),
		m_orientation(c.m_orientation),
		m_position(c.m_position),
		m_depth(c.m_depth)
	{

	}

	Camera2D::~Camera2D()
	{

	}

	void Camera2D::_updateViewMatrix()
	{
		m_view.loadIdentity();
		//Translate:
		m_view[3][0] = -m_position.x;
		m_view[3][1] = -m_position.y;
		m_view[3][2] = m_depth;

		//Rotate:
		m_view[0][0] = math::cos(m_orientation);
		m_view[1][0] = math::sin(m_orientation);
		m_view[0][1] = -math::sin(m_orientation);
		m_view[1][1] = m_view[0][0];
	}

	void	Camera2D::_constructProjectionMatrix()
	{
		//Left, Right, Top, Bottom, Near, Far.
		f32 l = -m_aspectRatio;
		f32 r = m_aspectRatio;
		f32 t = 1;
		f32 b = -1;
		f32 n = m_nearPlane;
		f32 f = m_farPlane;

		m_projection.loadIdentity();
		
		//First column:
		m_projection[0][0] = 2.0f / (r - l);

		//Second column:
		m_projection[1][1] = 2.0f / (t - b);

		//Third column:
		m_projection[2][2] = -2.0f / (f - n);

		//Fourth column:
		m_projection[3][0] = -(r + l) / (r - l);
		m_projection[3][1] = -(t + b) / (t - b);
		m_projection[3][2] = -(f + n) / (f - n);
	}


}