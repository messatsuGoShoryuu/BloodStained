#include "bs_Error.h"
#include "bs_String.h"
#include "../Globals/bs_globals.h"
#include "../Rendering/bs_OpenGLWindow.h"


namespace bs
{
	ERROR_ID	Error::fatalError(ERROR_ID error, String cause)
	{
		String fatalErrorString = "Fatal Error : ";
		fatalErrorString += errorString(error);
		MessageBox(g_game.window()->hwnd(), cause.utf8(), fatalErrorString.utf8(), MB_OK | MB_ICONERROR);
		g_game.quit();
		return error;
	}

	const char*	Error::errorString(ERROR_ID id)
	{
		switch (id)
		{
			case ERROR_ID::FAIL_FRAG_SHADER_LOAD: 
				return "Failed to load fragment shader";
			case ERROR_ID::FAIL_SHADER:
				return "Failed to load shader";
			case ERROR_ID::FAIL_VERT_SHADER_LOAD:
				return "Failed to load vertex shader";
			case ERROR_ID::INVALID_FILE: 
				return "Invalid file";
			case ERROR_ID::INVALID_FORMAT:
				return "Invalid format";
			case ERROR_ID::INVALID_INDEX:
				return "Invalid index";
			case ERROR_ID::FAIL_GL_GENVERTEXARRAY:
				return "::glGenVertexArray failed";
			case ERROR_ID::FAIL_GL_GENBUFFERS:
				return "::glGenBuffers failed";
			case ERROR_ID::UNDEFINED:
				return "Undefined error";
			case ERROR_ID::NONE:
				return "No error";
			default: return "No error";
		}
	}
}