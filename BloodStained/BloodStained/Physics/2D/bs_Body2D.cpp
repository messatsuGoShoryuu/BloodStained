#include "bs_Body2D.h"

bs::Body2D::Body2D()
	:m_mass(0),
	m_inertia(0),
	m_inverseMass(0),
	m_inverseInertia(0),
	m_angularVelocity(0),
	m_torque(0),
	m_owner(nullptr),
	m_gravityScale(0.0f),
	m_timeScale(1.0f),
	m_staticFriction(0.1f),
	m_dynamicFriction(0.1f),
	m_restitution(0.0f)
{
}

bs::Body2D::Body2D(const Body2D & b)
	:m_mass(b.m_mass),
	m_inertia(b.m_inertia),
	m_inverseMass(b.m_inverseMass),
	m_inverseInertia(b.m_inverseInertia),
	m_transform(b.m_transform),
	m_velocity(b.m_velocity),
	m_acceleration(b.m_acceleration),
	m_angularVelocity(b.m_angularVelocity),
	m_torque(b.m_torque),
	m_owner(b.m_owner),
	m_gravityScale(b.m_gravityScale),
	m_timeScale(b.m_timeScale),
	m_staticFriction(b.m_staticFriction),
	m_dynamicFriction(b.m_dynamicFriction),
	m_restitution(b.m_restitution)
{
}

bs::Body2D::~Body2D()
{
}




void bs::Body2D::addForceAtPosition(const Vector2 & force, const Vector2 & position)
{
	m_acceleration += force;
	m_torque += Vector2::cross(position, force);
}

void bs::Body2D::addImpulseAtPosition(const Vector2 & force, const Vector2 & position)
{
	m_velocity += force;
	m_angularVelocity += Vector2::cross(position, force);

}

void bs::Body2D::integrate(real dt)
{
	m_angularVelocity += m_torque;
	m_velocity += m_acceleration;

	m_transform.rotate(m_angularVelocity * dt * m_timeScale);
	m_transform.translate(m_velocity * dt * m_timeScale);

	m_torque = 0.0f;
	m_acceleration = Vector2::zero;
}
