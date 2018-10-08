#pragma once
#include "stdafx.h"
#include "stdheader.h"

_8_cylinder_car::_8_cylinder_car() {}

_8_cylinder_car::_8_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc) {
	id = id_;
	move = new movement_8_cylinder_car(mp, strt_pt, startDir, acc);
}

void _8_cylinder_car::move_() {
	move->initiate_movement();
	set_current_pt(move->current_pt);
	set_direction(move->return_dir());
}

void _8_cylinder_car::report() {
	move->report();
}