#ifndef BS_FONTSHADER_H
#define	BS_FONTSHADER_H

#include "../../bs_ShaderScript.h"

namespace bs
{
	class FontShader : public ShaderScript
	{
	public:
		FontShader();
		~FontShader();

		static FontShader instance;

		void initialize();
	};
}

#endif // !BS_FONTSHADER_H
