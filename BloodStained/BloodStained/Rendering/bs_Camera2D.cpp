#include "bs_Camera2D.h"
#include  "bs_Screen.h"

namespace bs
{
	Camera2D::Camera2D()
		:Camera(),
		m_orientation(0.0f),
		m_position(Vector2::zero),
		m_depth(-10.0),
		m_scale(10.0f)
	{
		m_viewPort.w = static_cast<f32>(Screen::width());
		m_viewPort.h = static_cast<f32>(Screen::height());
		m_aspectRatio = Screen::aspectRatio();
		m_view.loadIdentity();
		_updateViewMatrix();
		_constructProjectionMatrix();
	}

	Camera2D::Camera2D(const Camera2D& c)
		:Camera(c),
		m_orientation(c.m_orientation),
		m_position(c.m_position),
		m_depth(c.m_depth),
		m_scale(c.m_scale)
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

		m_isDirty = true;
	}

	Vector2 Camera2D::screenToWorld(const Vector2 & screenPoint)
	{
		Vector2 coordinates = screenPoint;
		coordinates.x /= static_cast<f32>(Screen::width()) / m_scale;
		coordinates.y /= static_cast<f32>(-(i32)Screen::height()) / m_scale;

		coordinates.x -= 0.5f * m_scale;
		coordinates.x *= 2.0f * Screen::aspectRatio();
		coordinates.y += 0.5f * m_scale;
		coordinates.y *= 2.0f;

		coordinates += m_position;

		return coordinates;
	}

	Vector2 Camera2D::pixelsToNDC(const Vector2 & pixels)
	{
		Vector2 coordinates = pixels;
		coordinates.x = pixels.x / m_viewPort.w * 2.0f - 1.0f;
		coordinates.y = (m_viewPort.h - pixels.y) / m_viewPort.h * 2.0f - 1.0f;

		return coordinates;
	}

	void	Camera2D::_constructProjectionMatrix()
	{
		//Left, Right, Top, Bottom, Near, Far.
		f32 l = -m_scale * m_aspectRatio;
		f32 r = m_scale * m_aspectRatio;
		f32 t = m_scale;
		f32 b = -m_scale;
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

		m_isDirty = true;
	}


}