#include "world.h"
#include "agk.h"
#include "../berekeningen/check_data.h"
#include "../2d/gui.h"

extern Gui gui;
extern check_data check;

void World::load_all()
{
	/****************************************************************
							Slotmachine
	****************************************************************/
	// Slotmachine texture
	tex_slotmachine = agk::LoadImage("textures/tex_slotmachine.png");

	// Mesh slotmachine_base
	mdl_slotmachine = agk::LoadObject("models/slotmachine.obj");
	agk::SetObjectImage(mdl_slotmachine, tex_slotmachine, 0);
	agk::SetObjectPosition(mdl_slotmachine, 0, 0, 20);
	//agk::SetObjectVisible(mdl_slotmachine, true);
	agk::Create3DPhysicsStaticBody(mdl_slotmachine);

	// Load arm
	arm = agk::LoadObject("models/slotmachine_arm.obj");
	agk::SetObjectImage(arm, tex_slotmachine, 0);
	// Set mesh coordinates
	agk::SetObjectPosition(arm, 0, 0, 20);
	agk::SetObjectVisible(arm, true);
	agk::Create3DPhysicsStaticBody(arm);

	// Slot sides - texture
	tex_slot_faces = agk::LoadImage("textures/slot_sides.png");

	// Load 3d mesh
	slot_1 = agk::LoadObject("models/slot_faces.obj");
	agk::SetObjectImage(slot_1, tex_slot_faces, 0);
	// Set mesh coordinates
	agk::SetObjectPosition(slot_1, -10, 0, 20);
	agk::SetObjectVisible(slot_1, true);
	agk::Create3DPhysicsStaticBody(slot_1);

	// Load 3d mesh
	slot_2 = agk::LoadObject("models/slot_faces.obj");
	agk::SetObjectImage(slot_2, tex_slot_faces, 0);
	// Set mesh coordinates
	agk::SetObjectPosition(slot_2, 0, 0, 20);
	agk::SetObjectVisible(slot_2, true);
	agk::Create3DPhysicsStaticBody(slot_2);

	// Load 3d mesh
	slot_3 = agk::LoadObject("models/slot_faces.obj");
	agk::SetObjectImage(slot_3, tex_slot_faces, 0);
	// Set mesh coordinates
	agk::SetObjectPosition(slot_3, 10, 0, 20);
	agk::SetObjectVisible(slot_3, true);
	agk::Create3DPhysicsStaticBody(slot_3);

	// Draw plane
	floor = agk::CreateObjectPlane(1024, 1024);
	tex_floor = agk::LoadImage("textures/floor_texture.png");
	agk::SetObjectImage(floor, tex_floor, 0);
	agk::SetObjectRotation(floor, 90, 0, 0);
	agk::SetObjectPosition(floor, 0, -10, 256);
	agk::SetObjectVisible(floor, true);

	/****************************************************************
							Hold knoppen
	****************************************************************/
	// Hold knop laad texture en model extern
	mdl_hold = agk::LoadObject("models/hold.obj");
	agk::SetObjectImage(mdl_hold, tex_slotmachine, 0);
	agk::SetObjectVisible(mdl_hold, false);

	// Laad en plaats hold knop 1
	obj_hold1 = agk::CreateObjectFromObjectMesh(mdl_hold, 1);
	agk::SetObjectPosition(obj_hold1, -10, -12, 20);
	agk::SetObjectVisible(obj_hold1, true);
	agk::SetObjectRotation(obj_hold1, 0, 0, 0);

	// Laad en plaats hold knop 2
	obj_hold2 = agk::CreateObjectFromObjectMesh(mdl_hold, 1);
	agk::SetObjectPosition(obj_hold2, 0, -12, 20);
	agk::SetObjectVisible(obj_hold2, true);
	agk::SetObjectRotation(obj_hold2, 0, 0, 0);

	// Laad en plaats hold knop 3
	obj_hold3 = agk::CreateObjectFromObjectMesh(mdl_hold, 1);
	agk::SetObjectPosition(obj_hold3, 10, -12, 20);
	agk::SetObjectVisible(obj_hold3, true);
	agk::SetObjectRotation(obj_hold3, 0, 0, 0);

	/****************************************************************
							Cashen knop
	****************************************************************/
	// Laad en plaats cashen knop
	cashen_knop = agk::LoadObject("models/slotmachine_cashen.obj");
	agk::SetObjectImage(cashen_knop, tex_slotmachine, 0);
	agk::SetObjectVisible(cashen_knop, true);
	agk::SetObjectPosition(cashen_knop, 0, 0, 22);
}

void World::init_vars()
{
	// Slotmachine arm
	arm_up = true;
	arm_rot = 0;

	// Slots
	angle1 = (360 * 3) + 90;
	angle2 = (360 * 3) + 270;
	angle3 = (360 * 3) + 180;

	// Spin slots
	spin1 = false;
	spin2 = false;
	spin3 = false;

	// Slot index
	slot1_index = 1;
	slot2_index = 3;
	slot3_index = 2;
	
	// Slot speed
	s1_speed = 0;
	s2_speed = 0;
	s3_speed = 0;

	// Hold false
	slots_hold = 0;
	hold1_pressed = false;
	hold2_pressed = false;
	hold3_pressed = false;

	// Zet eerste hold_z coordinaten
	hold1_z = 20;
	hold2_z = 20;
	hold3_z = 20;

	// Hold indrukken
	allow_hold = true;
}

void World::update_world() {
	// Rotate arm
	if (arm_up == false) {
		if (arm_rot < 90) {
			arm_rot += 4;
		} else {
			spin_slots();
			arm_up = true;
		}
	} else {
		if (arm_rot > 0) {
			arm_rot -= 4;
		}
	}
	agk::SetObjectRotation(arm, arm_rot*-1, 0, 0);

	// Animeer hold knop
	if (hold1_pressed == true && agk::GetObjectZ(obj_hold1) < 23) {
		hold1_z += 0.5;
		agk::SetObjectPosition(obj_hold1, -10, -12, hold1_z);
	} else if (hold1_pressed == false && agk::GetObjectZ(obj_hold1) > 20) {
		hold1_z -= 0.5;
		agk::SetObjectPosition(obj_hold1, -10, -12, hold1_z);
	}

	if (hold2_pressed == true && agk::GetObjectZ(obj_hold2) < 23) {
		hold2_z += 0.5;
		agk::SetObjectPosition(obj_hold2, 0, -12, hold2_z);
	} else if (hold2_pressed == false && agk::GetObjectZ(obj_hold2) > 20) {
		hold2_z -= 0.5;
		agk::SetObjectPosition(obj_hold2, 0, -12, hold2_z);
	}

	if (hold3_pressed == true && agk::GetObjectZ(obj_hold3) < 23) {
		hold3_z += 0.5;
		agk::SetObjectPosition(obj_hold3, 10, -12, hold3_z);
	} else if (hold3_pressed == false && agk::GetObjectZ(obj_hold3) > 20) {
		hold3_z -= 0.5;
		agk::SetObjectPosition(obj_hold3, 10, -12, hold3_z);
	}
}

void World::pull_lever()
{
	// Check of machine in gebruik is en welke slots op hold staan
	if (spin1 == false && spin2 == false && spin3 == false) {
		if (hold1_pressed == false) {
			angle1 -= (360 * 3);
			slot1_index = 1 + (rand() % (int)(4 - 1 + 1));
			spin1 = true;
		}
		if (hold2_pressed == false) {
			angle2 -= (360 * 3);
			slot2_index = 1 + (rand() % (int)(4 - 1 + 1));
			spin2 = true;
		}
		if (hold3_pressed == false) {
			angle3 -= (360 * 3);
			slot3_index = 1 + (rand() % (int)(4 - 1 + 1));
			spin3 = true;
		}
		arm_up = false;

		// Zet slots rotatie snelheid
		srand(time(NULL));
		s1_speed = 6 + (rand() % (int)(12 - 6 + 1));
		s2_speed = 6 + (rand() % (int)(12 - 6 + 1));
		s3_speed = 6 + (rand() % (int)(12 - 6 + 1));

		allow_hold = true;

		gui.change_credits(-1);
	}
}

bool World::spin_slots() 
{
	// Slot 1 rot
	if (angle1 >= (360 * 3) + (slot1_index * 90)) {
		angle1 = (360 * 3) + (slot1_index * 90);
		spin1 = false;
	} else { angle1 += s1_speed; }

	// Slot 2 rot
	if (angle2 >= (360 * 3) + (slot2_index * 90)) {
		angle2 = (360 * 3) + (slot2_index * 90);
		spin2 = false;
	} else { angle2 += s2_speed; }

	// Slot 3 rot
	if (angle3 >= (360 * 3) + (slot3_index * 90)) {
		angle3 = (360 * 3) + (slot3_index * 90);
		spin3 = false;
	} else { angle3 += s3_speed; }

	// Zet rotatie naar nieuwe hoek
	agk::SetObjectRotation(slot_1, angle1, 0, 0);
	agk::SetObjectRotation(slot_2, angle2, 0, 0);
	agk::SetObjectRotation(slot_3, angle3, 0, 0);
	
	// Check of slots nog draaien anders stoppen
	if (spin1 == false && spin2 == false && spin3 == false) { 
		check.check_won(slot1_index, slot2_index, slot3_index);
		return false; 
	} else { 
		return true;
	}
}

void World::hold_slot(int slot)
{
	if (allow_hold == true) {
		switch (slot) {
		case 1:
			if (hold1_pressed == false) {
				if (slots_hold < 2) {
					hold1_pressed = true;
					slots_hold += 1;
				}
			} else {
				hold1_pressed = false;
				slots_hold -= 1;
			}
			break;

		case 2:
			if (hold2_pressed == false) {
				if (slots_hold < 2) {
					hold2_pressed = true;
					slots_hold += 1;
				}
			} else {
				hold2_pressed = false;
				slots_hold -= 1;
			}
			break;

		case 3:
			if (hold3_pressed == false) {
				if (slots_hold < 2) {
					hold3_pressed = true;
					slots_hold += 1;
				}
			} else {
				hold3_pressed = false;
				slots_hold -= 1;
			}
			break;
		}
	}
}

void World::unhold()
{
	hold1_pressed = false;
	hold2_pressed = false;
	hold3_pressed = false;
	slots_hold = 0;
	allow_hold = false;
}