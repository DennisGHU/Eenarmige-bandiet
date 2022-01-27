#include "leeftijdcheck.h"
#include "agk.h"


void Leeftijdcheck::init()
{
	// Texture
	tex = agk::LoadImage("textures/leeftijd_check.png");

	// Mesh leeftijdcheck background
	mdl_bg = agk::LoadObject("models/leeftijdcheck_bg.obj");
	agk::SetObjectImage(mdl_bg, tex, 0);
	agk::SetObjectPosition(mdl_bg, 5, -10, 0);
	agk::SetObjectScale(mdl_bg, 0.8, 0.8, 0.8);
	//agk::SetObjectVisible(mdl_slotmachine, true);
	agk::Create3DPhysicsDynamicBody(mdl_bg);
	agk::SetObject3DPhysicsMass(mdl_bg, 0);

	// Mesh ja knop
	mdl_ja = agk::LoadObject("models/leeftijdcheck_ja.obj");
	agk::SetObjectImage(mdl_ja, tex, 0);
	agk::SetObjectPosition(mdl_ja, 5, -10, 0);
	agk::SetObjectScale(mdl_ja, 0.8, 0.8, 0.8);
	//agk::SetObjectVisible(mdl_slotmachine, true);
	agk::Create3DPhysicsDynamicBody(mdl_ja);
	agk::SetObject3DPhysicsMass(mdl_ja, 0);

	// Mesh nee knop
	mdl_nee = agk::LoadObject("models/leeftijdcheck_nee.obj");
	agk::SetObjectImage(mdl_nee, tex, 0);
	agk::SetObjectPosition(mdl_nee, 5, -10, 0);
	agk::SetObjectScale(mdl_nee, 0.8, 0.8, 0.8);
	//agk::SetObjectVisible(mdl_slotmachine, true);
	agk::Create3DPhysicsDynamicBody(mdl_nee);
	agk::SetObject3DPhysicsMass(mdl_nee, 0);

	// Nog geen knop ingedrukt
	button_pressed = 0;
}

void Leeftijdcheck::button_press(int button) 
{
	switch (button) {
		
		case 1: // Ja
			button_pressed = 1;
			break;
	
		case 2: // Nee
			button_pressed = 2;
			break;

	}
}

bool Leeftijdcheck::loop() 
{
	
	if (button_pressed == 1) { // Ja
		if (agk::GetObjectZ(mdl_ja) <= 2.0) {
			agk::SetObjectPosition(mdl_ja, 5, -10, agk::GetObjectZ(mdl_ja) + 0.05);
			return false;
		} else {
			agk::SetObject3DPhysicsMass(mdl_ja, 1);
			agk::SetObject3DPhysicsMass(mdl_nee, 1);
			agk::SetObject3DPhysicsMass(mdl_bg, 1);
			return true; // Animatie klaar
		}
	} else if (button_pressed == 2) { // Nee
		if (agk::GetObjectZ(mdl_nee) <= 2.0) {
			agk::SetObjectPosition(mdl_nee, 5, -10, agk::GetObjectZ(mdl_nee) + 0.05);
			return false;
		} else {
			exit(0); // Animatie klaar
			return true;
		}
	}

}