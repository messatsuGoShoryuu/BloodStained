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
		FAIL_FRAG_SHADER_LOAD,
		FAIL_VERT_SHADER_LOAD,
		FAIL_SHADER,
		FAIL_GL_GENVERTEXARRAY,
		FAIL_GL_GENBUFFERS,
		UNDEFINED
	};
	class String;

	class Error
	{
	public:
		static ERROR_ID fatalError(ERROR_ID id, String cause);
		static const char* errorString(ERROR_ID id);
	};
}
#endif // !BS_ERROR_H
