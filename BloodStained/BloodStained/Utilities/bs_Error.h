#ifndef BS_ERROR_H
#define BS_ERROR_H




namespace bs
{
	enum class ERROR_ID
	{
		NONE,
		INVALID_INDEX,
		INVALID_POINTER,
		INVALID_FILE,
		INVALID_FORMAT,
	};
	class String;

	class Error
	{
		static bool fatalError()
	};
}
#endif // !BS_ERROR_H
