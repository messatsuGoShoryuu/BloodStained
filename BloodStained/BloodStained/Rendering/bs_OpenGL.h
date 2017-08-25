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

	class OpenGL
	{
	public:
		static	ui32	createShader(OPENGL_SHADER_TYPE type);
		static	void	shaderSource(ui32 id, int count, const char* source, i32 length);
		static	void	compileShader(ui32 id);
		static	bool	isCompilationSuccessful(ui32 id);
		static	String	getCompilationFailMessage(ui32 id);
		static	void	deleteShader(ui32 id);

	};
}
#endif // !_BS_OPENGL_H_