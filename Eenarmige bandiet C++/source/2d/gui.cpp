#include "gui.h"
#include "agk.h"
#include "string"

void Gui::create()
{
	// Plaats inworp achtergrond
	tex_inworp = agk::LoadImage("textures/gui_inworp.png");
	agk::CreateSprite(tex_inworp, tex_inworp);
	agk::SetSpritePosition(tex_inworp, 16, 16);

	// Plaats credits achtergrond
	tex_credits = agk::LoadImage("textures/gui_credits.png");
	agk::CreateSprite(tex_credits, tex_credits);
	agk::SetSpritePosition(tex_credits, (agk::GetVirtualWidth()-256)-16, 16);

	// Create string inworp
	agk::CreateText(1, "0");
	agk::SetTextPosition(1, 16 + 128, 80);
	agk::SetTextAlignment(1, 1); // Centreer
	agk::SetTextSize(1, 64);
	agk::SetTextColor(1, 157, 71, 71);

	// Create string credits
	agk::CreateText(2, "0");
	agk::SetTextPosition(2, ((agk::GetVirtualWidth() - 256) - 16) + 128, 80);
	agk::SetTextAlignment(2, 1); // Centreer
	agk::SetTextSize(2, 64);
	agk::SetTextColor(2, 157, 71, 71);


	// Init vars
	credits = 0;
	ingeworpen = 0;
	credits_ani = 0;
}

void Gui::add_money(double waarde)
{
	// Voeg geld toe
	ingeworpen += waarde;

	// Check of genoeg geld is ingeworpen voor 10 credits
	while (ingeworpen >= 1) {
		credits += 10;
		ingeworpen -= 1;

		// Update credit string
		std::string conv = std::to_string(credits);
		agk::SetTextString(2, conv.c_str());
	}

	// Update ingeworpen string
	std::string temp = std::to_string(ingeworpen);
	std::string conv2 = temp.substr(0, temp.length() - 4);;
	agk::SetTextString(1, conv2.c_str());
}

bool Gui::can_play() 
{
	if (credits > 0) {
		return true;
	} else {
		return false;
	}
}

void Gui::change_credits(int amount) 
{
	credits += amount;

	// Update credit string
	std::string conv = std::to_string(credits);
	agk::SetTextString(2, conv.c_str());
}

int Gui::get_credits()
{
	return credits;
}

void Gui::credits_gewonnen()
{
	// Popup
	std::string conv = "€ " + std::to_string((int)std::floor(credits/10)) + " gewonnen";
	MessageBox(NULL, conv.c_str(), "Gewonnen", MB_OK);

	// Zet credits naar 0 en update string
	change_credits(-credits);
}