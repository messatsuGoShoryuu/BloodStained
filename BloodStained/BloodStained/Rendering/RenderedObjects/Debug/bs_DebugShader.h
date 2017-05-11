#ifndef BS_DEBUGSHADER_H
#define BS_DEBUGSHADER_H


#include "../../bs_ShaderScript.h"

namespace bs
{
	class DebugDrawShader : public ShaderScript
	{
	public:
		DebugDrawShader();
		~DebugDrawShader();

		static DebugDrawShader instance;

		void initialize();
	};
}
#endif // !BS_DEBUGSHADER_H
