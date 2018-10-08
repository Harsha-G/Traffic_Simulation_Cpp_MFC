#pragma once

#include "Road.h"
#include "enum.h"
#include "Traffic_Light_Manager.h"

class Intersection {
	friend class vehicle;
	friend class movement;
private:
	int id;
	Road* NORTH;
	Road* EAST;
	Road* SOUTH;
	Road* WEST;
	vertex intersection_mid_pt;
	vertex upper_left;
	vertex lower_right;
	turn_opt turn_option;
	color nrth, est, sth, wst;

public:
	//	Traffic_Light_Cell cntrl;

	Traffic_Light_Manager *Trf_lght_man;

	Intersection();
	Intersection(int id_, Road* nrth, Road* east, Road* south, Road* west, vertex mid_pt);
	bool point_in_Intersection(vertex pt_);
	turn_opt get_options(traj inc);
	void assign_trf_lght_man(Traffic_Light_Manager *Tlm);
	int return_id();

	vertex return_upper_left() { return upper_left; }
	vertex return_lower_right() { return lower_right; }

	void draw_lights(CDC *cdc);
};