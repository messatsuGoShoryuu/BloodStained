#include "bs_Resource.h"
#include "bs_FileSystem.h"

#include "../Rendering/bs_Texture2D.h"
#include "bs_ImageLoader.h"

#include "../Globals/bs_globals.h"
#include "../Rendering/RenderedObjects/Font/bs_Font.h"

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

	bool Resource::_loadError()
	{
		return true;
	}


	TextResource::TextResource()
		:Resource(RESOURCE_TYPE::TEXT)
	{
		
	}

	TextResource::TextResource(const TextResource& t)
		: Resource(t)
	{

	}

	TextResource::~TextResource()
	{

	}

	bool TextResource::load()
	{
		if (m_isLoaded) return false;
		std::cout << "Load" << std::endl;
		FileInfo file = FileSystem::open(m_fileName);

		if (file.size == 0)
		{
			std::cout << "File size is 0" << std::endl;
			m_data.clearFromMemory();
			return _loadError();
		}
		
		m_data.clearFromMemory();
		
		m_data.resize(file.size + 1);
		
		if (!FileSystem::read(file, &m_data[0]))
		{
			std::cout << "File reading failed" << std::endl;
			m_data.clearFromMemory();
			return _loadError();
		}

		FileSystem::close(file);
		m_data.add(NULL_CHARACTER);
		m_isLoaded = true;

		return false;
	}

	bool TextResource::unload()
	{
		m_data.clearFromMemory();
		return true;
	}


	ImageResource::ImageResource()
		:Resource(RESOURCE_TYPE::IMAGE)
	{

	}

	ImageResource::ImageResource(const ImageResource& t)
		: Resource(t)
	{

	}

	ImageResource::~ImageResource()
	{

	}

	bool ImageResource::load()
	{
		if (m_isLoaded) return false;

		FileInfo file = FileSystem::open(m_fileName);

		if (file.size == 0)
		{
			std::cout << "File size is 0" << std::endl;
			return _loadError();
		}

		//Create buffer
		byte*	rawBuffer = (byte*)BS_Malloc(file.size);
		if (!FileSystem::read(file, rawBuffer))
		{
			BS_Free(rawBuffer);
			std::cout << "File reading failed" << std::endl;
			return _loadError();
		}

		//Load png as new buffer.
		byte*	newBuffer = ImageLoader::load(&rawBuffer, &file, m_width, m_height);


		//Upload texture to OpenGL

		Texture2D tex = Texture2D::create(m_channels, m_width, m_height, newBuffer, m_isTiled);

		if (tex.id() == 0)
		{
			free(newBuffer);
			BS_Free(rawBuffer);
			std::cout << "Texture generation failed" << std::endl;
			return _loadError();
		}

		m_textureId = tex.id();
		m_width = tex.width();
		m_height = tex.height();
		m_isTiled = tex.isTiled();

		//Clean up
		FileSystem::close(file);
		BS_Free(rawBuffer);
		free(newBuffer);
		m_isLoaded = true;
		return false;
	}

	bool ImageResource::unload()
	{
		::glDeleteTextures(1, &m_textureId);
		return false;
	}

	Texture2D ImageResource::getData()
	{
		return Texture2D(m_width, m_height, m_textureId, m_isLoaded);
	}


	MeshResource::MeshResource()
		:Resource(RESOURCE_TYPE::MESH)
	{

	}

	MeshResource::MeshResource(const MeshResource& t)
		: Resource(t)
	{

	}

	MeshResource::~MeshResource()
	{

	}

	bool MeshResource::load()
	{
		return false;
	}

	bool MeshResource::unload()
	{
		return false;
	}

	AudioResource::AudioResource()
		:Resource(RESOURCE_TYPE::AUDIO)
	{

	}

	AudioResource::AudioResource(const AudioResource& t)
		: Resource(t)
	{

	}

	AudioResource::~AudioResource()
	{

	}

	bool AudioResource::load()
	{
		return false;
	}

	bool AudioResource::unload()
	{
		return false;
	}


	FontResource::FontResource()
		:Resource(RESOURCE_TYPE::FONT)
	{

	}

	FontResource::FontResource(const FontResource& f)
		: Resource(f),
		m_id(f.m_id),
		m_name(f.m_name)
	{

	}

	FontResource::~FontResource()
	{
		
	}

	bool FontResource::load()
	{
		if (m_isLoaded) return false;

		FileInfo file = FileSystem::open(m_fileName);

		if (file.size == 0)
		{
			std::cout << "File size is 0" << std::endl;
			return _loadError();
		}

		//Create buffer
		byte*	rawBuffer = (byte*)BS_Malloc(file.size);
		if (!FileSystem::read(file, rawBuffer))
		{
			BS_Free(rawBuffer);
			std::cout << "File reading failed" << std::endl;
			return _loadError();
		}

		String charset = " !\"#$%&'()*+,-./0123456789:;<=>?ABCDEFGHIJKLMNOPQRSTUVWXTYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{}~";

		Font* f = g_fontManager._createFont(rawBuffer, file.size, charset, 16);

#ifdef BS_ASSERT
		assert(f);
#endif // BS_ASSERT

		m_name = f->name();

		FileSystem::close(file);
		//Clean up
		BS_Free(rawBuffer);
		m_isLoaded = true;

		return false;
	}

	bool FontResource::unload()
	{
		g_fontManager.m_fonts.remove(m_name);
		return true;
	}

	Font*	FontResource::getData()
	{
		if (!m_isLoaded) return nullptr;

		if (g_fontManager.m_fonts.isEmptyAt(m_name)) return nullptr;

		return &g_fontManager.m_fonts[m_name];
	}

}