#include "bs_Level.h"

//Test purposes.
#include <FileIO/bs_ResourceManager.h>
#include <Rendering/bs_Texture2D.h>

#include <Rendering/bs_RenderManager.h>
#include <Rendering/bs_RenderBufferObjects.h>
#include <Rendering/bs_Primitive.h>
#include <Rendering/bs_ShaderManager.h>
#include <Rendering/bs_Shader.h>
#include <Time/bs_Clock.h>
#include <Math/bs_math.h>
#include <Input/bs_InputManager.h>

#include <Physics/2D/bs_Physics2D.h>
#include <Physics/2D/Collisions/bs_GJK2D.h>


namespace bs
{
	Level::Level()
		:m_id(0)
	{
	}

	Level::Level(const Level & l)
		:m_cameras(l.m_cameras),
		m_id(l.m_id)
	{
	}

	Level::~Level()
	{
	}

	void Level::initialize()
	{
		m_cameras.add(new Camera2D());
	}

	void Level::shutDown()
	{
		for (int i = 0; i < m_cameras.count(); i++) delete m_cameras[i];
		m_cameras.~Array();
	}

	void Level::update(f32 dt)
	{
		static	PhysicalObject2D* player = PhysicsManager2D::addPhysicalObject();
		static  PhysicalObject2D* ground = PhysicsManager2D::addPhysicalObject();


		Camera2D* cam = dynamic_cast<Camera2D*>(m_cameras[0]);

		Vector2 pos2 = cam->screenToWorld(Vector2(InputManager::mouse.getX(), InputManager::mouse.getY()));


		if (InputManager::keyboard.isKeyPressed(KB_R)) player->shape() = Shape2D();

		if (InputManager::mouse.isButtonPressed(MOUSE_BUTTON_1))
		{
			player->shape().addVertex(makeVector2RelativeToBasis(player->body()->transform(), pos2));

		}

		if (InputManager::mouse.isButtonPressed(MOUSE_BUTTON_2))
		{
			PhysicalObject2D* box = PhysicsManager2D::addPhysicalObject();
			box->shape().addVertex(Vector2(-0.5f,0.7f));
			box->shape().addVertex(Vector2(0.5f, 0.7f));
			box->shape().addVertex(Vector2(0.5f, -0.7f));
			box->shape().addVertex(Vector2(-0.5f, -0.7f));

			box->shape().calculateNormals();
			box->shape().calculateCenter();
			real inertia = box->shape().getInertiaMoment();
			box->body()->setInertia(inertia);
			box->body()->setGravityScale(1.0f);

			box->body()->transform().setPosition(pos2);
		}


		if (InputManager::keyboard.isKeyHeld(KB_RIGHTARROW))
		{
			if (InputManager::keyboard.isKeyHeld(KB_SHIFT))
			{
				player->body()->addAcceleration(Vector2::right * 0.1f);
			}
			else
			{
				player->body()->setVelocity(Vector2::zero);
				player->body()->transform().translate(Vector2::right * (dt));
			}
		}
		if (InputManager::keyboard.isKeyHeld(KB_LEFTARROW))
		{
			if (InputManager::keyboard.isKeyHeld(KB_SHIFT))
			{
				player->body()->addAcceleration(Vector2::right * -0.1f);
			}
			else
			{
				player->body()->setVelocity(Vector2::zero);
				player->body()->transform().translate(Vector2::right * (-dt));
			}
			
		}
		if (InputManager::keyboard.isKeyHeld(KB_UPARROW))
		{
			if (InputManager::keyboard.isKeyHeld(KB_SHIFT))
			{
				player->body()->addAcceleration(Vector2::up * 0.1f);
			}
			else
			{
				player->body()->setVelocity(Vector2::zero);
				player->body()->transform().translate(Vector2::up * dt);
			}
			
		}
		if (InputManager::keyboard.isKeyHeld(KB_DOWNARROW))
		{
			if (InputManager::keyboard.isKeyHeld(KB_SHIFT))
			{
				player->body()->addAcceleration(Vector2::up * -0.1f);
			}
			else
			{
				player->body()->setVelocity(Vector2::zero);
				player->body()->transform().translate(Vector2::up * (-dt));
			}
			
		}

		if (InputManager::keyboard.isKeyHeld(KB_S)) cam->setScale(cam->scale() * 0.9);
		if (InputManager::keyboard.isKeyHeld(KB_W)) cam->setScale(cam->scale() * 1.1);

		if (InputManager::keyboard.isKeyHeld(KB_A)) player->body()->transform().rotate(-(BS_PI / 180.0f));
		if (InputManager::keyboard.isKeyHeld(KB_D)) player->body()->transform().rotate(BS_PI / 180.0f);

		if (InputManager::keyboard.isKeyHeld(KB_E)) player->body()->addTorque(0.1f);
		if (InputManager::keyboard.isKeyHeld(KB_Q)) player->body()->addTorque(-0.1f);

		if (InputManager::keyboard.isKeyPressed(KB_C))
		{
			player->body()->setGravityScale(1.0f);
			player->shape().calculateNormals();
			player->shape().calculateCenter();
			player->shape().getInertiaMoment();
			player->body()->setInertia(player->shape().getInertiaMoment());
			
		}

		if (InputManager::keyboard.isKeyPressed(KB_G))
		{
			ground->shape().addVertex(-20.0f, 5.5f);
			ground->shape().calculateNormals();
			ground->shape().calculateCenter();
			ground->shape().getInertiaMoment();

			ground->shape().addVertex(5.0f, 5.5f);
			ground->shape().calculateNormals();
			ground->shape().calculateCenter();
			ground->shape().getInertiaMoment();

			ground->shape().addVertex(10.0f, -10.0f);
			ground->shape().calculateNormals();
			ground->shape().calculateCenter();
			ground->shape().getInertiaMoment();

			ground->shape().addVertex(-20.0f, -10.0f);
			ground->shape().calculateNormals();
			ground->shape().calculateCenter();
			ground->shape().getInertiaMoment();

			ground->shape().calculateNormals();
			ground->shape().calculateCenter();
			ground->shape().getInertiaMoment();
			ground->body()->setInertia(0.0f);

			ground->body()->transform().setPosition(Vector2(0.0f, -10.0f));
		}
	

		PhysicsManager2D::update(dt);

		cam->setPosition(player->body()->transform().position());
		

		Shape2D attShape = *player->relativeShape();

//		RenderManager::drawDebugShape(shape.getVertices(), shape.vertexCount(), ColorRGBAf::green);
		RenderManager::drawDebugShape(attShape.getVertices(), attShape.vertexCount(), ColorRGBAf::blue);
		
		
	//	RenderManager::drawDebugCircle(relshape.center(), relshape.radius(), 32, ColorRGBAf::blue);
		RenderManager::drawDebugCircle(attShape.centerOfGravity(), 0.008f, 8, ColorRGBAf::blue);
		RenderManager::drawDebugCircle(attShape.center(), 0.008f, 8, ColorRGBAf::red);
		RenderManager::drawDebugCircle(attShape.getSupportPoint(Vector2::up), 0.008f, 32, ColorRGBAf::magenta);
		RenderManager::drawDebugShape((Vector2*)ground->relativeShape()->getVertices(), ground->relativeShape()->vertexCount(), ColorRGBAf::red);

		


		for (int i = 0; i < attShape.vertexCount(); i++)
		{
			i32 id = i + 1;
			id %= attShape.vertexCount();
			Vector2 face = attShape.getVertices()[id] - attShape.getVertices()[i];
			face = attShape.getVertices()[i] + face / 2.0f;

			Vector2 reducedNormal = attShape.getNormals()[i];
			reducedNormal *= 0.2f;

			RenderManager::drawDebugLine(face ,face
				+ reducedNormal, ColorRGBAf::red);

			Vector2 normalFace = Vector2::cross(-1.0f, attShape.getNormals()[i]);
			normalFace.normalize();
			normalFace *= 0.01f;

			Vector2 head[3];
			head[0] = face + reducedNormal * 1.07f;
			head[1] = face + reducedNormal + normalFace;
			head[2] = face + reducedNormal - normalFace;

			RenderManager::drawDebugShape(head, 3, ColorRGBAf::red);
			

			face = player->body()->transform().position();
			RenderManager::drawDebugLine(player->body()->transform().position(), 
				player->body()->transform().position() + player->body()->transform().basis().x(), ColorRGBAf::magenta);
			RenderManager::drawDebugLine(player->body()->transform().position(), 
				player->body()->transform().position() + player->body()->transform().basis().y(), ColorRGBAf::cyan);
			RenderManager::drawDebugLine(Vector2::zero, Vector2::up, ColorRGBAf::black);
			RenderManager::drawDebugLine(Vector2::zero, Vector2::right, ColorRGBAf::black);
			
		}
		RenderManager::render(m_cameras);
	}
}

