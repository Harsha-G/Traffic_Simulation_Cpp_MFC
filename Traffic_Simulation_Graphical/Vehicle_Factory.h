#pragma once

#include "vehicle.h"
#include "_18_wheeler_truck.h"
#include "_4_cylinder_car.h"
#include "_6_cylinder_car.h"
#include "_8_cylinder_car.h"
#include "_Panel_truck.h"

//====================================================================================================================
//FACTORY class Vehicle_Factory		
class Vehicle_Factory {
public:
	//Vehicle_Factory();
	static Vehicle_Factory *getIntsance();
	~Vehicle_Factory();
	_18_wheeler_truck create_18_wheeler_truck(int id_, road_map *mp, vertex strt_pt, double startDir, double acc);
	_8_cylinder_car create_8_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc);
	_6_cylinder_car create_6_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc);
	_4_cylinder_car create_4_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc);
	_Panel_truck create_Panel_truck(int id_, road_map *mp, vertex strt_pt, double startDir, double acc);
};
//===================================================================================================================