#ifndef _BS_OPENGL_H_
#define _BS_OPENGL_H_

#include <Utilities/bs_types.h>

#include "bs_Color.h"

namespace bs
{	
	class String;
	enum class SHADER_ATTRIB_TYPE;
	enum class ERROR_ID;

	enum class OPENGL_SHADER_TYPE
	{
		FRAGMENT = 0x8B30,
		VERTEX,
	};

	enum class OPENGL_BUFFER_TYPE
	{
		ARRAY = 0x8892,
		ATOMIC_COUNTER = 0x92C0,
		COPY_READ = 0x8F36,
		COPY_WRITE = 0x8F37,
		DISPATCH_INDIRECT = 0x90EE,
		DRAW_INDIRECT = 0x8F3F,
		ELEMENT_ARRAY = 0x8893,
		PIXEL_PACK = 0x88EB,
		PIXEL_UNPACK = 0x88EC,
		QUERY = 0x9192,
		SHADER_STORAGE = 0x90D2,
		TEXTURE = 0x8C2A,
		TRANSFORM_FEEDBACK = 0x8C8E,
		UNIFORM = 0x8A11
	};

	enum class OPENGL_TYPE
	{
		FLOAT = 0x1406,
		INT = 0x1404,
		UINT = 0x1405,
		BYTE = 0x1400,
		UBYTE = 0x1401,
		SHORT = 0x1402,
		USHORT = 0x1403
	};

	enum class OPENGL_PRIMITIVE
	{
		POINTS = 0x0000,
		LINE_STRIP = 0x0003,
		LINE_LOOP = 0x0002,
		LINES = 0x0001,
		LINE_STRIP_ADJACENCY = 0x000B,
		LINE_ADJACENCY = 0x000A,
		TRIANGLE_STRIP = 0x0005,
		TRIANGLE_FAN = 0x0006,
		TRIANGLES = 0x0004,
		TRIANGLE_STRIP_ADJACENCY = 0x000D,
		TRIANGLES_ADJACENCY = 0x000C,
		PATCHES = 0x000E,
	};

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

		//@param transpose only available for matrices.
		static ERROR_ID	uniform(ui32 shaderID, const char* name, SHADER_ATTRIB_TYPE type, void* data, bool transpose);
	};
}
#endif // !_BS_OPENGL_H_