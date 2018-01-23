#include "bs_Camera3D.h"
#include "bs_Screen.h"
#include "../Physics/3D/Collisions/bs_Ray3D.h"

namespace bs
{
	Camera3D::Camera3D()
		:Camera(),
		m_orientation(Quaternion::identity),
		m_fov(40.0f),
		m_up(Vector3::up),
		m_forward(Vector3::forward),
		m_right(Vector3::right)
	{
		m_viewPort.w = static_cast<f32>(Screen::width());
		m_viewPort.h = static_cast<f32>(Screen::height());
		m_aspectRatio = Screen::aspectRatio();
		m_view.loadIdentity();
		_updateViewMatrix();
		_constructProjectionMatrix();
	}

	Camera3D::Camera3D(const Camera3D& c)
		:Camera(c),
		m_orientation(c.m_orientation),
		m_fov(c.m_fov),
		m_up(c.m_up),
		m_forward(c.m_forward),
		m_right(c.m_right)
	{

	}

	Camera3D::~Camera3D()
	{

	}

	void Camera3D::_updateViewMatrix()
	{
		m_view.loadIdentity();
		//Rotation
		m_view[0][0] = m_right.x;
		m_view[1][0] = m_right.y;
		m_view[2][0] = m_right.z;
		m_view[0][1] = m_up.x;
		m_view[1][1] = m_up.y;
		m_view[2][1] = m_up.z;
		m_view[0][2] = m_forward.x;
		m_view[1][2] = m_forward.y;
		m_view[2][2] = m_forward.z;

		//Translation
		m_view[3][0] = -m_right.dot(m_position);
		m_view[3][1] = -m_up.dot(m_position);
		m_view[3][2] = -m_forward.dot(m_position);

		m_isDirty = true;
	}

	void	Camera3D::_constructProjectionMatrix()
	{
		//Left, Right, Top, Bottom, Near, Far.
		f32 n = m_nearPlane;
		f32 f = m_farPlane;
		f32 a = m_aspectRatio;
		f32 fov = math::tan((m_fov * BS_DEG_TO_RAD) / 2.0f);

		m_projection.loadIdentity();

		//First column:
		m_projection[0][0] = 1.0f / (fov * a);

		//Second column:
		m_projection[1][1] = 1.0f / fov;

		//Third column:
		m_projection[2][2] = (f + n) / (f - n);
		m_projection[2][3] = 1.0f;


		//Fourth column:
		m_projection[3][2] = -(2.0f * f * n) / (f - n);
		m_projection[3][3] = 0.0f;

		m_isDirty = true;
	}

	Ray3D Camera3D::screenToWorld(const Vector2& screenPoint)
	{
		Ray3D result;

		//Transform from window view to NDC
		Vector3 NDCnear = pixelsToNDC(screenPoint, m_nearPlane);
		Vector3 NDCfar = pixelsToNDC(screenPoint, m_farPlane);

		//Transform to homogenous coordinates
		Vector4 hNear = Vector4(NDCnear, 1.0);
		Vector4 hFar = Vector4(NDCfar, 1.0);

		//Compute inverse view-projection matrix
		Matrix4x4 vp = m_view * m_projection;
		Matrix4x4 ivp;
		vp.inverse(ivp);

		//Apply transformation to near and far.
		Vector4 ihNear = ivp * hNear;
		Vector4 ihFar = ivp * hFar;

		//Apply perspective division
		ihNear /= ihNear.w;
		ihFar /= ihFar.w;
		
		//Calculate normal.
		result.normal = ihFar - ihNear;
		result.normal.normalize();

		//Origin is the near plane projection
		result.origin = ihNear;

		return result;
	}

	Vector3 Camera3D::pixelsToNDC(const Vector2& pixels, real desiredZ)
	{
		Vector3 coordinates = pixels;
		coordinates.x = pixels.x / m_viewPort.w * 2.0f - 1.0f;
		coordinates.y = (m_viewPort.h - pixels.y) / m_viewPort.h * 2.0f - 1.0f;
		coordinates.z = (desiredZ - m_nearPlane) / (m_farPlane - m_nearPlane) * 2.0f - 1.0f;

		return coordinates;
	}
}