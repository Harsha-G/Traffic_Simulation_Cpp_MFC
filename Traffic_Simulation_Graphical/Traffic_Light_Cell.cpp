/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Traffic_Light_Cell.cpp
*   Author: Harsha Gandikota
*   Desc: Defines Traffic_Light_Cell objects
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"

Traffic_Light_Cell::Traffic_Light_Cell() {
	
	NS_green = true;
	NS = nrth = sth = green;
	is_yellow = false;
	EW = est = wst = red;
	intersectionid = 0;
}

void Traffic_Light_Cell::update() {
	if (NS_green) {
		if (is_yellow) {
			NS = nrth = sth = yellow;
			EW = est = wst = red;
		}
		else
		{
			NS = nrth = sth = green;
			EW = est = wst = red;
		}
	}
	else {
		if (is_yellow) {
			NS = nrth = sth = red;
			EW = est = wst = yellow;
		}
		else {
			NS = nrth = sth = red;
			EW = est = wst = green;
		}
	}
}

color Traffic_Light_Cell::return_active(traj inc) {
	if (inc ==  north) { return sth; }
	else if (inc == east) { return wst; }
	else if (inc == south) { return nrth; }
	else { return est; }
}
