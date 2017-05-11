#ifndef BS_SPRITERENDERER_H
#define	BS_SPRITERENDERER_H

#include "bs_Sprite.h"
#include "../../bs_VertexBufferObject.h"
#include "../../../Containers/bs_LinkedArray.h"
#include "../../../Utilities/bs_Error.h"

namespace bs
{
	class	Camera2D;
	class	Shader;
	class	String;
	
	struct SpriteBatch
	{
		Texture2D	texture;
		Shader*		shader;
		ui32		first;
		ui32		last;
	};

	class SpriteRenderer
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();


	private:
		SpriteRenderer(const SpriteRenderer& s);

	public:
		//Manual init
		ERROR_ID	initialize();

		//Manual shut down
		ERROR_ID	shutDown();


		//Call render for each camera
		void	render(Camera2D* camera);

		

		//Add a sprite
		Sprite*	addSprite(String fileName);

		//Remove a sprite
		void	removeSprite(Sprite* sprite);

		//Camera uniforms
	private:
		void	_updateCameraUniforms(Camera2D* camera, Shader* shader);

		//Makes draw calls
		void	_draw(Camera2D* camera);

		//Upload sprite data to OpenGL
		void	_uploadData();

	private:
		VertexArrayObject	m_vao;
		VertexBufferObject	m_vbo;
		IndexBufferObject	m_ibo;

		//Actual sprite objects.
		LinkedArray<Sprite>	m_sprites;
		//Handles used for sorting.
		Array<Sprite*>		m_spriteHandles;
		//Batches
		Array<SpriteBatch>	m_batches;

		Texture2D			m_currentTexture;
		Shader*				m_currentShader;
	};
}
#endif // !BS_SPRITERENDERER_H
