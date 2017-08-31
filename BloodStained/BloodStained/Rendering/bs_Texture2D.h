#ifndef		_BS_TEXTURE2D_H_
#define		_BS_TEXTURE2D_H_

#include <Utilities/bs_types.h>
#include <Utilities/bs_String.h>
#include "bs_OpenGL.h"



namespace bs
{
	enum class ERROR_ID;
	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(const Texture2D& t);
		~Texture2D();

		inline	ui32 id() const{ return m_id; }
		inline	ui32 width() const { return m_width; }
		inline	ui32 height() const{ return m_height; }

		void	bind(ui32 texIndex) const;
		void	unbind(ui32 texIndex) const; 

	public:
		static ERROR_ID create(Texture2D* tex, byte* data, ui32 width, ui32 height, 
			OPENGL_COLOR_FORMAT colorFormat);

		static void destroy(Texture2D* tex);

		static void setClamped(bool value);
		

	private:
		ui32	m_id;
		ui32	m_width;
		ui32	m_height;
	};
}

#endif