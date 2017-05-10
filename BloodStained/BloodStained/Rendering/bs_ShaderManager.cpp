#include "bs_ShaderManager.h"
#include "bs_ShaderScript.h"

namespace bs
{
	ShaderManager::ShaderManager()
	{

	}

	ShaderManager::~ShaderManager()
	{

	}

	bool ShaderManager::initialize()
	{
		//Initialize all shader scripts
		ui32 shaderCount = m_shaderScripts.count();
		std::cout << "Shader count  = " <<shaderCount << std::endl;
		for (ui32 i = 0; i < shaderCount; i++)m_shaderScripts[i]->initialize();
		return true;
	}

	bool ShaderManager::shutDown()
	{
		ui32 shaderCount = m_shaderScripts.count();
		for (ui32 i = 0; i < shaderCount; i++) if(m_shaderScripts[i])delete m_shaderScripts[i];

		m_shaderScripts.reset();
		m_shaderSources.reset();
		m_shaders.reset();
		return true;
	}

	void ShaderManager::addShaderScript(ShaderScript* s)
	{
		m_shaderScripts.add(s);
	}
}