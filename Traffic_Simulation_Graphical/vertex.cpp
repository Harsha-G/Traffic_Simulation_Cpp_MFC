/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: vertex.cpp
*   Author: Harsha Gandikota
*   Desc: Defines the vertex class
*   Date: 3/20/2017
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "stdafx.h"
#include "stdheader.h"
vertex::vertex() {};
vertex::vertex(double x_, double y_) { x = x_; y = y_; };

double vertex::return_x() { return x; }
double vertex::return_y() { return y; }


float get_distance(vertex *v1, vertex *v2) {
	return (pow(v2->return_x() - v1->return_x(), 2.0) - pow(v2->return_y() - v1->return_y(), 2.0));
}