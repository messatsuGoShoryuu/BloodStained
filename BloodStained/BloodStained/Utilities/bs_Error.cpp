#include "bs_Error.h"
#include "bs_String.h"

namespace bs
{
	const char * getErrorString(ERROR_ID id)
	{
		switch (id)
		{
		case	ERROR_ID::NONE:
			return "No error.";
		case	ERROR_ID::WINDOW_CLASS_REGISTRATION_FAILED:
			return "Window class registration failed.";
		case	ERROR_ID::WINDOW_CREATION_FAILED:
			return "Window creation failed.";
		case ERROR_ID::WINDOWS_RAWINPUT_FAIL:
			return "Couldn't retrieve RAW INPUT from Win32 API.";
		case ERROR_ID::WINDOWS_RID_REGISTRATION_FAIL:
			return "Couldn't register Raw Input Device.";
		case	ERROR_ID::DC_NOT_FOUND:
			return "Device context not found.";
		case	ERROR_ID::GL_DC_FAIL:
			return "OpenGL Context creation failed.";
		case	ERROR_ID::PIXEL_FORMAT_FAIL:
			return "Pixel format could not be chosen.";
		case	ERROR_ID::WGL_EXTENSION_LOAD_FAIL:
			return "WGL extension could not be loaded.";
		case	ERROR_ID::LOAD_RESOURCE_FAIL:
			return "Resource could not be loaded.";
		case	ERROR_ID::FILE_SIZE_0:
			return "Requested file has a size of 0 bytes.";
		case	ERROR_ID::SHADER_TEXT_NOT_FOUND:
			return "Source for shader failed to load.";
		case	ERROR_ID::SHADER_CREATION_FAIL:
			return "Shader could not be created.";
		case	ERROR_ID::SHADER_COMPILATION_FAIL:
			return "Shader couldn't be compiled.";
		case ERROR_ID::SHADER_NOT_FOUND:
			return "Shader doesn't exist or failed to be loaded.";
		case ERROR_ID::GL_PROGRAM_CREATION_FAIL:
			return "Shader program couldn't be created.";
		case ERROR_ID::GL_PROGRAM_LINKING_FAIL:
			return "OpenGL shader program could not be linked.";
		case ERROR_ID::GL_UNIFORM_NOT_FOUND:
			return "Uniform variable not found in currently bound shader.";
		case ERROR_ID::GL_TEXTURE_CREATION_FAIL:
			return "OpenGL texture couldn't be created";
		case ERROR_ID::TEXTURE_CREATION_FAIL:
			return "Texture2D::create has returned with error.";
		case ERROR_ID::QUAD_RENDERER_INIT_FAIL:
			return "Quad renderer initialization failed.";
		case ERROR_ID::IMAGE_LOADING_FAIL:
			return "Image could not be loaded.";
		case ERROR_ID::IMAGE_FORMAT_NOT_SUPPORTED:
			return "Image format not supported.";
		case ERROR_ID::VBO_INIT_FAIL:
			return "Vertex buffer object couldn't be created.";
		case ERROR_ID::VAO_INIT_FAIL:
			return "Vertex array object couldn't be created.";
		case ERROR_ID::EBO_INIT_FAIL:
			return "Element buffer object couldn't be created.";
		case ERROR_ID::SPRITERENDERER_INIT_FAIL:
			return "SpriteRenderer initalization failed.";
		case ERROR_ID::SPRITERENDERER_SHUTDOWN_FAIL:
			return "SpriteRenderer shut down failed.";
		}
		return nullptr;
	}


	ERROR_ID fatalError(ERROR_ID id, String info)
	{
		return _FATAL_ERROR_INFO_(id, info);
	}

}