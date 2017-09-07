#ifndef _BS_ERROR_H_
#define _BS_ERROR_H_


#include <Platform/bs_Platform.h>
#include <Platform/Windows/bs_WindowsError.h>

#ifdef BS_WINDOWS
#define	_FATAL_ERROR_(id) winFatalError(id);
#define _FATAL_ERROR_INFO_(id,info) winFatalError(id,info);
#define _WARNING_(id) winWarning(id);
#define _GET_ERROR_STRING_(id) winGetErrorString(id);
#endif


namespace bs
{
	enum class ERROR_ID
	{
		NONE,
		WINDOW_CLASS_REGISTRATION_FAILED,
		WINDOW_CREATION_FAILED,
		DC_NOT_FOUND,
		PIXEL_FORMAT_FAIL,
		GL_DC_FAIL,
		WGL_EXTENSION_LOAD_FAIL,
		LOAD_RESOURCE_FAIL,
		FILE_SIZE_0,
		SHADER_TEXT_NOT_FOUND,
		SHADER_CREATION_FAIL,
		SHADER_COMPILATION_FAIL,
		GL_PROGRAM_CREATION_FAIL,
		GL_PROGRAM_LINKING_FAIL,
		GL_UNIFORM_NOT_FOUND,
		GL_TEXTURE_CREATION_FAIL,
		TEXTURE_CREATION_FAIL,
		QUAD_RENDERER_INIT_FAIL,
		IMAGE_LOADING_FAIL,
		IMAGE_FORMAT_NOT_SUPPORTED,
		VBO_INIT_FAIL,
		VAO_INIT_FAIL,
		IBO_INIT_FAIL,
		SPRITERENDERER_INIT_FAIL,
		SPRITERENDERER_SHUTDOWN_FAIL,
	};

	inline	ERROR_ID	fatalError(ERROR_ID id) { return _FATAL_ERROR_(id); }
	ERROR_ID	fatalError(ERROR_ID id, String info);
	inline	ERROR_ID	warning(ERROR_ID id) { return _WARNING_(id); }
	const char* getErrorString(ERROR_ID id);
	
}
#endif // !_BS_ERROR_H_