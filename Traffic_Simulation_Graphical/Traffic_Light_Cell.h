#pragma once

#include "enum.h"

class Traffic_Light_Cell {
	friend class Traffic_Light_Manager;
	int intersectionid;
	color NS, EW;
	bool NS_green, is_yellow;
	color nrth, est, sth, wst;
public:
	Traffic_Light_Cell();
	void update();
	void set_intersectionid(int id) { intersectionid = id; }
	int return_intersectionid() { return intersectionid; }
	void set_NS_green(bool inp) { NS_green = inp; };
	void set_is_yellow(bool inp) { is_yellow = inp; };
	bool return_is_NS_Green() { return NS_green; };
	bool return_is_yellow_st() { return is_yellow; };
	color return_active(traj inc);
};
