#pragma once

#include "Road.h"
#include "Intersection.h"
#include "road_map.h"

//===================================================================================================================
//STRATEGY Design pattern : class movement
//along with: movement_18_wheeler_truck, movement_8_cylinder_car, movement_6_cylinder_car, movement_4_cylinder_car
class movement {
protected:
	bool turn_decided;
	turn current_trn;
	traj trajectory;
	float VSmps, VSmph, acc_mph, acc_mps, dist_nxt_intr;
	double dir;
	
	road_map *mp;
	Road *current_Rd;
	Intersection *nxt_inters;
public:
	vertex current_pt;
	movement();
	/*explicit*/ movement(road_map *mp_, vertex strt_pt, double startDir, double acc);
	void get_current_Rd(road_map *mp);
	void get_nxt_intrsct(road_map *mp);
	void set_speed(road_map *mp);
	void handle_exception(Intersection *current_intr);
	void initiate_movement();
	vertex turn_left(int num_lanes);
	vertex turn_right(int num_lanes);
	turn decide_turn();
	void report();
	traj return_dir() { return trajectory; }
};
