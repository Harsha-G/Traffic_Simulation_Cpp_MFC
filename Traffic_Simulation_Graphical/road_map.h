#pragma once

#include "Intersection.h"
#include <vector>

class road_map {
	friend class vehicle;
	friend class movement;
	friend class Traffic_Sim;
	vector<Road> road_set;
	vector<Intersection> intersection_set;
public:
	road_map();
	void push_back_on_road_set(Road* new_rd);
	void push_back_on_intersection_set(Intersection* new_intr);
	vector<Road>* return_road_setptr() { return &road_set; }
	vector<Intersection>* return_intersection_setptr() { return &intersection_set; }

};