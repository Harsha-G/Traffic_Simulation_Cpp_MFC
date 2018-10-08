#pragma once

#include "Road.h"
#include "Intersection.h"
#include "road_map.h"
#include "movement.h"

class movement_8_cylinder_car : public movement {
public:
	movement_8_cylinder_car(road_map *mp_, vertex strt_pt, double startDir, double acc):movement( mp_,  strt_pt,  startDir,  acc){}
	using movement::movement;
};