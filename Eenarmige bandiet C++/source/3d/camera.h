#pragma once
class camera
{
	private:
		double cam_speed;     // Setting
		int mouse_x, mouse_y; // Muis x y
		float _xmove, _ymove; // Cam rot

	public:
		void init();          // Init cam
		void update_pos();    // Update cam

};

