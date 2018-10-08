
/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Header.h
*   Author: Harsha Gandikota
*   Desc: Has all the class declarations
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once

#include <sys/types.h>     
#include <sys/timeb.h>     
#include <time.h>  
#include <vector>
#include <iostream>
#include <math.h>
#include <string>

#include "TrafficSimDataParser.h"
#include "vertex.h"
#include "Vehicle_Factory.h"
#include "vehicle.h"
#include "Traffic_Sim.h"
#include "Traffic_Light_Manager.h"
#include "Traffic_Light_Cell.h"
#include "road_map.h"
#include "Road.h"
#include "movement.h"
#include "Intersection.h"
#include "enum.h"

#include "_18_wheeler_truck.h"
#include "_4_cylinder_car.h"
#include "_6_cylinder_car.h"
#include "_8_cylinder_car.h"
#include "_Panel_truck.h"

#include "movement_18_wheeler_truck.h"
#include "movement_8_cylinder_car.h"
#include "movement_6_cylinder_car.h"
#include "movement_4_cylinder_car.h"
#include "movement_Panel_truck.h"


using namespace std;


extern float lane_width;


float total_stopping_dist(float val);
float mph_to_mps(float mph) ;


