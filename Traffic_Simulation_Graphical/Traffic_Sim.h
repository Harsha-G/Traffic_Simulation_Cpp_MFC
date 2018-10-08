#pragma once

#include "_18_wheeler_truck.h"
#include "_4_cylinder_car.h"
#include "_6_cylinder_car.h"
#include "_8_cylinder_car.h"
#include "_Panel_truck.h"
#include "Traffic_Light_Manager.h"
#include "vehicle.h"
#include "Vehicle_Factory.h"

class Traffic_Sim {
	double SimWidth, SimHeight;

	float yellow_dur;
	float green_dur;
	Traffic_Light_Manager TLM;
	vector<vehicle> veh_set;

	Vehicle_Factory vefact;




	
public:
	road_map map1;	
	double			wait_time;
	int run_spd;
	double          outputTime;
	double			vehicle_wait_time;
	double			report_time;
	double			Sim_interval;

	vector<_18_wheeler_truck> _18_wheeler_truck_set;
	vector<_8_cylinder_car> _8_cylinder_car_set;
	vector<_6_cylinder_car> _6_cylinder_car_set;
	vector<_4_cylinder_car> _4_cylinder_car_set;
	vector<_Panel_truck> _Panel_truck_set;

	~Traffic_Sim();
	static Traffic_Sim *get_instance();
	void set_Data_File(string file);
	//Traffic_Sim(string xml_file);
	void paint_map(CDC *cdc);
	void run_Simulation(int speed);

	void update(double time_);
};