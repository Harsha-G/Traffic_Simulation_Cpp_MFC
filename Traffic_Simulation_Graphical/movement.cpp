/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: movement.cpp
*   Author: Harsha Gandikota
*   Desc: Defines movement object functions
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"

turn roll_dice(int lft, int rght, int strt) {
	int min = 1;
	int max = 10;
	int value = min + (rand() % (int)(max - min + 1));

	int n1 = 0 + lft;
	int n2 = n1 + rght;
	int n3 = n2 + strt;

	if (value > 0 && value <= n1) {
		return LEFT;
	}
	else if (value > n1 && value <= n2) {
		return RIGHT;
	}
	else if (value > n2 && value <= n3) {
		return STRAIGHT;
	}
}

movement::movement() {
	turn_decided = false;
	dist_nxt_intr = 65536.999;
	dir = 0;
	trajectory = (traj)(int)dir;
	acc_mph = 0;
	acc_mps = 0;
	VSmph = 0;
	VSmps = 0;
	current_Rd = NULL;
	nxt_inters = NULL;
}

movement::movement(road_map *mp_, vertex strt_pt, double startDir, double acc) {
	mp = mp_;

	turn_decided = false;
	dist_nxt_intr = 65536.999;
	current_pt = strt_pt;
	dir = startDir;
	trajectory = (traj)(int)dir;
	acc_mph = acc;
	acc_mps = mph_to_mps(acc_mph);
	VSmph = 0;
	VSmps = 0;
	current_Rd = NULL;
	nxt_inters = NULL;
}

void movement::get_current_Rd(road_map *mp) {
	current_Rd = NULL;
	for (int i = 0; i < mp->road_set.size(); i++) {
		if ((mp->road_set)[i].upper_left.return_x() <= current_pt.return_x()
			&& (mp->road_set)[i].upper_left.return_y() <= current_pt.return_y()
			&& (mp->road_set)[i].lower_right.return_x() >= current_pt.return_x()
			&& (mp->road_set)[i].lower_right.return_y() >= current_pt.return_y()) {
			if (mp->road_set[i].NS_state == true && (trajectory == north || trajectory == south)) {
				current_Rd = &(mp->road_set)[i];
			}
			else if (mp->road_set[i].NS_state == false && (trajectory == east || trajectory == west)) {
				current_Rd = &(mp->road_set)[i];
			}



		}
	}
}

void movement::get_nxt_intrsct(road_map *mp) {
	dist_nxt_intr = 65536.999;
	nxt_inters = NULL;
	for (int i = 0; i < mp->intersection_set.size(); i++) {
		bool chck_intr = false;
		if ((trajectory == east) && (mp->intersection_set[i].WEST == current_Rd) && (current_pt.return_x() < mp->intersection_set[i].intersection_mid_pt.return_x())) {
			chck_intr = true;
		}
		else if ((trajectory == north) && (mp->intersection_set[i].SOUTH == current_Rd) && (current_pt.return_y() > mp->intersection_set[i].intersection_mid_pt.return_y())) {
			chck_intr = true;
		}
		else if ((trajectory == west) && (mp->intersection_set[i].EAST == current_Rd) && (current_pt.return_x() > mp->intersection_set[i].intersection_mid_pt.return_x())) {
			chck_intr = true;
		}
		else if ((trajectory == south) && (mp->intersection_set[i].NORTH == current_Rd) && (current_pt.return_y() < mp->intersection_set[i].intersection_mid_pt.return_y())) {
			chck_intr = true;
		}

		if (chck_intr == true) {
			float dist = sqrt(pow(current_pt.return_x() - mp->intersection_set[i].intersection_mid_pt.return_x(), 2) + pow(current_pt.return_y() - mp->intersection_set[i].intersection_mid_pt.return_y(), 2));
			if (dist < dist_nxt_intr) {
				dist_nxt_intr = dist;
				nxt_inters = &(mp->intersection_set[i]);
				
			}
		}

	}
}

void movement::set_speed(road_map *mp) {

	if (nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), trajectory) == red || nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), trajectory) == yellow) {

		if (total_stopping_dist(current_Rd->speed_limit) < dist_nxt_intr) {
			if (VSmps < mph_to_mps(current_Rd->speed_limit)) {
				VSmps += acc_mps;
				VSmph = VSmps / 0.44704;
				if (VSmps > mph_to_mps(current_Rd->speed_limit)) {
					VSmps = mph_to_mps(current_Rd->speed_limit);
					VSmph = VSmps / 0.44704;
				}
			}
		}
		else if (total_stopping_dist(VSmps) > dist_nxt_intr && VSmps != 0) {
			while ((total_stopping_dist(VSmps) > dist_nxt_intr) && (dist_nxt_intr > lane_width) && VSmps > 0) {
				VSmps -= acc_mps;
				VSmph = VSmps / 0.44704;
				if (VSmps < 0) {
					VSmps = 0;
					VSmph = 0;
				}

				float new_tsdvsmps = total_stopping_dist(VSmps);

				if (VSmps == 0) break;
			}
		}
		if (dist_nxt_intr < lane_width) {
			VSmps = 0;
			VSmph = 0;
		}

		else {
			if (VSmps < mph_to_mps(current_Rd->speed_limit)) {
				VSmps += acc_mps;
				VSmph = VSmps / 0.44704;
				if (VSmps > mph_to_mps(current_Rd->speed_limit)) {
					VSmps = mph_to_mps(current_Rd->speed_limit);
					VSmph = VSmps / 0.44704;
				}
			}
		}
	}
	else if (VSmps == 0) {
		VSmps = mph_to_mps(current_Rd->speed_limit);
		VSmph = VSmps / 0.44704;
	}
}

void movement::handle_exception(Intersection *current_intr) {
	if (current_intr == NULL) return;
	float newx = 0, newy = 0;
	if (trajectory == east) {
		if (current_trn == LEFT) {


			if (current_intr->NORTH) { newx = current_pt.return_x() + ((current_intr->NORTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }
			else if (current_intr->SOUTH) { newx = current_pt.return_x() + ((current_intr->SOUTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }

			if (current_intr->EAST) { newy = current_pt.return_y() - (current_intr->EAST->no_of_lanes / 2)  * lane_width; }
			else if (current_intr->WEST) { newy = current_pt.return_y() - (current_intr->WEST->no_of_lanes / 2)  * lane_width; }

			current_pt = vertex(newx, newy);
			trajectory = north;

		}
		else if (current_trn == RIGHT) {

			if (current_intr->NORTH) { newx = current_pt.return_x() - ((current_intr->NORTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }
			else if (current_intr->SOUTH) { newx = current_pt.return_x() - ((current_intr->SOUTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }

			if (current_intr->EAST) { newy = current_pt.return_y() + (current_intr->EAST->no_of_lanes / 2)  * lane_width; }
			else if (current_intr->WEST) { newy = current_pt.return_y() + (current_intr->WEST->no_of_lanes / 2)  * lane_width; }

			//float newx = current_pt.return_x() - ((current_intr->NORTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width;
			//float newy = current_pt.return_y() + (current_intr->EAST->no_of_lanes / 2)  * lane_width;
			current_pt = vertex(newx, newy);
			trajectory = south;

		}
	}
	else if (trajectory == north) {
		if (current_trn == LEFT) {

			if (current_intr->NORTH) { newx = current_pt.return_x() - ((current_intr->NORTH->no_of_lanes / 2)  * lane_width); }
			else if (current_intr->SOUTH) { newx = current_pt.return_x() - ((current_intr->SOUTH->no_of_lanes / 2)  * lane_width); }

			if (current_intr->EAST) { newy = current_pt.return_y() - ((current_intr->EAST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }
			else if (current_intr->WEST) { newy = current_pt.return_y() - ((current_intr->WEST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }

			//float newx = current_pt.return_x() - (current_intr->NORTH->no_of_lanes / 2)  * lane_width;
			//float newy = current_pt.return_y() - ((current_intr->EAST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width ;
			current_pt = vertex(newx, newy);
			trajectory = west;

		}
		else if (current_trn == RIGHT) {

			if (current_intr->NORTH) { newx = current_pt.return_x() + ((current_intr->NORTH->no_of_lanes / 2)  * lane_width); }
			else if (current_intr->SOUTH) { newx = current_pt.return_x() + ((current_intr->SOUTH->no_of_lanes / 2)  * lane_width); }

			if (current_intr->EAST) { newy = current_pt.return_y() + ((current_intr->EAST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }
			else if (current_intr->WEST) { newy = current_pt.return_y() + ((current_intr->WEST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }

			//float newx = current_pt.return_x() + (current_intr->NORTH->no_of_lanes / 2)  * lane_width;
			//float newy = current_pt.return_y() + ((current_intr->EAST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width;
			current_pt = vertex(newx, newy);
			trajectory = east;
		}
	}
	else if (trajectory == south) {
		if (current_trn == LEFT) {

			if (current_intr->NORTH) { newx = current_pt.return_x() - ((current_intr->NORTH->no_of_lanes / 2)  * lane_width); }
			else if (current_intr->SOUTH) { newx = current_pt.return_x() - ((current_intr->SOUTH->no_of_lanes / 2)  * lane_width); }

			if (current_intr->EAST) { newy = current_pt.return_y() - ((current_intr->EAST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }
			else if (current_intr->WEST) { newy = current_pt.return_y() - ((current_intr->WEST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }

			//float newx = current_pt.return_x() - (current_intr->NORTH->no_of_lanes / 2)  * lane_width;
			//float newy = current_pt.return_y() - ((current_intr->EAST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width;
			current_pt = vertex(newx, newy);
			trajectory = east;
		}
		else if (current_trn == RIGHT) {

			if (current_intr->NORTH) { newx = current_pt.return_x() + ((current_intr->NORTH->no_of_lanes / 2)  * lane_width); }
			else if (current_intr->SOUTH) { newx = current_pt.return_x() + ((current_intr->SOUTH->no_of_lanes / 2)  * lane_width); }

			if (current_intr->EAST) { newy = current_pt.return_y() + ((current_intr->EAST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }
			else if (current_intr->WEST) { newy = current_pt.return_y() + ((current_intr->WEST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }

			//float newx = current_pt.return_x() + (current_intr->NORTH->no_of_lanes / 2)  * lane_width;
			//float newy = current_pt.return_y() + ((current_intr->EAST->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width;
			current_pt = vertex(newx, newy);
			trajectory = west;
		}
	}
	else if (trajectory == west) {
		if (current_trn == LEFT) {

			if (current_intr->NORTH) { newx = current_pt.return_x() - ((current_intr->NORTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }
			else if (current_intr->SOUTH) { newx = current_pt.return_x() - ((current_intr->SOUTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }

			if (current_intr->EAST) { newy = current_pt.return_y() + (current_intr->EAST->no_of_lanes / 2)  * lane_width; }
			else if (current_intr->WEST) { newy = current_pt.return_y() + (current_intr->WEST->no_of_lanes / 2)  * lane_width; }

			//float newx = current_pt.return_x() - ((current_intr->NORTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width;
			//float newy = current_pt.return_y() + (current_intr->EAST->no_of_lanes / 2)  * lane_width;
			current_pt = vertex(newx, newy);
			trajectory = south;
		}
		else if (current_trn == RIGHT) {

			if (current_intr->NORTH) { newx = current_pt.return_x() - ((current_intr->NORTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }
			else if (current_intr->SOUTH) { newx = current_pt.return_x() - ((current_intr->SOUTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width; }

			if (current_intr->EAST) { newy = current_pt.return_y() + (current_intr->EAST->no_of_lanes / 2)  * lane_width; }
			else if (current_intr->WEST) { newy = current_pt.return_y() + (current_intr->WEST->no_of_lanes / 2)  * lane_width; }

			//float newx = current_pt.return_x() - ((current_intr->NORTH->no_of_lanes == 2) ? 0.5 : 1.5) * lane_width;
			//float newy = current_pt.return_y() + (current_intr->EAST->no_of_lanes / 2)  * lane_width;
			current_pt = vertex(newx, newy);
			trajectory = north;
		}
	}

	turn_decided = false;
}

vertex movement::turn_left(int num_lanes) {

	float bc = 0;
	float ac = VSmps;
	float bd = (num_lanes == 4) ? (lane_width * 1.5) : (lane_width * .5);
	float cx = 0, cy = 0;

	if (trajectory == east)
	{
		float ad = nxt_inters->intersection_mid_pt.return_x() - current_pt.return_x();
		bc = ac - ad - bd;
		cx = nxt_inters->intersection_mid_pt.return_x() + (bd);
		cy = current_pt.return_y() - (bc);
	}
	else if (trajectory == west)
	{
		float ad = current_pt.return_x() - nxt_inters->intersection_mid_pt.return_x();
		bc = ac - ad - bd;
		cx = nxt_inters->intersection_mid_pt.return_x() - (bd);
		cy = current_pt.return_y() + (bc);
	}
	else if (trajectory == north)
	{
		float ad = current_pt.return_y() - nxt_inters->intersection_mid_pt.return_y();
		bc = ac - ad - bd;
		cx = current_pt.return_x() - (bc);
		cy = nxt_inters->intersection_mid_pt.return_y() - (bd);
	}
	else if (trajectory == south)
	{
		float ad = nxt_inters->intersection_mid_pt.return_y() - current_pt.return_y();
		bc = ac - ad - bd;
		cx = current_pt.return_x() + (bc);
		cy = nxt_inters->intersection_mid_pt.return_y() + (bd);
	}

	return vertex(cx, cy);
}

vertex movement::turn_right(int num_lanes) {

	float bc = 0;
	float ac = VSmps;
	float bd = (num_lanes == 4) ? (lane_width * 1.5) : (lane_width * .5);
	float cx = 0, cy = 0;

	if (trajectory == east)
	{
		float ad = nxt_inters->intersection_mid_pt.return_x() - current_pt.return_x();
		bc = ac - ad + bd;
		cx = nxt_inters->intersection_mid_pt.return_x() - (bd);
		cy = current_pt.return_y() + (bc);
	}
	else if (trajectory == north)
	{
		float ad = current_pt.return_y() - nxt_inters->intersection_mid_pt.return_y();
		bc = ac - ad + bd;
		cx = current_pt.return_x() + (bc);
		cy = nxt_inters->intersection_mid_pt.return_y() + (bd);
	}
	else if (trajectory == south)
	{
		float ad = nxt_inters->intersection_mid_pt.return_y() - current_pt.return_y();
		bc = ac - ad + bd;
		cx = current_pt.return_x() - (bc);
		cy = nxt_inters->intersection_mid_pt.return_y() - (bd);
	}
	else if (trajectory == west)
	{
		float ad = current_pt.return_x() - nxt_inters->intersection_mid_pt.return_x();
		bc = ac - ad + bd;
		cx = nxt_inters->intersection_mid_pt.return_x() - (bd);
		cy = current_pt.return_y() - (bc);
	}

	return vertex(cx, cy);
}

turn movement::decide_turn() {

	turn_opt opt1 = nxt_inters->get_options(trajectory);

	if (opt1 == turn_opt_leftrightstraight) {
		return roll_dice(3, 3, 4);
	}
	else if (opt1 == turn_opt_leftright) {
		return roll_dice(5, 5, 0);
	}
	else if (opt1 == turn_opt_leftstraight) {
		return roll_dice(4, 0, 6);
	}
	else if (opt1 == turn_opt_rightstraight) {
		return roll_dice(0, 4, 6);
	}
	else if (opt1 == turn_opt_left) {
		return LEFT;
	}
	else return RIGHT;
}

void movement::initiate_movement() {

	get_current_Rd(mp);
	if (current_Rd == NULL) {
		if (trajectory == east) {
			current_pt = vertex(current_pt.return_x() + lane_width * 2.0, current_pt.return_y());
		}
		else if (trajectory == north) {
			current_pt = vertex(current_pt.return_x(), current_pt.return_y() - lane_width * 2.0);
		}
		else if (trajectory == west) {
			current_pt = vertex(current_pt.return_x() - lane_width * 2.0, current_pt.return_y());
		}
		else if (trajectory == south) {
			current_pt = vertex(current_pt.return_x(), current_pt.return_y() + lane_width * 2.0);
		}
		get_current_Rd(mp);

	}



	if (current_Rd == NULL) {
		cout << "Road is faulty" << endl;
		return;
	}
	Intersection *current_intr = nxt_inters;

	get_nxt_intrsct(mp);

	if (nxt_inters == NULL) {
		handle_exception(current_intr);
		if (nxt_inters == NULL) {
			return;
		}
	}


	if (turn_decided == false) {
		current_trn = decide_turn();
		turn_decided = true;
	}

	color intr_light;
	if (trajectory == north) {
		intr_light = nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), trajectory);
	}
	else if (trajectory == south) {
		intr_light = nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), trajectory);
	}
	else if (trajectory == east) {
		intr_light = nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), trajectory);
	}
	else if (trajectory == west) {
		intr_light = nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), trajectory);
	}

	set_speed(mp);

	vertex intr_mid(nxt_inters->intersection_mid_pt.return_x(), nxt_inters->intersection_mid_pt.return_y());

	if (trajectory == east) {

		float nx = current_pt.return_x();
		float ny = current_pt.return_y();
		nx += VSmps;

		if (nx > nxt_inters->intersection_mid_pt.return_x()) {
			if (current_trn == LEFT) {
				current_pt = turn_left(nxt_inters->NORTH->no_of_lanes);
				trajectory = north;
			}
			else if (current_trn == RIGHT) {
				current_pt = turn_right(nxt_inters->SOUTH->no_of_lanes);
				trajectory = south;
			}
		}
		turn_decided = false;
		if (trajectory == east) {
			if ((nx) < current_Rd->lower_right.return_x()) {
				current_pt = vertex(nx, ny);
			}
		}

		if (current_pt.return_x() > current_Rd->lower_right.return_x())
		{
			//cout << "Current Position going out of range" << endl;
		}
	}

	else if (trajectory == north)
	{
		float nx = current_pt.return_x();
		float ny = current_pt.return_y();
		ny -= VSmps;


		if (ny < nxt_inters->intersection_mid_pt.return_y()) {
			if (current_trn == LEFT) {
				current_pt = turn_left(nxt_inters->WEST->no_of_lanes);
				trajectory = west;
			}
			if (current_trn == RIGHT) {
				current_pt = turn_right(nxt_inters->EAST->no_of_lanes);
				trajectory = east;
			}
		}
		turn_decided = false;
		if (trajectory == north) {
			if ((ny) > current_Rd->upper_left.return_y())
				current_pt = vertex(nx, ny);
		}

		if (current_pt.return_y() < current_Rd->upper_left.return_y())
		{
			//cout << "Current Position going out of range" << endl;
		}

	}

	else if (trajectory == west) {
		float nx = current_pt.return_x();
		float ny = current_pt.return_y();
		nx -= VSmps;

		if (nx < nxt_inters->intersection_mid_pt.return_x()) {
			if (current_trn == LEFT) {
				current_pt = turn_left(nxt_inters->SOUTH->no_of_lanes);
				trajectory = south;
			}
			if (current_trn == RIGHT) {
				current_pt = turn_right(nxt_inters->NORTH->no_of_lanes);
				trajectory = north;
			}
		}
		turn_decided = false;
		if (trajectory == west) {
			if ((nx) > current_Rd->upper_left.return_x())
				current_pt = vertex(nx, ny);
		}

		if (current_pt.return_x() < current_Rd->upper_left.return_x())
		{
			//cout << "Current Position going out of range" << endl;
		}

	}

	else if (trajectory == south) {
		float nx = current_pt.return_x();
		float ny = current_pt.return_y();
		ny += VSmps;

		if (ny > nxt_inters->intersection_mid_pt.return_y()) {
			if (current_trn == LEFT) {
				current_pt = turn_left(nxt_inters->EAST->no_of_lanes);
				trajectory = east;
			}
			if (current_trn == RIGHT) {
				current_pt = turn_right(nxt_inters->WEST->no_of_lanes);
				trajectory = west;
			}

		}
		turn_decided = false;
		if (trajectory == south) {
			if ((ny) < current_Rd->lower_right.return_y())
				current_pt = vertex(nx, ny);
		}
		if (current_pt.return_y() > current_Rd->lower_right.return_y())
		{
			//cout << "Current Position going out of range" << endl;
		}

	}
}

void movement::report() {
	if (current_Rd == NULL) {
		return;
	}

	cout << "\t\t\tNext Traffic Light Status:" << endl;
	cout << "\t\t\tN: " << return_str_color(nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), north)) << "  "<< "E: "<< return_str_color(nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), east))<<" "<<"S: "<< return_str_color(nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), south))<<" "<<"W: "<< return_str_color(nxt_inters->Trf_lght_man->return_active(nxt_inters->return_id(), west))<< endl;

	//cout << "Vehicle-Type: " << type << endl;
	cout << "\t\t\tLocation: (" << current_pt.return_x() << " ," << current_pt.return_y() << " )" << endl;
	cout << "\t\t\tCurrent Road: " << current_Rd->return_name() << endl;
	cout << "\t\t\tDirection: " << return_str_dir(trajectory) << endl;
	cout << "\t\t\tSpeed: " << VSmph << " mph" << endl;
	cout << "\n";
}