#ifndef BS_LEVEL_H
#define BS_LEVEL_H

#include "../Utilities/bs_types.h"
#include "../Utilities/bs_String.h"
#include "bs_LevelScript.h"
#include "../Containers/bs_LinkedArray.h"


namespace bs
{
	class Entity;
	class Camera2D;
	class Camera3D;
	class Level
	{
	public:
		//Constructor.
		Level();
		//Constructor with level name.
		Level(String name);

		//Copy constructor.
		Level(const Level& l);
		//Destructor.
		~Level();
	public:
		//Entity management:
		Entity*	addEntity();
		void	removeEntity(Entity* e);

	public:
		void	initialize();
		void	shutDown();

		void	update(real dt);
		void	render();
		void	setName(String name);
		inline void	setScript(LevelScript* script){ m_levelScript = script; }

		//Accessors:
		inline	const String&			name()		{ return m_name; }
		inline	LinkedArray<Entity>&	entities()	{ return m_entities; }

		Camera2D*						addCamera2D();
		Camera2D*						getCamera2D(ui32 index);
	protected:
		String	m_name;
		LevelScript*	m_levelScript;
		LinkedArray<Entity> m_entities;
		PoolAllocator<Camera2D> m_cameraAllocator;
		Array<Camera2D*>		m_cameras2D;
	};
}
#endif // !BS_LEVEL_H
