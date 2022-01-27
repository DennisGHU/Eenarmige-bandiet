#include "check_data.h"
#include "agk.h"
#include "../2d/gui.h"
#include "../3d/world.h"

extern Gui gui;
extern World world;

void check_data::check_won(int i1, int i2, int i3) 
{
	if (i1 == i2 && i2 == i3) {
		gui.change_credits(100);
		world.unhold();
	}
}