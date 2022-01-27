#include "mouse_click.h"
#include "agk.h"
#include "../3d/physics.h"

void mouse_click::init()
{
	/****************************************************************
								Slots
	****************************************************************/
	slots_hold = 0; // Aantal op hold

	// Slots rot
	angle1 = 360 * 3;
	angle2 = 360 * 3;
	angle3 = 360 * 3;

	// Image index
	slot1_index = 1;
	slot2_index = 4;
	slot3_index = 3;

	// Draaien de slots rond
	spin1 = true;
	spin2 = true;
	spin3 = true;

	// Draai snelheid
	s1_speed = 90;
	s2_speed = 90;
	s3_speed = 90;


	/****************************_arm_*******************************/
	// Slotmachine arm vars
	arm_up = true;
	arm_rot = 0;


	/****************************_hold_******************************/
	// Hold knoppen ingedrukt
	hold1_pressed = false;
	hold2_pressed = false;
	hold3_pressed = false;

	// Z coordinaten voor hold objecten
	hold1_z = 20;
	hold2_z = 20;
	hold3_z = 20;
}



int mouse_click::raytrace()
{
	// Muis x en y
	int mX = agk::GetPointerX();
	int mY = agk::GetPointerY();

	// Convert muis naar 3D vector
	float X3D = agk::Get3DVectorXFromScreen(mX, mY);
	float Y3D = agk::Get3DVectorYFromScreen(mX, mY);
	float Z3D = agk::Get3DVectorZFromScreen(mX, mY);

	// Ontvang camera coordinaten
	float camX = agk::GetCameraX(1);
	float camY = agk::GetCameraY(1);
	float camZ = agk::GetCameraZ(1);

	// Raytracer startpos
	float rStartX = X3D + camX;
	float rStartY = Y3D + camY;
	float rStartZ = Z3D + camZ;

	// Raytracer eindpos
	float rEndX = 1024 * X3D + camX;
	float rEndY = 1024 * Y3D + camY;
	float rEndZ = 1024 * Z3D + camZ;

	// Raytrace met data
	return( agk::ObjectRayCast(0, rStartX, rStartY, rStartZ, rEndX, rEndY, rEndZ) );
}