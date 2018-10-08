/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Traffic_Sim.cpp
*   Author: Harsha Gandikota
*   Desc: Defines Traffic_Sim object functions
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"
#define _CRT_SECURE_NO_DEPRECATE // Shut up MS, about strcpy(), etc.
#define _CRT_SECURE_NO_WARNINGS  //   just don't say anything.


Road* get_road_(string rd_nm, vector<Road>* rset) {
	for (int i = 0; i < rset->size(); i++) {
		if (rd_nm == rset->at(i).return_name()) {
			return &(rset->at(i));
		}
	}
	return NULL;
}

Traffic_Sim::~Traffic_Sim() {

}

Traffic_Sim *Traffic_Sim::get_instance() {

	static Traffic_Sim *instance = NULL;
	if (instance == NULL)
	{
		instance = new Traffic_Sim();
	}
	return instance;
}

void Traffic_Sim::set_Data_File(string xml_file) {

	TrafficSimDataParser* dataparse = TrafficSimDataParser::getInstance();
	dataparse->setDataFileName((char*)xml_file.c_str());
	yellow_dur = 5.0;
	green_dur = 45.0;


	char roadName[64];
	double xstrt, ystrt, xend, yend, speedLim;
	int intersectstrt, intersectend, numLanes;

	SimHeight = dataparse->getSimHeight();
	SimWidth = dataparse->getSimWidth();

	cout << "-----------------------------------------------------------" << endl;
	cout << "\t\t\ Extracting Roads" << endl;


	for (int i = 0; i < dataparse->getRoadCount(); i++) {
		dataparse->getRoadData(roadName, &xstrt, &ystrt, &xend, &yend, &intersectstrt, &intersectend, &speedLim, &numLanes);
		map1.push_back_on_road_set(&Road((string)roadName, vertex(xstrt, ystrt), vertex(xend, yend), numLanes, (int)speedLim, intersectstrt, intersectend));
	}

	int id;
	double xpos;
	double ypos;
	char roadN[32];
	char roadE[32];
	char roadS[32];
	char roadW[32];

	cout << "\t\t\ Extracting Intersections" << endl;


	for (int i = 0; i < dataparse->getIntersectionCount(); i++) {
		dataparse->getIntersectionData(&id, &xpos, &ypos, roadN, roadE, roadS, roadW);

		map1.push_back_on_intersection_set(&Intersection(id, get_road_((string)roadN, map1.return_road_setptr()),
			get_road_((string)roadE, map1.return_road_setptr()),
			get_road_((string)roadS, map1.return_road_setptr()),
			get_road_((string)roadW, map1.return_road_setptr()),
			vertex(xpos, ypos)));

		//Incrementing number of Traffic Light Cells in Traffic_Light_Manager
		TLM.add_Traffic_Light(id);
	}



	char type[32];
	int id_;
	double xpos_;
	double ypos_;
	double startDir;
	double acc;

	cout << "\t\t\ Extracting Vehicles" << endl;
	cout << "-----------------------------------------------------------" << endl;

	for (int i = 0; i < dataparse->getVehicleCount(); i++) {
		dataparse->getVehicleData(type, &id_, &xpos_, &ypos_, &startDir, &acc);

		veh_set.push_back(vehicle((string)type, id_, vertex(xpos_, ypos_), startDir, acc));

	}


	//Assigning the pointer of the Traffic Light Manager to the entire intersection set
	for (int i = 0; i < map1.intersection_set.size(); i++) {
		map1.intersection_set[i].assign_trf_lght_man(&TLM);
	}

	for (int i = 0; i < veh_set.size(); i++) {
		if (veh_set[i].return_type() == "18-WHEELER") {

			_18_wheeler_truck_set.push_back(

				//====================================================================================================================================================================
				vefact.create_18_wheeler_truck(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())		//
																																									//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
																																									//====================================================================================================================================================================

			);
		}
		else if (veh_set[i].return_type() == "8-CYLINDER_CAR") {

			_8_cylinder_car_set.push_back(
				//====================================================================================================================================================================
				vefact.create_8_cylinder_car(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())			//
																																									//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
																																									//====================================================================================================================================================================
			);

		}
		else if (veh_set[i].return_type() == "6-CYLINDER_CAR") {

			_6_cylinder_car_set.push_back(

				//====================================================================================================================================================================
				vefact.create_6_cylinder_car(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())			//
																																									//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
																																									//====================================================================================================================================================================

			);
		}
		else if (veh_set[i].return_type() == "4-CYLINDER_CAR") {

			_4_cylinder_car_set.push_back(

				//====================================================================================================================================================================
				vefact.create_4_cylinder_car(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())			//
																																									//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
																																									//====================================================================================================================================================================
			);
		}
		else if (veh_set[i].return_type() == "LARGE_TRUCK") {

			_Panel_truck_set.push_back(
				//====================================================================================================================================================================
				vefact.create_Panel_truck(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())				//
																																									//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
																																									//====================================================================================================================================================================

			);
		}

	}
}

/*
Traffic_Sim::Traffic_Sim(string xml_file) {

	

	TrafficSimDataParser* dataparse = TrafficSimDataParser::getInstance();
	dataparse->setDataFileName((char*)xml_file.c_str());
	yellow_dur = 5.0;
	green_dur = 45.0;

	char roadName[64];
	double xstrt, ystrt, xend, yend, speedLim;
	int intersectstrt, intersectend, numLanes;

	SimHeight = dataparse->getSimHeight();
	SimWidth = dataparse->getSimWidth();

	cout << "-----------------------------------------------------------" << endl;
	cout << "\t\t\ Extracting Roads" << endl;


	for (int i = 0; i < dataparse->getRoadCount(); i++) {
		dataparse->getRoadData(roadName, &xstrt, &ystrt, &xend, &yend, &intersectstrt, &intersectend, &speedLim, &numLanes);
		map1.push_back_on_road_set(&Road((string)roadName, vertex(xstrt, ystrt),vertex(xend, yend), numLanes, (int)speedLim));
	}

	int id; 
	double xpos; 
	double ypos;
	char roadN[32]; 
	char roadE[32];
	char roadS[32];
	char roadW[32];

	cout << "\t\t\ Extracting Intersections" << endl;


	for (int i = 0; i < dataparse->getIntersectionCount(); i++) {
		dataparse->getIntersectionData(&id, &xpos, &ypos, roadN, roadE, roadS, roadW);

		map1.push_back_on_intersection_set(&Intersection(id, get_road_((string)roadN, map1.return_road_setptr()), 
													  get_road_((string)roadE, map1.return_road_setptr()), 
													  get_road_((string)roadS, map1.return_road_setptr()), 
													  get_road_((string)roadW, map1.return_road_setptr()), 
													  vertex(xpos, ypos)));
		
		//Incrementing number of Traffic Light Cells in Traffic_Light_Manager
		TLM.add_Traffic_Light(id);
	}

	char type[32];
	int id_; 
	double xpos_; 
	double ypos_;
	double startDir; 
	double acc;

	cout << "\t\t\ Extracting Vehicles" << endl;
	cout << "-----------------------------------------------------------" << endl;

	for (int i = 0; i < dataparse->getVehicleCount(); i++) {
		dataparse->getVehicleData(type, &id_, &xpos_, &ypos_, &startDir, &acc);

		veh_set.push_back(vehicle((string)type, id_, vertex(xpos_, ypos_), startDir, acc));

	}


	//Assigning the pointer of the Traffic Light Manager to the entire intersection set
	for (int i = 0; i < map1.intersection_set.size(); i++) {
		map1.intersection_set[i].assign_trf_lght_man(&TLM);
	}

	for (int i = 0; i < veh_set.size(); i++) {
		if (veh_set[i].return_type() == "18-WHEELER") {

			_18_wheeler_truck_set.push_back(

//====================================================================================================================================================================
				vefact.create_18_wheeler_truck(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())		//
//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
//====================================================================================================================================================================

			);
		}
		else if (veh_set[i].return_type() == "8-CYLINDER_CAR") {
	
			_8_cylinder_car_set.push_back(
//====================================================================================================================================================================
				vefact.create_8_cylinder_car(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())			//
//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
//====================================================================================================================================================================
			);

		}
		else if (veh_set[i].return_type() == "6-CYLINDER_CAR") {

			_6_cylinder_car_set.push_back(

//====================================================================================================================================================================
				vefact.create_6_cylinder_car(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())			//
//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
//====================================================================================================================================================================

			);
		}
		else if (veh_set[i].return_type() == "4-CYLINDER_CAR") {

			_4_cylinder_car_set.push_back(

//====================================================================================================================================================================
				vefact.create_4_cylinder_car(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())			//
//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
//====================================================================================================================================================================
			);
		}
		else if (veh_set[i].return_type() == "LARGE_TRUCK") {
			
			_Panel_truck_set.push_back(
//====================================================================================================================================================================
				vefact.create_Panel_truck(veh_set[i].return_id(), &map1, veh_set[i].return_strt_pt(), veh_set[i].return_dir(), veh_set[i].return_acc())				//
//				^^^^^^ Vehicle Factory Object 'vehact' builds all vehicle objects																					//
//====================================================================================================================================================================
				
				);
		}

	}

}
*/

void Traffic_Sim::paint_map(CDC *cdc) {

	COLORREF Grey = RGB(128, 128, 128);

	vector<Road> *rds = map1.return_road_setptr();
	vector<Intersection> *intrs = map1.return_intersection_setptr();

	for (int i = 0; i < rds->size(); i++) {
		vertex upper_left = rds->at(i).return_upper_left();
		vertex lower_right = rds->at(i).return_lower_right();

		int length = lower_right.return_x() - upper_left.return_x();
		int width = lower_right.return_y() - upper_left.return_y();

		cdc->FillSolidRect(upper_left.return_x(), upper_left.return_y(), length, width, Grey);
	}

	for (int j = 0; j < intrs->size(); j++) {
		vertex upper_left = intrs->at(j).return_upper_left();
		vertex lower_right = intrs->at(j).return_lower_right();

		int length = lower_right.return_x() - upper_left.return_x();
		int width = lower_right.return_y() - upper_left.return_y();

		cdc->FillSolidRect(upper_left.return_x(), upper_left.return_y(), length, width, Grey);
	}
}

void Traffic_Sim::run_Simulation(int speed) {



	//struct _timeb   tStruct;
	//double          thisTime;
	
	//bool            done = false;  // while loop flag
	//double			wait_time;
	//
	//double          outputTime;
	//double			vehicle_wait_time;
	//double			report_time;
	//double			Simulation_time;
	//double			Sim_interval;

	//struct _timeb
	//{
	//	int   dstflag;   // holds a non-zero value if daylight saving time is in effect
	//	long  millitm;   // time in milliseconds since the last one-second hack
	//	long  time;      // time in seconds since 00:00:00 1/1/1970
	//	long  timezone;  // difference in minutes moving west from UTC
	//	
	//};



	//_ftime(&tStruct);	// Get start time

	//thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);

	wait_time =  green_dur;
	vehicle_wait_time =  1.0;
	report_time =  5.0;
	run_spd = speed;

	//while (!done)
//	{
//		_ftime(&tStruct);
//		thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);
//
//
//		if (thisTime >= wait_time) {
//
////================================================================
//			TLM.update();										//
////			^^^^^^^^^^^^^										//
////			Traffic Light Manager a.k.a(TLM) is updated here	//
////================================================================
//
//			if (TLM.return_add_grn()) {
//				wait_time += green_dur;
//			}
//			else {
//				wait_time += yellow_dur;
//			}
//		}
//
//		if (thisTime >= vehicle_wait_time) {
//				vehicle_wait_time += 1.0;
//				Simulation_time += 1.0;
//		
//				if (speed == 2) {
//
//					for (int i = 0; i < _18_wheeler_truck_set.size();i++) {
//						_18_wheeler_truck_set[i].move_();
//						_18_wheeler_truck_set[i].move_();
//					}
//					for (int i = 0; i < _8_cylinder_car_set.size();i++) {
//						_8_cylinder_car_set[i].move_();
//						_8_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _6_cylinder_car_set.size();i++) {
//						_6_cylinder_car_set[i].move_();
//						_6_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _4_cylinder_car_set.size();i++) {
//						_4_cylinder_car_set[i].move_();
//						_4_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _Panel_truck_set.size();i++) {
//						_Panel_truck_set[i].move_();
//						_Panel_truck_set[i].move_();
//					}
//
//				}
//				else if (speed == 10) {
//					for (int i = 0; i < _18_wheeler_truck_set.size();i++) {
//						_18_wheeler_truck_set[i].move_();
//						_18_wheeler_truck_set[i].move_();
//						_18_wheeler_truck_set[i].move_();
//						_18_wheeler_truck_set[i].move_();
//						_18_wheeler_truck_set[i].move_();
//					}
//					for (int i = 0; i < _8_cylinder_car_set.size();i++) {
//						_8_cylinder_car_set[i].move_();
//						_8_cylinder_car_set[i].move_();
//						_8_cylinder_car_set[i].move_();
//						_8_cylinder_car_set[i].move_();
//						_8_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _6_cylinder_car_set.size();i++) {
//						_6_cylinder_car_set[i].move_();
//						_6_cylinder_car_set[i].move_();
//						_6_cylinder_car_set[i].move_();
//						_6_cylinder_car_set[i].move_();
//						_6_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _4_cylinder_car_set.size();i++) {
//						_4_cylinder_car_set[i].move_();
//						_4_cylinder_car_set[i].move_();
//						_4_cylinder_car_set[i].move_();
//						_4_cylinder_car_set[i].move_();
//						_4_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _Panel_truck_set.size();i++) {
//						_Panel_truck_set[i].move_();
//						_Panel_truck_set[i].move_();
//						_Panel_truck_set[i].move_();
//						_Panel_truck_set[i].move_();
//						_Panel_truck_set[i].move_();
//					}
//
//				}
//				else {
//					for (int i = 0; i < _18_wheeler_truck_set.size();i++) {
//						_18_wheeler_truck_set[i].move_();
//					}
//					for (int i = 0; i < _8_cylinder_car_set.size();i++) {
//						_8_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _6_cylinder_car_set.size();i++) {
//						_6_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _4_cylinder_car_set.size();i++) {
//						_4_cylinder_car_set[i].move_();
//					}
//					for (int i = 0; i < _Panel_truck_set.size();i++) {
//						_Panel_truck_set[i].move_();
//					}
//
//				}
//				
//			
//		}



		//if (thisTime >= report_time) {
		//	
		//	report_time += 5.0;
		//	
		//	for (int i = 0; i < _18_wheeler_truck_set.size();i++) {
		//		cout<<"Simulation Time: "<<Simulation_time<<endl;
		//		cout<<"Type: 18-wheeler truck"<<endl;
		//		_18_wheeler_truck_set[i].report();
		//	}
		//	for (int i = 0; i < _8_cylinder_car_set.size();i++) {
		//		cout<<"Simulation Time: "<<Simulation_time<<endl;
		//		cout<<"Type: 8-cylinder car"<<endl;
		//		_8_cylinder_car_set[i].report();
		//	}
		//	for (int i = 0; i < _6_cylinder_car_set.size();i++) {
		//		cout<<"Simulation Time: "<<Simulation_time<<endl;
		//		cout<<"Type: 6-cylinder car"<<endl;
		//		_6_cylinder_car_set[i].report();
		//	}
		//	for (int i = 0; i < _4_cylinder_car_set.size();i++) {
		//		cout<<"Simulation Time: "<<Simulation_time<<endl;
		//		cout<<"Type: 4-cylinder car"<<endl;
		//		_4_cylinder_car_set[i].report();
		//	}
		//	for (int i = 0; i < _Panel_truck_set.size();i++) {
		//		cout<<"Simulation Time: "<<Simulation_time<<endl;
		//		cout<<"Type: Panel Truck"<<endl;
		//		_Panel_truck_set[i].report();
		//	}
		//}
		// Do other stuff here
	//}
}

void Traffic_Sim::update(double time_) {
	double thisTime = time_;

	{
		/*_ftime(&tStruct);*/
		//thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);


		if (thisTime >= wait_time) {
			TLM.update();										
																

			if (TLM.return_add_grn()) {
				wait_time += green_dur;
			}
			else {
				wait_time += yellow_dur;
			}
		}

		if (thisTime >= vehicle_wait_time) {
			vehicle_wait_time += 1.0;
			//Simulation_time += 1.0;

	/*		if (run_spd == 2) {

				for (int i = 0; i < _18_wheeler_truck_set.size();i++) {
					_18_wheeler_truck_set[i].move_();
					_18_wheeler_truck_set[i].move_();
				}
				for (int i = 0; i < _8_cylinder_car_set.size();i++) {
					_8_cylinder_car_set[i].move_();
					_8_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _6_cylinder_car_set.size();i++) {
					_6_cylinder_car_set[i].move_();
					_6_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _4_cylinder_car_set.size();i++) {
					_4_cylinder_car_set[i].move_();
					_4_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _Panel_truck_set.size();i++) {
					_Panel_truck_set[i].move_();
					_Panel_truck_set[i].move_();
				}

			}
			else if (run_spd == 5) {
				for (int i = 0; i < _18_wheeler_truck_set.size();i++) {
					_18_wheeler_truck_set[i].move_();
					_18_wheeler_truck_set[i].move_();
					_18_wheeler_truck_set[i].move_();
					_18_wheeler_truck_set[i].move_();
					_18_wheeler_truck_set[i].move_();
				}
				for (int i = 0; i < _8_cylinder_car_set.size();i++) {
					_8_cylinder_car_set[i].move_();
					_8_cylinder_car_set[i].move_();
					_8_cylinder_car_set[i].move_();
					_8_cylinder_car_set[i].move_();
					_8_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _6_cylinder_car_set.size();i++) {
					_6_cylinder_car_set[i].move_();
					_6_cylinder_car_set[i].move_();
					_6_cylinder_car_set[i].move_();
					_6_cylinder_car_set[i].move_();
					_6_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _4_cylinder_car_set.size();i++) {
					_4_cylinder_car_set[i].move_();
					_4_cylinder_car_set[i].move_();
					_4_cylinder_car_set[i].move_();
					_4_cylinder_car_set[i].move_();
					_4_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _Panel_truck_set.size();i++) {
					_Panel_truck_set[i].move_();
					_Panel_truck_set[i].move_();
					_Panel_truck_set[i].move_();
					_Panel_truck_set[i].move_();
					_Panel_truck_set[i].move_();
				}

			}*/
			//else 
			{
				for (int i = 0; i < _18_wheeler_truck_set.size();i++) {
					_18_wheeler_truck_set[i].move_();
				}
				for (int i = 0; i < _8_cylinder_car_set.size();i++) {
					_8_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _6_cylinder_car_set.size();i++) {
					_6_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _4_cylinder_car_set.size();i++) {
					_4_cylinder_car_set[i].move_();
				}
				for (int i = 0; i < _Panel_truck_set.size();i++) {
					_Panel_truck_set[i].move_();
				}

			}


		}


		/*
		if (thisTime >= report_time) {

		report_time += 5.0;

		for (int i = 0; i < _18_wheeler_truck_set.size();i++) {
		cout<<"Simulation Time: "<<Simulation_time<<endl;
		cout<<"Type: 18-wheeler truck"<<endl;
		_18_wheeler_truck_set[i].report();
		}
		for (int i = 0; i < _8_cylinder_car_set.size();i++) {
		cout<<"Simulation Time: "<<Simulation_time<<endl;
		cout<<"Type: 8-cylinder car"<<endl;
		_8_cylinder_car_set[i].report();
		}
		for (int i = 0; i < _6_cylinder_car_set.size();i++) {
		cout<<"Simulation Time: "<<Simulation_time<<endl;
		cout<<"Type: 6-cylinder car"<<endl;
		_6_cylinder_car_set[i].report();
		}
		for (int i = 0; i < _4_cylinder_car_set.size();i++) {
		cout<<"Simulation Time: "<<Simulation_time<<endl;
		cout<<"Type: 4-cylinder car"<<endl;
		_4_cylinder_car_set[i].report();
		}
		for (int i = 0; i < _Panel_truck_set.size();i++) {
		cout<<"Simulation Time: "<<Simulation_time<<endl;
		cout<<"Type: Panel Truck"<<endl;
		_Panel_truck_set[i].report();
		}
		}*/
		// Do other stuff here
	}
}