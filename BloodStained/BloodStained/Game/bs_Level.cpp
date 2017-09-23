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
		
		Shape2D attshape = attachShapeToBasis(transform, shape);
		Shape2D relshape = makeShapeRelativeToBasis(transform, shape);
 
		RenderManager::drawDebugShape(shape.getVertices(), shape.vertexCount(), ColorRGBAf::green);
		RenderManager::drawDebugShape(relshape.getVertices(), shape.vertexCount(), ColorRGBAf::blue);
		RenderManager::drawDebugShape(attshape.getVertices(), shape.vertexCount(), ColorRGBAf::black);
		for (int i = 0; i < relshape.vertexCount(); i++)
		{
			i32 id = i + 1;
			id %= relshape.vertexCount();
			Vector2 face = relshape.getVertices()[id] - relshape.getVertices()[i];
			face = relshape.getVertices()[i] + face / 2.0f;

			Vector2 reducedNormal = relshape.getNormals()[i];
			reducedNormal *= 0.2f;

			RenderManager::drawDebugLine(face ,face
				+ reducedNormal, ColorRGBAf::red);

			Vector2 normalFace = Vector2::cross(-1.0f, relshape.getNormals()[i]);
			normalFace.normalize();
			normalFace *= 0.01f;

			Vector2 head[3];
			head[0] = face + reducedNormal * 1.07f;
			head[1] = face + reducedNormal + normalFace;
			head[2] = face + reducedNormal - normalFace;

			RenderManager::drawDebugShape(head, 3, ColorRGBAf::red);
			RenderManager::drawDebugCircle(relshape.center(), 0.008f, 8, ColorRGBAf::blue);

			face = transform.position();
			RenderManager::drawDebugLine(transform.position(), transform.position() + transform.basis().x(), ColorRGBAf::magenta);
			RenderManager::drawDebugLine(transform.position(), transform.position() + transform.basis().y(), ColorRGBAf::cyan);
			RenderManager::drawDebugLine(Vector2::zero, Vector2::up, ColorRGBAf::yellow);
			RenderManager::drawDebugLine(Vector2::zero, Vector2::right, ColorRGBAf::yellow);
			
		}
		RenderManager::render(m_cameras);
		
	}
}

