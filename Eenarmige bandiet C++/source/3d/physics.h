#pragma once
class PhysicsWorld
{
	private:
		int slot_1;
		int slot_2;
		int slot_3;

		int tex_geld;
		int cent50, euro1, euro2;

		int slot1_index, slot2_index, slot3_index;

		bool spin1, spin2, spin3;

		int mdl_slotmachine;

		int tex_slot_faces;
		int tex_slotmachine;

		int angle1, angle2, angle3;

		int floor;
		int tex_dirt;
		int arm;

		int arm_rot;
		bool arm_up;

		int s1_speed, s2_speed, s3_speed;

		int won_coin;

		int mdl_hold, obj_hold1, obj_hold2, obj_hold3;
		bool hold1_pressed, hold2_pressed, hold3_pressed;

		int coin_id;
		int cone;

		int slots_hold;

		double hold1_z, hold2_z, hold3_z;

		int first_coin;

		// Aantal gewonnen euros
		int euros;


		int despawned_coins;

	public:
		void init_vars();
		void physics_update();
		void load_data();
		void add_money(int munt);
		void drop_money();
};

