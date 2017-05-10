#include "bs_ShaderScript.h"
#include "../Globals/bs_globals.h"

namespace bs
{
	ShaderScript::ShaderScript()
	{
		g_shaderManager.addShaderScript(this);
	}

	ShaderScript::ShaderScript(const ShaderScript& s)
	{

	}

	ShaderScript::~ShaderScript()
	{

	}

	void ShaderScript::initialize()
	{

	}




}