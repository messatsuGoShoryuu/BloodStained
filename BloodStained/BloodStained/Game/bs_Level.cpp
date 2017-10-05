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
		static Transform2D transform = Transform2D();

		Camera2D* cam = dynamic_cast<Camera2D*>(m_cameras[0]);

		Vector2 pos2 = cam->screenToWorld(Vector2(InputManager::mouse.getX(), InputManager::mouse.getY()));

		static Shape2D shape;

		if (InputManager::keyboard.isKeyPressed(KB_R)) shape = Shape2D();

		if (InputManager::mouse.isButtonPressed(MOUSE_BUTTON_1))
		{
			shape.addVertex(makeVector2RelativeToBasis(transform, pos2));
		}

		if (InputManager::keyboard.isKeyHeld(KB_RIGHTARROW)) transform.translate(Vector2::right * (dt));
		if (InputManager::keyboard.isKeyHeld(KB_LEFTARROW)) transform.translate(Vector2::right * (-dt));
		if (InputManager::keyboard.isKeyHeld(KB_UPARROW)) transform.translate(Vector2::up * dt);
		if (InputManager::keyboard.isKeyHeld(KB_DOWNARROW)) transform.translate(Vector2::up * (-dt));

		if (InputManager::keyboard.isKeyHeld(KB_S)) transform.multScale(Vector2(1.1f, 1.1f));
		if (InputManager::keyboard.isKeyHeld(KB_W)) transform.multScale(Vector2(0.9f, 0.9f));

		if (InputManager::keyboard.isKeyHeld(KB_A)) transform.rotate(-(BS_PI / 180.0f));
		if (InputManager::keyboard.isKeyHeld(KB_D)) transform.rotate(BS_PI / 180.0f);
		
		Shape2D staticShape = Shape2D();
		staticShape.addVertex(-0.8f, -0.3f);
		staticShape.addVertex(-0.9f, 0.5);
		staticShape.addVertex(-0.7f, 0.5f);
		staticShape.addVertex(-0.6f, -0.5f);
		staticShape.calculateNormals();
		staticShape.calculateCenter();

		Shape2D attShape = attachShapeToBasis(transform, shape);
 
		gjk2D::Collision collision = gjk2D::testCollision(staticShape, attShape);
		if (collision.collided)
		{
			transform.translate(collision.contact.mtd[0].normal * collision.contact.mtd[0].penetration * 0.8f);
		}
		attShape = attachShapeToBasis(transform, shape);
	//	if (collision.collided)
	//		transform.translate(collision.contact.mtd[0].normal * collision.contact.mtd[0].penetration/2.0f);

//		RenderManager::drawDebugShape(shape.getVertices(), shape.vertexCount(), ColorRGBAf::green);
		RenderManager::drawDebugShape(attShape.getVertices(), shape.vertexCount(), ColorRGBAf::blue);
		RenderManager::drawDebugShape(staticShape.getVertices(), staticShape.vertexCount(), collision.collided ? ColorRGBAf(1.0,0.4,0.2,1.0) : ColorRGBAf(0.5,0.5,0.0,1.0));
		
	//	RenderManager::drawDebugCircle(relshape.center(), relshape.radius(), 32, ColorRGBAf::blue);
		RenderManager::drawDebugCircle(attShape.center(), 0.008f, 8, ColorRGBAf::blue);
		RenderManager::drawDebugCircle(attShape.getSupportPoint(Vector2::up), 0.008f, 32, ColorRGBAf::magenta);


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
			

			face = transform.position();
			RenderManager::drawDebugLine(transform.position(), transform.position() + transform.basis().x(), ColorRGBAf::magenta);
			RenderManager::drawDebugLine(transform.position(), transform.position() + transform.basis().y(), ColorRGBAf::cyan);
			RenderManager::drawDebugLine(Vector2::zero, Vector2::up, ColorRGBAf::black);
			RenderManager::drawDebugLine(Vector2::zero, Vector2::right, ColorRGBAf::black);
			
		}
		RenderManager::render(m_cameras);
		
	}
}

