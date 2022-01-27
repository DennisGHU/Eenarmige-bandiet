#pragma once
class World
{
	private:
		// Slot model
		int slot_1, slot_2, slot_3;
		
		// Slot index
		int slot1_index, slot2_index, slot3_index;

		// Hoek voor slots
		int angle1, angle2, angle3;

		// Slot rotatie snelheid
		int s1_speed, s2_speed, s3_speed;

		// Geld texture en modellen
		int tex_geld;
		int cent50, euro1, euro2;
		
		// Zijn de slots aan het draaien
		bool spin1, spin2, spin3;

		// Model slotmachine_base
		int mdl_slotmachine;

		// Slotmachine textures
		int tex_slot_faces;
		int tex_slotmachine;

		// Grond
		int floor;
		int tex_floor;
		
		// Slotmachine arm
		int arm; // model
		int arm_up; // rot_switch
		int arm_rot; // rot_zelf

		// Hold model en knoppen
		int mdl_hold, obj_hold1, obj_hold2, obj_hold3;
		// Staat hold aan
		bool hold1_pressed, hold2_pressed, hold3_pressed;
		// Hold z coordinaten
		double hold1_z, hold2_z, hold3_z;

		// Cashen knop
		int cashen_knop;

		// Aantal slots die op hold staan
		int slots_hold;

		// Temp var om coins te spawnen met obj id voor de raytrace
		int coin_id;

		// Hold kan worden ingedrukt
		bool allow_hold;

	public:
		void load_all(); // Laad alles textures en modellen
		void pull_lever(); // Zet rotatie van van de slotmachine arm
		bool spin_slots(); // Spin slots
		void update_world(); // Loop script
		void init_vars(); // Init vars
		void hold_slot(int slot); // Hold slot
		void unhold(); // Unhold alle slots
};

