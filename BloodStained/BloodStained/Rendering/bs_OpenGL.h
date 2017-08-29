#ifndef _BS_OPENGL_H_
#define _BS_OPENGL_H_

#include <Utilities/bs_types.h>

#include "bs_Color.h"
#include "bs_OpenGLEnums.h"

namespace bs
{	
	class String;
	enum class SHADER_ATTRIB_TYPE;
	enum class ERROR_ID;

	

	class OpenGL
	{
	public:
		static	ui32	createShader(OPENGL_SHADER_TYPE type);
		static	void	deleteShader(ui32 id);

		static	void	shaderSource(ui32 id, int count, const char* source, i32 length);
		static	void	compileShader(ui32 id);
		static	bool	isCompilationSuccessful(ui32 id);
		static	String	getCompilationFailMessage(ui32 id);
		
		
		static	void	attachShader(ui32 program, ui32 shader);
		static  void	detachShader(ui32 program, ui32 shader);
		static  void	bindAttribLocation(ui32 program, ui32 index, const char* name);
		static	void	bindFragDataLocation(ui32 program, ui32 color, const char* name);

		static	ui32	createProgram();
		static  void	deleteProgram(ui32 id);
		static	void	useProgram(ui32 id);
		static  void	linkProgram(ui32 id);
		static	bool	isProgramLinkingSuccessful(ui32 id);
		static	String	getProgramLinkingFailMessage(ui32 id);


		static	void	clearColor(const ColorRGBAf& color); 
		static	void	clearColor(const ColorRGBA32& color);
		static	void	clear(); 

		static	void	genBuffers(int count, ui32* buffers);
		static	void	deleteBuffers(int count, ui32* buffers);
		static	void	bindBuffer(OPENGL_BUFFER_TYPE type, ui32 index);

		static	void	genVertexArrays(int count, ui32* buffers);
		static	void	deleteVertexArrays(int count, const ui32* buffers);

		static	void	enableVertexAttribArray(ui32 index);
		static	void	disableVertexAttribArray(ui32 index);
		static	void	vertexAttribPointer(ui32 index, int size, OPENGL_TYPE type,
			bool normalized, int stride, const void* pointer);

		static	void	drawArrays(OPENGL_PRIMITIVE mode, i32 first, int count);
		static	void	drawElements(OPENGL_PRIMITIVE mode, int count, OPENGL_TYPE type,
			const void* indices);

		static void		genTextures(int count, ui32* textures);
		static void		bindTexture(OPENGL_TEXTURE type, ui32 index);
		static void		deleteTextures(int count, ui32* textures);

		static void		activeTexture(ui32 index);
		static void		texImage2D(OPENGL_TEXTURE type, i32 level, i32 internalFormat, int width,
			int height, i32 border, OPENGL_COLOR_FORMAT format, OPENGL_PIXEL_STORAGE pixelStorage, void* data);

		static void		pixelStorei(OPENGL_ALIGNMENT alignment, i32 param);
		static void		texParameteri(OPENGL_TEXTURE type, OPENGL_TEXTURE_PARAMETER_NAME parameterName, OPENGL_TEXTURE_PARAMETER param);

		//@param transpose only available for matrices.
		static ERROR_ID	uniform(ui32 shaderID, const char* name, SHADER_ATTRIB_TYPE type, void* data, bool transpose);
	};
}
#endif // !_BS_OPENGL_H_