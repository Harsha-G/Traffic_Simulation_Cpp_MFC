#include "stdafx.h"
#include "stdheader.h"

Traffic_Light_Manager::Traffic_Light_Manager() { add_grn = false; }

Traffic_Light_Manager::Traffic_Light_Manager(vector<Traffic_Light_Cell> Traffic_Light_Cell_Set_) {
	add_grn = false;
	Traffic_Light_Cell_Set = Traffic_Light_Cell_Set_;
}

bool Traffic_Light_Manager::return_add_grn() {
	return add_grn;
}

void Traffic_Light_Manager::add_Traffic_Light(int intersectionid) {
	Traffic_Light_Cell tr_lt;
	tr_lt.set_intersectionid(intersectionid);
	Traffic_Light_Cell_Set.push_back(tr_lt);
}

void Traffic_Light_Manager::update() {
	for (int i = 0; i < Traffic_Light_Cell_Set.size(); i++) {
	
		if (Traffic_Light_Cell_Set[i].return_is_yellow_st()) {
			add_grn = true;

			Traffic_Light_Cell_Set[i].set_is_yellow(false);

			if (Traffic_Light_Cell_Set[i].return_is_NS_Green()) {
				Traffic_Light_Cell_Set[i].set_NS_green(false);
			}

			else {
				Traffic_Light_Cell_Set[i].set_NS_green(true);
			}
		}

		else {

			add_grn = false;
			Traffic_Light_Cell_Set[i].set_is_yellow(true);
		}
		Traffic_Light_Cell_Set[i].update();
	}
}

color Traffic_Light_Manager::return_active(int intersection_id, traj inc) {
	for (int i = 0; i < Traffic_Light_Cell_Set.size(); i++) {
		if (intersection_id == Traffic_Light_Cell_Set[i].return_intersectionid()) {
			return Traffic_Light_Cell_Set[i].return_active(inc);
		}
	}
}
