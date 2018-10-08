/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: misc.cpp
*   Author: Harsha Gandikota
*   Desc: Defines misceleneous functions
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"

string return_str_color(color col) {
	if (col == red) { return "red"; }
	else if (col == yellow) { return "yellow"; }
	else if (col == green) { return "green"; }
}

string return_str_dir(traj dir) {
	if (dir == north) {
		return "north";
	}
	else if (dir == east) {
		return "east";
	}
	else if (dir == south) {
		return "south";
	}
	else if (dir == west) {
		return "west";
	}
}
