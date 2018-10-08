/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: road.cpp
*   Author: Harsha Gandikota
*   Desc: Has all the road declarations
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"

Road::Road(){}

Road::Road(string road_name_, vertex strt_, vertex end_, int lane_no_, int spd_lim, int intersectionstart_, int intersectionend_){//, Intersection *str, Intersection *en) {
	road_name = road_name_;
	no_of_lanes = lane_no_;

	road_strt = strt_;
	road_end = end_;

	intersectionstart = intersectionstart_;
	intersectionend = intersectionend_;

	speed_limit = spd_lim;

	double offset_ = (lane_no_/ 2 * lane_width) ;
	road_width = lane_no_ * lane_width;

	if ( road_strt.return_y() == road_end.return_y()) {
		//Road goes from east to west
		NS_state = false;

		upper_left = vertex(road_strt.return_x(), road_strt.return_y() - offset_);
		lower_right = vertex(road_end.return_x(), road_end.return_y() + offset_);
		
	}
	else if ( road_strt.return_x() == road_end.return_x()) {
		//Road goes from North to south
		NS_state = true;

		upper_left = vertex(road_strt.return_x() - offset_, road_strt.return_y() );
		lower_right = vertex(road_end.return_x() + offset_, road_end.return_y());

	}

}

double Road::return_road_width() {
	return road_width;
}