/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: map.cpp
*   Author: Harsha Gandikota
*   Desc: defines road_map object
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"

road_map::road_map(){}

void road_map::push_back_on_road_set(Road* new_rd) {
	road_set.push_back(*new_rd);
}

void road_map::push_back_on_intersection_set(Intersection* new_intr) {
	intersection_set.push_back(*new_intr);
}
