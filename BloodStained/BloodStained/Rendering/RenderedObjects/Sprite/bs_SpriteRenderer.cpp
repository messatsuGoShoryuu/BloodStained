#include "../../../Globals/bs_globals.h"
#include "../../bs_Camera2D.h"

#include "../../bs_Shader.h"
#include "../../bs_Texture2D.h"

namespace bs
{
	SpriteRenderer::SpriteRenderer()
		:m_currentShader(nullptr),
		m_sprites(4096)
	{

	}


	SpriteRenderer::~SpriteRenderer()
	{

	}

	ERROR_ID	SpriteRenderer::initialize()
	{
		ERROR_ID err = ERROR_ID::NONE;

		err = m_vao.initialize();
		if (err != ERROR_ID::NONE) return Error::fatalError(err, "SpriteRenderer Vertex Array Object initialization failed");
		err = m_ibo.initialize();
		if (err != ERROR_ID::NONE) return Error::fatalError(err, "SpriteRenderer Index Buffer Object initialization failed");
		err = m_vbo.initialize();
		if (err != ERROR_ID::NONE) return Error::fatalError(err, "SpriteRenderer Vertex Buffer Object initialization failed");

		m_vao.bind();
		m_ibo.bind();
		m_vbo.bind();
		
		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 2, offsetof(Vertex2D_PUC, position), GL_FALSE);
		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 2, offsetof(Vertex2D_PUC, uv), GL_FALSE);
		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 4, offsetof(Vertex2D_PUC, color), GL_FALSE);
		

		m_vao.unbind();
		m_ibo.unbind();
		m_vbo.unbind(); 

		return ERROR_ID::NONE;
	}

	ERROR_ID	SpriteRenderer::shutDown()
	{
		m_spriteHandles.reset();
		m_batches.reset();
		m_sprites.destroy();
		m_vbo.shutDown();
		m_ibo.shutDown();

		return ERROR_ID::NONE;
	}

	void	SpriteRenderer::_uploadData()
	{
		//Fetch indices for iteration
		ui32 firstIndex = m_sprites.firstIndex();
		ui32 lastIndex = m_sprites.lastIndex();

		//Fetch pointers for sorting
		for (ui32 i = firstIndex; i <= lastIndex; i++)
		{
			if (m_sprites[i])
			{
				//Prepare sprite.
				if(m_sprites[i]->isDirty()) m_sprites[i]->_setupVertices();
				//Add to list.
				m_spriteHandles.add(m_sprites[i]);
			}
		}

		//Create the first batch
		SpriteBatch s;
		ui32 currentBatch = m_batches.add(s);
		m_batches[currentBatch].first = 0;
		m_batches[currentBatch].last = 0;
		m_batches[currentBatch].shader = (Shader*)m_spriteHandles[0]->shader();
		m_batches[currentBatch].texture = m_spriteHandles[0]->texture();

		ui32 count = m_spriteHandles.count();

		//Iterate through sprites
		for (ui32 i = 0; i < count; i++)
		{
			//When there is a texture or shader change
			if (m_batches[currentBatch].texture != m_spriteHandles[i]->texture()
				|| m_batches[currentBatch].shader != m_spriteHandles[i]->shader())
			{
				//Create new batch
				currentBatch = m_batches.add(s);
				m_batches[currentBatch].first = i;
				m_batches[currentBatch].last = i;
				m_batches[currentBatch].shader = (Shader*)m_spriteHandles[i]->shader();
				m_batches[currentBatch].texture = m_spriteHandles[i]->texture();
			}
			else if(m_batches[currentBatch].last + 2 != count) m_batches[currentBatch].last++;

			ui32 offset = i * 4;

			//Upload indices to draw

			//First triangle
			m_ibo.addData(offset);
			m_ibo.addData(offset + 1);
			m_ibo.addData(offset + 2);

			//Second triangle
			m_ibo.addData(offset + 2);
			m_ibo.addData(offset + 3);
			m_ibo.addData(offset);

			//Upload data to vbo.
			for (ui32 j = 0; j < 4; j++)
			{
				m_vbo.addData<Vertex2D_PUC>(m_spriteHandles[i]->vertices()[j]);
			}
		}

		m_vbo.upload(GL_DYNAMIC_DRAW);
		m_ibo.upload(GL_DYNAMIC_DRAW);
	}

	void	SpriteRenderer::_draw(Camera2D* camera)
	{
		//Initialize values
		ui32 count = m_spriteHandles.count();
		ui32 currentBatch = 0;
		
		//Fetch the first shader
		Shader* shader = m_batches[currentBatch].shader;
		Texture2D texture = m_batches[currentBatch].texture;

		//Bind first texture and shader
		texture.bind();
		shader->bind();
		
		//Accumulate rendered element count
		ui32 totalElementCount = 0;

		//For each sprite
		for (ui32 i = 0; i < count; i++)
		{
			//If a batch is completed
			if (i >= m_batches[currentBatch].last)
			{
				//Calculate element count per batch.
				ui32 elementCount = (m_batches[currentBatch].last - m_batches[currentBatch].first + 1) * 6;

				//Upload uniform data to the shader
				_updateCameraUniforms(camera, shader);

				//Make draw call (index buffer object)
				glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_SHORT, (void*)(totalElementCount * sizeof(GLushort)));
				
				//Update total element count offset
				totalElementCount += elementCount;

				//Go to the next batch
				currentBatch++;

				//Did we do all batches?
				if (currentBatch >= m_batches.count()) break;

				//Unbind previous stuff.
				shader->unbind();
				texture.unbind();

				//Update and bind shader and texture.
				shader = m_batches[currentBatch].shader;
				texture = m_batches[currentBatch].texture;

				shader->bind();
				texture.bind();
			}
		}
		shader->unbind();
		texture.unbind();
	}

	void	SpriteRenderer::render(Camera2D* camera)
	{
		//Bind the big vertex buffer object
		m_vbo.bind();
		//Bind the big index buffer object
		m_ibo.bind();

		//GL buffer data
		_uploadData();

		//Nothing more to do with the vbo
		m_vbo.unbind();

		//We need vertex array pointers to specify how vertices are drawn
		m_vao.bind();
		
		//Draw with current camera.
		_draw(camera);

		//Cleanup
		m_vao.unbind();
		m_ibo.clearData();
		m_vbo.clearData();

		m_spriteHandles.clear();
		m_batches.clear();
	}

	void		SpriteRenderer::_updateCameraUniforms(Camera2D* camera, Shader* shader)
	{
		shader->beginScope();
		shader->uploadUniform((void*)&(camera->view()));
		shader->uploadUniform((void*)&(camera->projection()));
		shader->uploadUniform(0);
	}


	Sprite*		SpriteRenderer::addSprite(String fileName)
	{
		//Add sprite to linked array
		Sprite* s = m_sprites.construct();

		//Find and set texture.
		s->setTexture(g_resourceManager.loadImage(fileName));
		s->setShader(&g_shaderManager.getShaderMap()["DefaultSpriteShader"]);

		//Store inverse screen height
		f32 k = 1.0f / g_screen.height();

		//Calculate width (pixels)
		s->setWidth(s->texture().width() * k);
		s->setHeight(s->texture().height() * k);

		//Update vertices.
		s->_setupVertices();
		return s;
	}

	void		SpriteRenderer::removeSprite(Sprite* sprite)
	{
		m_sprites.remove(sprite);
	}
}