#ifndef _BS_BODY2D_H_
#define _BS_BODY2D_H_

#include "bs_Transform2D.h"

namespace bs
{
	class Body2D
	{
	public:
		Body2D();
		Body2D(const Body2D& b);
		~Body2D();

	public:
		inline	void	setMass(real mass) 
		{ 
			m_mass = mass; 
			m_inverseMass = mass == 0.0f ? 0.0f : 1.0f / mass; 
		}

		inline	void	setInertia(real inertia) 
		{ 
			m_inertia = inertia; 
			m_inverseInertia = inertia == 0.0f ?  0.0f : 1.0f / inertia; 
		}

		inline  void	addAcceleration(const Vector2& amount) { m_acceleration += amount; }
		inline  void	addVelocity(const Vector2& amount) { m_velocity += amount; }
		inline  void	setVelocity(const Vector2& newVelocity) { m_velocity = newVelocity; }
		inline  void	addAngularVelocity(real amount) { m_angularVelocity += amount; }
		inline  void	setAngularVelocity(real newVelocity) { m_angularVelocity = newVelocity; }
		inline	void	addTorque(real torque) { m_torque += torque; }
		inline	void	setGravityScale(real newScale) { m_gravityScale = newScale; }
		inline	void	setTimeScale(real newScale) { m_timeScale = newScale; }
		inline  void	multTimeScale(real multiplier) { m_timeScale *= multiplier; }
		inline void		setStaticFriction(real value) { m_staticFriction = value; }
		inline void		setDynamicFrictioN(real value) { m_dynamicFriction = value; }
		inline void		setRestitution(real value) { m_restitution = value; }

		void addForceAtPosition(const Vector2& force, const Vector2& position);
		void addImpulseAtPosition(const Vector2& force, const Vector2& position);

		inline real					mass()				const { return m_mass; }
		inline real					inertia()			const { return m_inertia; }
		inline real					inverseMass()		const { return m_inverseMass; }
		inline real					inverseInertia()		const { return m_inverseInertia; }
		inline Transform2D&	transform()					{ return m_transform; }
		inline Vector2				velocity()			const { return m_velocity; }
		inline Vector2				acceleration()		const { return m_acceleration; }
		inline real					angularVelocity()	const { return m_angularVelocity; }
		inline real					torque()			const { return m_torque; }
		inline real					gravityScale()		const { return m_gravityScale; }
		inline real					timeScale()			const { return m_timeScale; }
		inline real					staticFriction()	const { return m_staticFriction; }
		inline real					dynamicFriction()	const { return m_dynamicFriction; }
		inline real					setRestitution()	const { return m_restitution; }


		inline	void	setOwner(void* owner) { m_owner = owner; }
		inline	void*	owner() { return m_owner; }

	public:
		void integrate(real dt);

	private:

		//position + orientation
		Transform2D m_transform;

		//dp / da
		Vector2 m_velocity;
		real m_angularVelocity;
		real m_gravityScale;

		//ddp / dda
		Vector2 m_acceleration;
		real m_torque;

		//dt
		real m_timeScale;

		real m_mass;
		real m_inverseMass;
		real m_inertia;
		real m_inverseInertia;

		//Material
		real m_staticFriction;
		real m_dynamicFriction;
		real m_restitution;

		void* m_owner;

	};
}
#endif // !_BS_BODY2D_H_
