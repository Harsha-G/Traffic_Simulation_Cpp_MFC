#pragma once

#include "Road.h"
#include "Intersection.h"
#include "road_map.h"
#include "movement.h"

class movement_18_wheeler_truck : public movement {
public:
	movement_18_wheeler_truck(road_map *mp_, vertex strt_pt, double startDir, double acc):movement( mp_,  strt_pt,  startDir,  acc){}
	using movement::movement;
};