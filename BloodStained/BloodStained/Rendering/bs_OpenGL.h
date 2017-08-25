#ifndef _BS_OPENGL_H_
#define _BS_OPENGL_H_

#include <Utilities/bs_types.h>

#include <Platform/Windows/bs_WindowsOpenGL.h>

namespace bs
{	
	class String;

	enum class OPENGL_SHADER_TYPE
	{
		FRAGMENT = 0x8B30,
		VERTEX,
	};

	enum class OPENGL_ATTRIBUTE_TYPE
	{

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
		
	};
}
#endif // !_BS_OPENGL_H_