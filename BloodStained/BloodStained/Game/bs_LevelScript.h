#ifndef BS_LEVELSCRIPT_H
#define BS_LEVELSCRIPT_H

#include "../Utilities/bs_types.h"

namespace bs
{
	class Level;

	class LevelScript
	{
	public:
		LevelScript();

		LevelScript(const LevelScript& l);

		virtual ~LevelScript() = 0;

		virtual void execute(Level* l, real dt) = 0;

		virtual void initialize(Level* l) = 0;

		virtual void shutDown();

		virtual void render(Level* l);

	};
}
#endif // !BS_LEVELSCRIPT_H
