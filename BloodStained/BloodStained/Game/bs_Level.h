#ifndef _BS_LEVEL_H_
#define _BS_LEVEL_H_

#include <Utilities/bs_types.h>

namespace bs
{
	class Level
	{
	public:
		Level();
		Level(const Level& l);
		~Level();

		void	initialize();
		void	shutDown();
		void	update();

	private:
		ui32 m_id;
	};
}

#endif // !_BS_LEVEL_H_