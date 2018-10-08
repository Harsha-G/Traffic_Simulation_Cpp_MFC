#pragma once
#include <string>
#include "vertex.h"

using namespace std;

class Road {
	friend class vehicle;
	friend class movement;
private:
	string road_name;
	int speed_limit;
	int no_of_lanes;
	bool NS_state;
	vertex road_strt;
	vertex road_end;
	vertex upper_left;
	vertex lower_right;
	double road_width;
	int intersectionstart;
	int intersectionend;

public:
	Road();
	Road(string road_name_, vertex strt_, vertex end_, int lane_no_, int spd_lim, int intersectionstart, int intersectionend);
	string return_name() { return road_name; };
	int return_no_of_lanes() { return no_of_lanes; }
	double return_road_width();
	int return_intersectionstart() {
		return intersectionstart;
	};
	int return_intersectionend() {
		return intersectionend;
	};

	vertex return_road_strt() { return road_strt; }
	vertex return_road_end() { return road_end; }

	vertex return_upper_left() { return upper_left; }
	vertex return_lower_right() { return lower_right; }

	void set_upper_left(vertex upper_left_) { upper_left = upper_left_; }
	void set_lower_right(vertex lower_right_) { lower_right = lower_right_; }
};