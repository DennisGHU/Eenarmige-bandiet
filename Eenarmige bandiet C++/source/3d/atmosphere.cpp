#include "atmosphere.h"
#include "agk.h"

void atmosphere::init()
{
	// Skybox
	agk::SetSkyBoxVisible(1);
	agk::SetAmbientColor(128, 128, 128);

	// Fog
	agk::SetFogMode(1);
	agk::SetFogColor(161, 183, 209);
	agk::SetFogRange(192, 1024);
	agk::SetFogSunColor(255, 230, 179);

	// Zon
	agk::SetSunActive(1);
	agk::SetSunColor(200, 200, 200);
	agk::SetSunDirection(1, -50, 1);

	// Init physics
	agk::Create3DPhysicsWorld();
	agk::Set3DPhysicsGravity(0, -1, 0);
}
