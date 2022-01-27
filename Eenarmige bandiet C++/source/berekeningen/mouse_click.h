#pragma once
class mouse_click
{
	private:
		// Slots image index
		int slot1_index, slot2_index, slot3_index;

		// Draaien de slots
		bool spin1, spin2, spin3;

		// Aantal graden gedraait per slot
		int angle1, angle2, angle3;

		// Slots draai snelheid
		int s1_speed, s2_speed, s3_speed;

		// Arm hoek
		int arm_rot;

		// Moet de arm naar beneden of boven
		bool arm_up;

		int slots_hold; // aantal holds pressed
		bool hold1_pressed, hold2_pressed, hold3_pressed; // is ingedrukt
		double hold1_z, hold2_z, hold3_z; // z coordinaten voor object

	public:
		void init(); // Init 
		int raytrace(); // Raytrace voor object id
};

