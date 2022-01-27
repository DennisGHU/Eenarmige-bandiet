#pragma once
class Gui
{
	private: 
		// Vars voor de data
		double ingeworpen;
		int credits;

		// Textures
		int tex_inworp;
		int tex_credits;

		// Sprites
		int spr_inworp;
		int spr_credits;

		// Credits animatie
		int credits_ani;
		int prev_credits;

	public:
		void create(); // Init
		void add_money(double waarde); // Voeg geld toe
		bool can_play(); // kijk of er genoeg credits zijn om te spelen
		void change_credits(int amount); // Verander credits waarde
		int get_credits(); // Stuur aantal credits door
		void credits_gewonnen(); // geef aan hoeveel credits er zijn gewonnen
};

