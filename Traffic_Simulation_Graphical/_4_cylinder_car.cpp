/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: vehicle_type.cpp
*   Author: Harsha Gandikota
*   Desc: Defines vehicle_type object functions
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"

_4_cylinder_car::_4_cylinder_car() {}

_4_cylinder_car::_4_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc) {
	id = id_;
	move = new movement_4_cylinder_car(mp, strt_pt, startDir, acc);
}

void _4_cylinder_car::move_() {
	move->initiate_movement();
	set_current_pt(move->current_pt);
	set_direction(move->return_dir());
}

void _4_cylinder_car::report() {
	move->report();
}