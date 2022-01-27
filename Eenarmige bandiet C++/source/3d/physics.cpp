#include "physics.h"
#include "agk.h"
#include "../3d/world.h"
#include "../berekeningen/check_data.h"

#include "../2d/gui.h"

// Gebruik object hier opnieuw
extern World world;
extern Gui gui;

void PhysicsWorld::load_data() 
{
	/****************************************************************
							Inwerp geld
	****************************************************************/
	// Geld texture
	tex_geld = agk::LoadImage("textures/geld_tex.png");

	// 50cent
	cent50 = agk::LoadObject("models/50cent.obj");
	agk::SetObjectImage(cent50, tex_geld, 0);
	agk::SetObjectPosition(cent50, -3, 3, -10);
	//agk::SetObjectVisible(cent50, true);
	agk::SetObjectRotation(cent50, -60, 0, 0);

	// 1euro
	euro1 = agk::LoadObject("models/1euro.obj");
	agk::SetObjectImage(euro1, tex_geld, 0);
	agk::SetObjectPosition(euro1, 2, 3, -10);
	//agk::SetObjectVisible(euro1, true);
	agk::SetObjectRotation(euro1, -60, 0, 0);

	// 2euro
	euro2 = agk::LoadObject("models/2euro.obj");
	agk::SetObjectImage(euro2, tex_geld, 0);
	agk::SetObjectPosition(euro2, 7, 3, -10);
	//agk::SetObjectVisible(euro2, true);
	agk::SetObjectRotation(euro2, -60, 0, 0);
	

	/****************************************************************
							Gewonnen munten
	****************************************************************/
	// Laad en plaats 30 munten boven de machine
	for (int i = first_coin; i <= first_coin + 29; i++) {
		coin_id += 1;
		coin_id = agk::CreateObjectFromObjectMesh(euro1, 1);
		agk::SetObjectVisible(coin_id, true);
		agk::SetObjectPosition(coin_id, -10 + ((i % 3) * 10), 50 + ((i - first_coin) * 3.5), 30);
		agk::Create3DPhysicsDynamicBody(coin_id);
		agk::SetObjectShapeSphere(coin_id, 3.5);
		agk::SetObject3DPhysicsMass(coin_id, 0);
	}
}

void PhysicsWorld::init_vars()
{
	// Slotmachine arm is up
	arm_up = true;

	slots_hold = 0;

	hold1_z = 20;
	hold2_z = 20;
	hold3_z = 20;

	// slots angles
	angle1 = 360 * 3;
	angle2 = 360 * 3;
	angle3 = 360 * 3;

	// init vars
	arm_up = true;
	arm_rot = 0;

	slot1_index = 1;
	slot2_index = 4;
	slot3_index = 3;

	spin1 = true;
	spin2 = true;
	spin3 = true;

	s1_speed = 90;
	s2_speed = 90;
	s3_speed = 90;

	// Aantal coins onder de map gedespawned
	despawned_coins = 0;

	// First coin_id
	first_coin = 100018;
}

void PhysicsWorld::physics_update()
{
	// Herplaats munten als de y as te laag is
	if (agk::GetObjectY(cent50) <= -10) {
		agk::SetObject3DPhysicsMass(cent50, 0);
		agk::SetObjectPosition(cent50, -3, 3, -10);
		agk::SetObjectRotation(cent50, -60, 0, 0);
	}
	if (agk::GetObjectY(euro1) <= -10) {
		agk::SetObject3DPhysicsMass(euro1, 0);
		agk::SetObjectPosition(euro1, 2, 3, -10);
		agk::SetObjectRotation(euro1, -60, 0, 0);
	}
	if (agk::GetObjectY(euro2) <= -10) {
		agk::SetObject3DPhysicsMass(euro2, 0);
		agk::SetObjectPosition(euro2, 7, 3, -10);
		agk::SetObjectRotation(euro2, -60, 0, 0);
	}

	// Despawn munten als deze te ver onder de y as komen
	for (int i = first_coin; i <= first_coin + 29; i++) {
		if (agk::GetObjectWorldY(i) <= -25) {
			agk::Delete3DPhysicsBody(i);
			agk::DeleteObject(i);
			despawned_coins += 1;
		}
	}

	// Als alle munten gedespawned zijn respawn deze dan
	if (despawned_coins == 30) {
		despawned_coins = 0;
		for (int i = first_coin; i <= first_coin + 29; i++) {
			coin_id += 1;
			coin_id = agk::CreateObjectFromObjectMesh(euro1, 1);
			agk::SetObjectVisible(coin_id, true);
			agk::SetObjectPosition(coin_id, -10 + ((i % 3) * 10), 50 + ((i - first_coin) * 3.5), 30);
			agk::Create3DPhysicsDynamicBody(coin_id);
			agk::SetObjectShapeSphere(coin_id, 3.5);
			agk::SetObject3DPhysicsMass(coin_id, 0);
		}
		first_coin += 30;
	}

	// Update physics
	agk::Step3DPhysicsWorld();
}

void PhysicsWorld::add_money(int munt)
{
	switch (munt) {

	case 1: // cent50
		gui.add_money(0.50);
		agk::Create3DPhysicsDynamicBody(cent50);
		agk::SetObjectShapeCylinder(cent50, 1, 3.5, 3);
		agk::SetObject3DPhysicsRollingFriction(cent50, 1);
		agk::SetObject3DPhysicsRestitution(cent50, 1);
		agk::SetObject3DPhysicsLinearVelocity(cent50, 0, 1, 2, 80);
		agk::SetObject3DPhysicsMass(cent50, 5);
		break;

	case 2: // euro1
		gui.add_money(1);
		agk::Create3DPhysicsDynamicBody(euro1);
		agk::SetObjectShapeCylinder(euro1, 1, 3.5, 3);
		agk::SetObject3DPhysicsRollingFriction(euro1, 1);
		agk::SetObject3DPhysicsRestitution(euro1, 1);
		agk::SetObject3DPhysicsLinearVelocity(euro1, 0, 1, 2, 80);
		agk::SetObject3DPhysicsMass(euro1, 5);
		break;

	case 3: // euro1
		gui.add_money(2);
		agk::Create3DPhysicsDynamicBody(euro2);
		agk::SetObjectShapeCylinder(euro2, 1, 3.5, 3);
		agk::SetObject3DPhysicsRollingFriction(euro2, 1);
		agk::SetObject3DPhysicsRestitution(euro2, 1);
		agk::SetObject3DPhysicsLinearVelocity(euro2, 0, 1, 2, 90);
		agk::SetObject3DPhysicsMass(euro2, 6);
		break;

	}
}

void PhysicsWorld::drop_money() 
{
	if (gui.get_credits() >= 10) {

		// Maak munten zwaarder en maak ze wakker
		for (int i = first_coin; i <= first_coin + 29; i++) {
			agk::SetObject3DPhysicsMass(i, 10);
			agk::SetObject3DPhysicsCanSleep(i, 0);
		}

		gui.credits_gewonnen();
	}
}