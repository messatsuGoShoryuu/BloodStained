#ifndef SPRITETEST_H
#define SPRITETEST_H

#include <Game/bs_Level.h>
#include <Game/bs_LevelScript.h>
#include <GL\glew.h>

#include <Rendering/bs_VertexBufferObject.h>
#include <Physics\3D\Collisions\bs_Primitives.h>
#include <Rendering/bs_Texture2D.h>
#include <Game/Entity/Component/Basic/bs_Transform3D.h>

namespace bs
{
	class Camera2D;
	class Shader;
	class Sprite;
}
class SpriteTest : public bs::LevelScript
{
public:
	SpriteTest();
	SpriteTest(const SpriteTest& t);
	~SpriteTest();

	void execute(bs::Level* l, real dt);
	void initialize(bs::Level* l);
	void render(bs::Level* l);
	void shutDown();

private:

	bs::Camera2D*	m_camera;
	f32	m_time;

	bool m_initialized;

	bs::Sprite* m_sprite;
};

#endif