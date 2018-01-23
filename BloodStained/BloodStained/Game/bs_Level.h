#ifndef _BS_LEVEL_H_
#define _BS_LEVEL_H_

#include <Utilities/bs_types.h>
#include <Rendering/bs_Camera2D.h>
#include <Rendering/bs_Camera3D.h>
#include <Containers/bs_Array.h>
namespace bs
{
	struct Event;
	class Level
	{
	public:
		Level();
		Level(const Level& l);
		~Level();

		void	initialize();
		void	shutDown();
		void	update(f32 dt);

		void	onCollisionBegin(Event e);

	private:
		ui32 m_id;
		Array<Camera*>m_cameras;
	};
}

#endif // !_BS_LEVEL_H_