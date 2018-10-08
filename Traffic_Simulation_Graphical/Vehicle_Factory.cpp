#include "stdafx.h"
#include "stdheader.h"
//Vehicle_Factory::Vehicle_Factory() {}

Vehicle_Factory::~Vehicle_Factory(){}

//------------------------------------------------
// Get the singleton instance
//------------------------------------------------
Vehicle_Factory *Vehicle_Factory::getIntsance(){
	static Vehicle_Factory *instance = NULL;
	if(instance == NULL){
		instance = new Vehicle_Factory();
	}
	return instance;
}

_18_wheeler_truck Vehicle_Factory::create_18_wheeler_truck(int id_, road_map *mp, vertex strt_pt, double startDir, double acc) {
	_18_wheeler_truck trk(id_, mp, strt_pt,startDir, acc);
	return trk;
}

_8_cylinder_car Vehicle_Factory::create_8_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc) {
	_8_cylinder_car car(id_, mp, strt_pt, startDir, acc);
	return car;
}

_6_cylinder_car Vehicle_Factory::create_6_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc) {
	_6_cylinder_car car(id_, mp, strt_pt, startDir, acc);
	return car;
}

_4_cylinder_car Vehicle_Factory::create_4_cylinder_car(int id_, road_map *mp, vertex strt_pt, double startDir, double acc) {
	_4_cylinder_car car(id_, mp, strt_pt, startDir, acc);
	return car;
}

_Panel_truck Vehicle_Factory::create_Panel_truck(int id_, road_map *mp, vertex strt_pt, double startDir, double acc){
	_Panel_truck trk(id_, mp, strt_pt, startDir, acc);
	return trk;
}