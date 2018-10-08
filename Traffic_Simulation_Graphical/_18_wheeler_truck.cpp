#pragma once
#include "stdafx.h"
#include "stdheader.h"

_18_wheeler_truck::_18_wheeler_truck() {}

_18_wheeler_truck::_18_wheeler_truck(int id_, road_map *mp, vertex strt_pt, double startDir, double acc) {
	id = id_;
	move = new movement_18_wheeler_truck(mp, strt_pt, startDir, acc);
}

void _18_wheeler_truck::move_() {
	move->initiate_movement();
	set_current_pt(move->current_pt);
	set_direction(move->return_dir());
}

void _18_wheeler_truck::report() {
	move->report();
}