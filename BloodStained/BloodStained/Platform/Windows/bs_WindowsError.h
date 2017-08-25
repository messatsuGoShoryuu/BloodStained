#ifndef _BS_WINDOWS_ERROR_
#define	_BS_INDOWS_ERROR_

namespace bs
{
	enum class ERROR_ID;
	class String;

	ERROR_ID	winFatalError(ERROR_ID id);
	ERROR_ID	winFatalError(ERROR_ID id, const String& info);
	ERROR_ID	winWarning(ERROR_ID id);
}

#endif // !_WINDOWS_ERROR_INCLUDED_