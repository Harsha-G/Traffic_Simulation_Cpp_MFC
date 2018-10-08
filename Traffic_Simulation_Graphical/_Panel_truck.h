#pragma once
#include "movement_Panel_truck.h"
#include <string>
#include "vertex.h"
#include "movement.h"

class _Panel_truck :public vehicle {
	movement_Panel_truck *move;
public:
	_Panel_truck();
	_Panel_truck(int id_, road_map *mp, vertex strt_pt, double startDir, double acc);
	void move_();
	void report();
	vertex return_current_pt() { return move->current_pt; }
};