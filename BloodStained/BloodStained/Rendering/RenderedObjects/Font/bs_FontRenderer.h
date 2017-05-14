#ifndef BS_FONTRENDERER_H
#define	BS_FONTRENDERER_H

#include "../../bs_VertexBufferObject.h"
#include "../../../Containers/bs_Array.h"
#include "../../../Utilities/bs_String.h"
#include "../../../Math/bs_Vector.h"
#include "../../bs_Color.h"
#include "bs_Font.h"
#include "../../bs_Shader.h"


namespace bs
{
	class Camera2D;

	enum class FONT_ALIGNMENT
	{
		LEFT,
		RIGHT,
		CENTER
	};

	struct FontRegistry
	{
		String	string;
		Vector2 position;
		ColorRGBA32	color;
		Font*	font;
		FONT_ALIGNMENT alignment;
		ui32 size;
	};
	
	class FontRenderer
	{
	public:
		FontRenderer();
		~FontRenderer();

	private:
		FontRenderer(const FontRenderer& f);

	public:

		ERROR_ID	initialize();
		ERROR_ID	shutDown();

		//More for direct calling
		void	drawString(const char* string, const Vector2& position, const char* font, FONT_ALIGNMENT alignment, ui32 size, ColorRGBA32 color);
		//For calling from automated functions.
		void	drawString(const String& string, const Vector2& position, Font* font, FONT_ALIGNMENT alignment, ui32 size, ColorRGBA32 color);

		void	render(Camera2D* camera);

		void	setShader(Shader* shader);

	private:
		void	_updateCameraUniforms(Camera2D* camera);

		void	_generateVertices(const FontRegistry& registry);

		//Makes draw calls
		void	_draw(Camera2D* camera);

		//Upload sprite data to OpenGL
		void	_uploadData();

	public:
		VertexArrayObject	m_vao;
		VertexBufferObject	m_vbo;
		IndexBufferObject	m_ibo;

		Array<FontRegistry>	m_strings;
		Array<ui32>			m_batches;
		Shader*				m_shader;
	};
}
#endif // !BS_FONTRENDERER_H
