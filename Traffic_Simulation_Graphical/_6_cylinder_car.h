#pragma once

#include "movement_6_cylinder_car.h"
#include <string>
#include "vertex.h"
#include "movement.h"


class _6_cylinder_car :public vehicle {
	movement_6_cylinder_car *move;
public:
	_6_cylinder_car();
	_6_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc);
	void move_();
	void report();
	vertex return_current_pt() { return move->current_pt; }
};