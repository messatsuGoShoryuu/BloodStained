#ifndef BS_SHADERSCRIPT_H
#define BS_SHADERSCRIPT_H

#include "../Utilities/bs_String.h"

namespace bs
{
	//Interface to create shaders.
	class ShaderScript
	{
	public:
		ShaderScript();
		ShaderScript(const ShaderScript& s);
		virtual	~ShaderScript();
		virtual void	initialize();
		String	name;
	};
}

#endif // !BS_SHADERSCRIPT_H
