#ifndef		_BS_TEXTURE2D_H_
#define		_BS_TEXTURE2D_H_

#include <Utilities/bs_types.h>

namespace bs
{
	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(const Texture2D& t);
		~Texture2D();

		inline	ui32 id() { return m_id; }

	private:
		ui32	m_id;
	};
}

#endif