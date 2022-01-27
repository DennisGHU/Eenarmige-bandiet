#include "camera.h"
#include "agk.h"

void camera::init()
{
	// Render distance
	agk::SetCameraRange(1, 0.1, 2000);

	// Init cam vars
	cam_speed = 1.0;
	_xmove = 0;
	_ymove = 9;
	
	// Zet camera rot
	agk::SetCameraRotation(1, _ymove , _xmove , 0);
	
	// Zet camera positie
	agk::MoveCameraLocalZ(1, -20);
	agk::MoveCameraLocalY(1, 5);
	agk::MoveCameraLocalX(1, 5);

}

void camera::update_pos() {

	// verander cam_speed
	if (agk::GetRawKeyState(16)) { cam_speed = 2.0; } // Shift
	else if (agk::GetRawKeyState(17)) { cam_speed = 0.1; } // Control
	else { cam_speed = 1.0; } // Normale snelheid

	// Get mouse pos on screen
	mouse_x = agk::GetPointerX() - (1280 / 2);
	mouse_y = agk::GetPointerY() - (720 / 2);

	// Voeg muispositie toe aan huidige rotatie
	_xmove = _xmove + (mouse_x);
	_ymove = _ymove + (mouse_y);

	// Zet camera rotatie
	agk::SetCameraRotation(1, _ymove / 16.0, _xmove / 16.0, 0);

	// Centreer de muis
	agk::SetRawMousePosition(1280 / 2, 720 / 2);

	// WASD
	if (agk::GetRawKeyState(87)) { agk::MoveCameraLocalZ(1, cam_speed); } // W
	if (agk::GetRawKeyState(83)) { agk::MoveCameraLocalZ(1, -cam_speed); } // S
	if (agk::GetRawKeyState(65)) { agk::MoveCameraLocalX(1, -cam_speed); } // A
	if (agk::GetRawKeyState(68)) { agk::MoveCameraLocalX(1, cam_speed); } // D

}