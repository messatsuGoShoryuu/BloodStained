#include "bs_WindowsError.h"
#include <Utilities/bs_Error.h>
#include <Utilities/bs_String.h>
#include <Windows.h>

namespace bs
{
	ERROR_ID winFatalError(ERROR_ID id)
	{
		MessageBox(NULL, getErrorString(id), "Fatal Error!",  MB_OK | MB_ICONERROR);
		return id;
	}

	ERROR_ID winFatalError(ERROR_ID id, const String& info)
	{
		String concat = getErrorString(id);
		concat += String("\n\n") + info;

		MessageBox(NULL, concat.utf8() , "Fatal Error!", MB_OK | MB_ICONERROR);
		return id;
	}

	ERROR_ID winWarning(ERROR_ID id)
	{
		MessageBox(NULL, getErrorString(id), "Warning :", MB_OK | MB_ICONWARNING);
		return id;
	}
}
