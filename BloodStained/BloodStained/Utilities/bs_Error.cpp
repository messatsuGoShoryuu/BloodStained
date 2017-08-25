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
		}
		return nullptr;
	}


	ERROR_ID fatalError(ERROR_ID id, String info)
	{
		return _FATAL_ERROR_INFO_(id, info);
	}

}