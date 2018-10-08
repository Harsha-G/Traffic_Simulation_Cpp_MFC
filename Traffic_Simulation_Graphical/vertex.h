#pragma once


class vertex {
	friend class static_entity;
	friend class mobile_entity;
private:
	double x, y;
public:
	vertex();
	vertex(double x_, double y_);
	double return_x();
	double return_y();
};

float get_dist(vertex *v1, vertex *v2);
