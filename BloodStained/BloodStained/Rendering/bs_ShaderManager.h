#ifndef _BS_SHADERMANAGER_H_
#define _BS_SHADERMANAGER_H_

#include <Utilities/bs_types.h>

namespace bs
{
	enum class ERROR_ID;
	struct ShaderCompilationData;

	class ShaderManager
	{
	public:
		static	ERROR_ID	initialize();
		static	ERROR_ID	shutDown();

	private:
		static	void		_compileShaders();
		static	ERROR_ID	_compileShader(const ShaderCompilationData& data);
		static	void		_extractShaderFromSplittedString(const class String& splittedString,
			class ShaderScriptResource& r, ui32& current, String& out);
		
	};
}

#endif // !_BS_SHADERMANAGER_H_