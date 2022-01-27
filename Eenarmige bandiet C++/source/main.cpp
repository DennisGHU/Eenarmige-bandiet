// Includes
#include "string"
#include "main.h"

#include "3d/camera.h"
#include "3d/atmosphere.h"
#include "3d/world.h"
#include "3d/physics.h"
#include "3d/leeftijdcheck.h"

#include "berekeningen/mouse_click.h"
#include "berekeningen/check_data.h"

#include "2d/gui.h"

// Namespace
using namespace AGK;

app App;

// Instances
atmosphere atmos;
camera cam;
World world;
PhysicsWorld physics;
mouse_click mouse_c;
Gui gui;
check_data check;
Leeftijdcheck lt_check;

bool spin_slots = true;
bool debug_camera = false;
int leeftijdcheck_status = 1; // 1=niet voldaan 2=animatie bezig 3=compleet

void app::Begin(void)
{
	// Setup app
	agk::SetWindowTitle("Eenarmige bandiet C++ Dennis Smid");
	agk::SetVirtualResolution(1280, 720);
	agk::SetClearColor(151, 170, 204); // light blue
	agk::SetSyncRate(60, 0);
	agk::SetScissor(0, 0, 0, 0);
	agk::SetWindowAllowResize(true);

	// Zet AA uit
	agk::SetDefaultMagFilter(0);
	agk::SetDefaultMinFilter(0);

	// Create 3d physics world
	agk::Create3DPhysicsWorld();

	// Leeftijdcheck
	lt_check.init();

	// Init instances
	/*world.load_all(); // Load models en textures
	world.init_vars(); // Init vars*/
	atmos.init(); // Init atmos
	cam.init(); // Init camera
	mouse_c.init(); // Init mouse_click vars
	/*physics.init_vars(); // Init world physics
	physics.load_data(); // Laad objects
	gui.create(); // Init gui*/

	// Setup debug string
	/*agk::CreateText(3, "Geen data");
	agk::SetTextPosition(3, 512, 16);
	agk::SetTextSize(3, 48);*/
	
}

int app::Loop (void)
{
	if (leeftijdcheck_status == 3) {
		// Update world physics
		physics.physics_update();

		// Update world
		world.update_world();

		// Spin slots
		if (spin_slots == true) {
			spin_slots = world.spin_slots();
		}
	} else {
		// Loop animatie
		bool ani_done = lt_check.loop();
		if (ani_done == true) {
			world.load_all(); // Load models en textures
			world.init_vars(); // Init vars
			leeftijdcheck_status = 3; // Animatie klaar
			physics.init_vars(); // Init world physics
			physics.load_data(); // Laad objects
			gui.create(); // Init gui
		}
	}

	// Activeer debug camera
	if (agk::GetRawKeyReleased(69)) { // E toets
		if (debug_camera == false) {
			debug_camera = true;
		} else {
			debug_camera = false;
		}
	}

	// Beweeg camera als rechtermuisknop word ingehouden en debugger aanstaat
	if (agk::GetRawMouseRightState() == 1 && debug_camera == true) {
		cam.update_pos();
	}

	// Raytrace als linkermuisknop word ingedrukt
	if (agk::GetRawMouseLeftReleased()) {

		// Debugger raytrace info
		/*std::string conv = std::to_string(mouse_c.raytrace());
		agk::SetTextString(3, conv.c_str());*/

		switch (mouse_c.raytrace()) {
			case 100014: // cashen
				if (gui.get_credits() >= 100) {
					physics.drop_money();
				}
				break;

			case 100002: // Leeftijdcheck - ja
				if (leeftijdcheck_status == 1) { // niet voldaan
					leeftijdcheck_status = 2; // Animatie bezig
					lt_check.button_press(1);
				}
				break;

			case 100003: // Leeftijdcheck - nee
				if (leeftijdcheck_status == 1) { // niet voldaan
					leeftijdcheck_status = 2; // Animatie bezig
					lt_check.button_press(2);
				}
				break;

			case 100005: // Slotmachine arm
				if (gui.can_play() == true) { // Checkt of je genoeg credits hebt
					world.pull_lever();
					spin_slots = true;
				}
				break;

			case 100015: // cent50
				physics.add_money(1);
				break;
			case 100016: // euro1
				physics.add_money(2);
				break;
			case 100017: // euro2
				physics.add_money(3);
				break;

			case 100011: // Hold slot 1
				world.hold_slot(1);
				break;
			case 100012: // Hold slot 2
				world.hold_slot(2);
				break;
			case 100013: // Hold slot 3
				world.hold_slot(3);
				break;
			}
	}

	// Close app on esc
	if (agk::GetRawKeyReleased(27)) {
		return 1;
	}

	agk::Sync(); // Push frame
	return 0;
}


void app::End (void)
{

}
