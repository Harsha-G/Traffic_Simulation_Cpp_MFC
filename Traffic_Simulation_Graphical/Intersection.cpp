/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Intersection.cpp
*   Author: Harsha Gandikota
*   Desc: Defines the Intersection
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"

Intersection::Intersection(){}

int Intersection::return_id() {
	return id;
}

void Intersection::assign_trf_lght_man(Traffic_Light_Manager *Tlm) {
	Trf_lght_man = Tlm;
}

Intersection::Intersection(int id_, Road* nrth, Road* east, Road* south, Road* west, vertex mid_pt) {
	id = id_;
	intersection_mid_pt = mid_pt;

	NORTH = nrth;
	EAST = east;
	SOUTH = south;
	WEST = west;

	//if (NORTH != NULL && EAST != NULL && SOUTH != NULL && WEST != NULL) {
	//	turn_option = leftrightstraight;
	//}

	float offsetNS, offsetEW;
	if (NORTH != NULL) {
		offsetNS = NORTH->return_no_of_lanes() / 2 * lane_width;
	}
	else if (SOUTH != NULL) {
		offsetNS = SOUTH->return_no_of_lanes() / 2 * lane_width;
	}

	if (EAST != NULL) {
		offsetEW = EAST->return_no_of_lanes() / 2 * lane_width;
	}
	else if (WEST != NULL) {
		offsetEW = WEST->return_no_of_lanes() / 2 * lane_width;
	}

	upper_left = vertex(intersection_mid_pt.return_x() - offsetNS, intersection_mid_pt.return_y() - offsetEW);
	lower_right = vertex(intersection_mid_pt.return_x() + offsetNS, intersection_mid_pt.return_y() + offsetEW);

	if (NORTH == NULL && WEST == NULL && SOUTH != NULL && EAST != NULL)
	{
		EAST->set_upper_left(upper_left);
		SOUTH->set_upper_left(upper_left);
	}

	if (NORTH == NULL && WEST != NULL && SOUTH != NULL && EAST == NULL)
	{
		WEST->set_lower_right(lower_right);
		SOUTH->set_upper_left(upper_left);
	}

	if (NORTH != NULL && WEST != NULL && SOUTH == NULL && EAST == NULL)
	{
		NORTH->set_lower_right(lower_right);
		WEST->set_lower_right(lower_right);
	}

	if (NORTH != NULL && WEST == NULL && SOUTH == NULL && EAST != NULL)
	{
		NORTH->set_lower_right(lower_right);
		EAST->set_upper_left(upper_left);
	}

}

turn_opt Intersection::get_options(traj inc) {
	bool b_left, b_right, b_straight;
	b_left = b_right = b_straight =  false;
	if (inc == east) {
		if (NORTH) b_left = true;
		if (EAST) b_straight = true;
		if (SOUTH) b_right = true;
	}
	else if (inc == north) {
		if (WEST) b_left = true;
		if (EAST) b_right = true;
		if (NORTH) b_straight = true;
	}
	else if (inc == south) {
		if (WEST) b_right = true;
		if (EAST) b_left = true;
		if (SOUTH) b_straight = true;
	}
	else if (inc == west) {
		if (WEST) b_straight = true;
		if (SOUTH) b_left = true;
		if (NORTH) b_right = true;
	}

	if (b_left && b_straight && b_right) {
		return turn_opt_leftrightstraight;
	}
	else if (!b_left && b_straight && b_right) {
		return turn_opt_rightstraight;
	}
	else if (b_left && !b_straight && b_right) {
		return turn_opt_leftright;
	}
	else if (b_left && b_straight && !b_right) {
		return turn_opt_leftstraight;
	}
	else if (!b_left && !b_straight && b_right) {
		return turn_opt_right;
	}
	else if (b_left && !b_straight && !b_right) { 
		return turn_opt_left;
	}
	return turn_opt_left;
}

bool Intersection::point_in_Intersection(vertex pt_) {
	if ((pt_.return_x() >= upper_left.return_x()) && (pt_.return_x() <= lower_right.return_x()) && (pt_.return_y() >= upper_left.return_y()) && pt_.return_y() <= lower_right.return_y()) {
		return true;
	}
	else {
		return false;
	}
}

void Intersection::draw_lights(CDC *cdc) {
	CPen penRed;
	penRed.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));

	CPen penYellow;
	penYellow.CreatePen(PS_SOLID, 3, RGB(255, 255, 0));

	CPen penGreen;
	penGreen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));

	//cdc->SelectObject(&penBlack1);

	//cdc->Ellipse(x - 10, y - 10, x + 10, y + 10);

	color north_ = Trf_lght_man->return_active(id, south);
	color south_ = Trf_lght_man->return_active(id, north);
	color east_ = Trf_lght_man->return_active(id, west);
	color west_ = Trf_lght_man->return_active(id, east);

	int d_frm_mid=10;
	vertex p_nrth(intersection_mid_pt.return_x(), intersection_mid_pt.return_y() + d_frm_mid);
	vertex p_sth(intersection_mid_pt.return_x(), intersection_mid_pt.return_y() - d_frm_mid);

	vertex p_est(intersection_mid_pt.return_x()- d_frm_mid, intersection_mid_pt.return_y() );
	vertex p_wst(intersection_mid_pt.return_x() + d_frm_mid, intersection_mid_pt.return_y());

	int rad_ = 2;
	if (north_ == green) {
		cdc->SelectObject(&penGreen);
		cdc->Ellipse(p_nrth.return_x() - rad_, p_nrth.return_y() - rad_, p_nrth.return_x() + rad_, p_nrth.return_y() + rad_);
		cdc->Ellipse(p_sth.return_x() - rad_, p_sth.return_y() - rad_, p_sth.return_x() + rad_, p_sth.return_y() + rad_);
	}
	else if (north_ == yellow) {
		cdc->SelectObject(&penYellow);
		cdc->Ellipse(p_nrth.return_x() - rad_, p_nrth.return_y() - rad_, p_nrth.return_x() + rad_, p_nrth.return_y() + rad_);
		cdc->Ellipse(p_sth.return_x() - rad_, p_sth.return_y() - rad_, p_sth.return_x() + rad_, p_sth.return_y() + rad_);
	}
	else if (north_ == red) {
		cdc->SelectObject(&penRed);
		cdc->Ellipse(p_nrth.return_x() - rad_, p_nrth.return_y() - rad_, p_nrth.return_x() + rad_, p_nrth.return_y() + rad_);
		cdc->Ellipse(p_sth.return_x() - rad_, p_sth.return_y() - rad_, p_sth.return_x() + rad_, p_sth.return_y() + rad_);
	}

	if (east_ == green) {
		cdc->SelectObject(&penGreen);
		cdc->Ellipse(p_est.return_x() - rad_, p_est.return_y() - rad_, p_est.return_x() + rad_, p_est.return_y() + rad_);
		cdc->Ellipse(p_wst.return_x() - rad_, p_wst.return_y() - rad_, p_wst.return_x() + rad_, p_wst.return_y() + rad_);
	}
	else if (east_ == yellow) {
		cdc->SelectObject(&penYellow);
		cdc->Ellipse(p_est.return_x() - rad_, p_est.return_y() - rad_, p_est.return_x() + rad_, p_est.return_y() + rad_);
		cdc->Ellipse(p_wst.return_x() - rad_, p_wst.return_y() - rad_, p_wst.return_x() + rad_, p_wst.return_y() + rad_);
	}
	else if (east_ == red) {
		cdc->SelectObject(&penRed);
		cdc->Ellipse(p_est.return_x() - rad_, p_est.return_y() - rad_, p_est.return_x() + rad_, p_est.return_y() + rad_);
		cdc->Ellipse(p_wst.return_x() - rad_, p_wst.return_y() - rad_, p_wst.return_x() + rad_, p_wst.return_y() + rad_);
	}

}
