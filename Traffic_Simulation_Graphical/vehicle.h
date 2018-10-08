#pragma once

#include <string>
#include "vertex.h"
#include "movement.h"

using namespace std;

class vehicle {
protected:
	string type;
	int id;
	vertex current_pt;

	float acc_mph, acc_mps;

	traj trajectory;
	double dir;
public:
	vehicle();
	vehicle(string type_, int id_, vertex strt_pt, double startDir, double acc);
	string return_type();
	int return_id();
	vertex return_strt_pt();
	double return_dir();
	float return_acc();
	void set_current_pt(vertex curr_pt) { current_pt = curr_pt; };
	void set_direction(traj dir_) { trajectory = dir_; };
	void Draw(CDC *cdc);
	//turn decide_turn();
	//void get_current_Rd(road_map *mp);
	//void get_nxt_intrsct(road_map *mp);
	//void set_speed(road_map *mp);
	//void move(road_map *mp);
	//void handle_exception(Intersection *current_intr);
	//vertex turn_left(int num_lanes);
	//vertex turn_right(int num_lanes);
	void report();
};




