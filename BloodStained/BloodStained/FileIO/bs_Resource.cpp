#include "bs_Resource.h"
#include "bs_FileSystem.h"
#include <Utilities/bs_Error.h>

namespace bs
{
	Resource::Resource()
		:m_isLoaded(false),
		m_type(RESOURCE_TYPE::NONE)
	{

	}

	Resource::Resource(RESOURCE_TYPE type)
		:m_isLoaded(false),
		m_type(type)
	{

	}

	Resource::Resource(const Resource& r)
		:m_isLoaded(r.m_isLoaded),
		m_type(r.m_type),
		m_fileName(r.m_fileName)
	{

	}

	Resource::~Resource()
	{

	}


	TextResource::TextResource()
		:Resource(RESOURCE_TYPE::TEXT)
	{
		
	}

	TextResource::TextResource(const TextResource& t)
		: Resource(t),
		m_data(t.m_data)
	{

	}

	TextResource::~TextResource()
	{

	}

	ERROR_ID TextResource::load()
	{
		if (m_isLoaded) return ERROR_ID::NONE;
		FileInfo file = FileSystem::open(m_fileName);

		if (file.size == 0)
		{
			m_data.clearFromMemory();
			return ERROR_ID::FILE_SIZE_0;
		}
		
		m_data.clearFromMemory();
		
		m_data.resize(file.size + 1);
		
		if (!FileSystem::read(file, &m_data[0]))
		{
			m_data.clearFromMemory();
			return ERROR_ID::LOAD_RESOURCE_FAIL;
		}

		FileSystem::close(file);
		m_data.add(NULL_CHARACTER);
		m_isLoaded = true;

		return ERROR_ID::NONE;
	}

	ERROR_ID TextResource::unload()
	{
		m_data.clearFromMemory();
		return ERROR_ID::NONE;
	}


	ShaderScriptResource::ShaderScriptResource()
	{
		m_type = RESOURCE_TYPE::SHADER_SCRIPT;
	}

	ShaderScriptResource::ShaderScriptResource(const ShaderScriptResource & s)
		:TextResource(s)
	{

	}

	void ShaderScriptResource::compile()
	{
		
	}

}