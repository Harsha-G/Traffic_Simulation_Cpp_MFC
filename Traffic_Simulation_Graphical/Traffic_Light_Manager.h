#pragma once

#include <vector>
#include "Traffic_Light_Cell.h"

//=========================================================================================
//FLY-WEIGHT class Traffic_Light_Manager				
class Traffic_Light_Manager {
private:
	bool add_grn;
	vector<Traffic_Light_Cell> Traffic_Light_Cell_Set;
public:
	Traffic_Light_Manager();
	Traffic_Light_Manager(vector<Traffic_Light_Cell> Traffic_Light_Cell_Set_);
	void add_Traffic_Light(int intersectionid);
	bool return_add_grn();
	void update();
	color return_active(int intersection_id, traj inc);

};
//=========================================================================================