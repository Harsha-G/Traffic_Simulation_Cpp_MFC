#pragma once
#include "movement_18_wheeler_truck.h"
#include <string>
#include "vertex.h"
#include "movement.h"


class _18_wheeler_truck :public vehicle {
	movement_18_wheeler_truck *move;
public:
	_18_wheeler_truck();
	_18_wheeler_truck(int id_, road_map *mp, vertex strt_pt, double startDir, double acc);
	void move_();
	void report();
	vertex return_current_pt() { return move->current_pt; }
};