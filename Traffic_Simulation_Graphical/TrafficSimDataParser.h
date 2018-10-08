//===========================================================
// TrafficSimDataParser.h
// Purpose: Interface file for the DataParser utility class.
// Author: Dr. Rick Coleman
//===========================================================
#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <iostream>
#include <fstream>

using namespace std;

class TrafficSimDataParser
{
	private:
		ifstream	*inFile;					// Traffic sim definition file
		int			m_iNumRoads;				// Number of roads in the simulation
		int			m_iNumIntersections;		// Number of intersections in the simulation
		int			m_iNumVehicles;				// Number of vehicles in the simulation
		int			m_iNextRoadIndex;			// Index of next road to read
		int			m_iNextIntersectionIndex;	// Index of next road to read
		int			m_iNextVehicleIndex;		// Index of next road to read
		char        m_sFileName[64];			// Data file
		double		m_dSimWidth;				// Width of the simulation road network in meters
		double		m_dSimHeight;				// Height of the simulation road network in meters
		TrafficSimDataParser();					// Private constructor

	public:
		~TrafficSimDataParser();
		static TrafficSimDataParser *getInstance();
		void setDataFileName(char *fileName);
		int getRoadCount();
		int getIntersectionCount();
		int getVehicleCount();
		double getSimWidth();				// Return the width of the simulation
		double getSimHeight();				// Return the height of the simulation
		bool getRoadData(char *name, double *xStart, double *yStart, double *xEnd, double *yEnd, 
							int *intersStart, int *intersEnd, double *spdLimit, int *numLanes);
		bool getIntersectionData(int *id, double *xpos, double *ypos, 
						char *roadN, char *roadE, char *roadS, char *roadW);
		bool getVehicleData(char *type, int *id, double *xpos, double *ypos, 
						double *startDir, double *acc);
	private:
		bool getNextLine(char *buffer, int n);
};
#endif
