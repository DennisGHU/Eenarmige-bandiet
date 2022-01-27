#pragma once
class Leeftijdcheck
{
	private:
		// Model en texture
		int mdl_bg, mdl_ja, mdl_nee, tex;

		// Vars
		int button_pressed;

	public:
		void init(); // Init
		void button_press(int button); // Knop animatie
		bool loop(); // Loop animaties
};

