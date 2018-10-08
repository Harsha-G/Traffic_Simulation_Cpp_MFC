//================================================================
// TrafficSimDataParser.cpp
// Purpose: Implementation file for the DataParser utility class.
// Author: Dr. Rick Coleman
//================================================================
#pragma warning(disable : 4996)

#include "stdafx.h"
#include "TrafficSimDataParser.h"
#include <cctype>

using namespace std;

//------------------------------------------------
// Default private constructor
//------------------------------------------------
TrafficSimDataParser::TrafficSimDataParser()
{
	strcpy(m_sFileName, "");
}

//------------------------------------------------
// Default private constructor
//------------------------------------------------
void TrafficSimDataParser::setDataFileName(char *fileName)
{
	// Initialize everything
	char line[128];
	m_iNumRoads = 0;				// Number of roads in the simulation
	m_iNumIntersections = 0;		// Number of intersections in the simulation
	m_iNumVehicles = 0;				// Number of vehicles in the simulation
	m_iNextRoadIndex = 0;			// Index of next road to read
	m_iNextIntersectionIndex = 0;	// Index of next road to read
	m_iNextVehicleIndex = 0;		// Index of next road to read

	strcpy(this->m_sFileName, fileName); 
	inFile = new ifstream();
	inFile->open(fileName, fstream::in); // Open the data file
	cout << "Opening file: " << fileName << endl;
	if(inFile->is_open())
	{
		// Get the basic information
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<ROAD>") == 0)
			{
				m_iNumRoads++;	// Count all roads
			}
			else if(strcmp(line, "<INTERSECTION>") == 0)
			{
				m_iNumIntersections++;	// Count all intersections
			}
			else if(strcmp(line, "<VEHICLE>") == 0)
			{
				m_iNumVehicles++; // Count all vehicles
			}
			else if(strcmp(line, "<SIM_WIDTH>") == 0)
			{
				getNextLine(line, 127);   // Get the scenario width
				m_dSimWidth = atof(line); // Set the simulation height
			}
			else if(strcmp(line, "<SIM_HEIGHT>") == 0)
			{
				getNextLine(line, 127);   // Get the scenario width
				m_dSimHeight = atof(line); // Set the simulation width
			}
		}
		inFile->close();
	}
	else
	{
		cout << "Failed to open file\n";
		cout << "Program terminated.\n\n";
		exit(0);
	}
}

//------------------------------------------------
// Default destructor
//------------------------------------------------
TrafficSimDataParser::~TrafficSimDataParser()
{
}

//------------------------------------------------
// Get the singleton instance
//------------------------------------------------
TrafficSimDataParser *TrafficSimDataParser::getInstance()
{
	static TrafficSimDataParser *instance = NULL;
	if(instance == NULL)
	{
		instance = new TrafficSimDataParser();
	}
	return instance;
}

//------------------------------------------------
// Get the number of roads
//------------------------------------------------
int TrafficSimDataParser::getRoadCount()
{
	return m_iNumRoads;
}

//------------------------------------------------
// Get the number of intersections
//------------------------------------------------
int TrafficSimDataParser::getIntersectionCount()
{
	return m_iNumIntersections;
}

//------------------------------------------------
// Get the number of vehicles
//------------------------------------------------
int TrafficSimDataParser::getVehicleCount()
{
	return m_iNumVehicles;
}

//-------------------------------------------------
// Get the scenario width
//-------------------------------------------------
double TrafficSimDataParser::getSimWidth()
{
	return m_dSimWidth;
}

//-------------------------------------------------
// Get the scenario height
//-------------------------------------------------
double TrafficSimDataParser::getSimHeight()
{
	return m_dSimHeight;
}

//-------------------------------------------------------------------------
// Get the information on a road
// Args: *name - pointer to a character array to hold name of road
//       *xStart - pointer to double to hold start point X
//       *yStart - pointer to double to hold start point Y
//       *xEnd - pointer to double to hold end point X
//       *yEnd - pointer to double to hold end point Y
//		 *intersStart - pointer to int to hold ID of start intersection
//		 *intersEnd - pointer to int to hold ID of end intersection
//       *spdLimit - pointer to int to hold speed limit
//       *numLanes - pointer to in to hold number of lanes
// Returns: true if data is valid or false if all road data has been read.
//-------------------------------------------------------------------------
bool TrafficSimDataParser::getRoadData(char *name, double *xStart, double *yStart, double *xEnd, double *yEnd, 
							int *intersStart, int *intersEnd, double *spdLimit, int *numLanes)
{
	int rNum = 0;
	char line[128];
	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the current road count
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<ROAD>") == 0) // Got one
			{
				if(rNum == m_iNextRoadIndex)
				{
					// Get data on this one
					while(getNextLine(line, 127))
					{
						// Get the name
						if(strcmp(line, "<ROAD_NAME>") == 0)
						{
							if(getNextLine(line, 127))
							{
								strcpy(name, line); // Set the road name
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<ROAD_XSTART>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*xStart = atof(line); // Set the start X position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<ROAD_YSTART>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*yStart = atof(line); // Set the start Y position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<ROAD_XEND>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*xEnd = atof(line); // Set the end X position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<ROAD_YEND>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*yEnd = atof(line); // Set the end Y position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<ROAD_START_INTERSECTION>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*intersStart = atoi(line); // Set the ID of start intersection
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<ROAD_END_INTERSECTION>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*intersEnd = atoi(line); // Set the ID of end intersection
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<ROAD_SPEED_LIMIT>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*spdLimit = atof(line); // Set the ID of end intersection
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<ROAD_LANES>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*numLanes = atoi(line); // Set the ID of end intersection
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "</ROAD>") == 0)
						{
							m_iNextRoadIndex++; // Increment for next call to this function
							inFile->close();
							delete inFile; // Delete the istream object not the file
							return true; // Got it
						}
					} // end while
				} // end if(sNum == nextSensor)
				else
				{
					rNum++; // Check the next one
				}
			}
		}
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the roads
}

//---------------------------------------------------------------------------------
// Get the information on an intersection
// Args: *id - pointer to an int to hold intersection ID
//       *xpos - pointer to a double to hold X coordinate of mid point 
//       *ypos - pointer to a double to hold Y coordinate of mid point 
//		 *roadN - pointer to char array to hold name of road to north
//		 *roadE - pointer to char array to hold name of road to east
//		 *roadS - pointer to char array to hold name of road to south
//		 *roadW - pointer to char array to hold name of road to west
//     Note: if no road extends in that direction character array is
//      set to empty.
// Returns: true if data is valid or false if all intersection data has been read.
//---------------------------------------------------------------------------------
bool TrafficSimDataParser::getIntersectionData(int *id, double *xpos, double *ypos, 
						char *roadN, char *roadE, char *roadS, char *roadW)
{
	int iNum = 0;
	char line[128];
	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the current intersection count
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<INTERSECTION>") == 0) // Got one
			{
				if(iNum == m_iNextIntersectionIndex)
				{
					// Get data on this one
					while(getNextLine(line, 127))
					{
						// Get the name
						if(strcmp(line, "<INTERSECTION_ID>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*id = atoi(line); // Set the intersection ID
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<INTERSECTION_MIDPTX>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*xpos = atof(line); // Set the midpoint X position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<INTERSECTION_MIDPTY>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*ypos = atof(line); // Set the midpoint Y position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<INTERSECTION_ROAD_NORTH>") == 0)
						{
							if(getNextLine(line, 127))
							{
								if(strcmp(line, "NULL") == 0)  // Set name of road north
									strcpy(roadN, "");
								else
									strcpy(roadN, line);
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<INTERSECTION_ROAD_EAST>") == 0)
						{
							if(getNextLine(line, 127))
							{
								if(strcmp(line, "NULL") == 0)  // Set name of road east
									strcpy(roadE, "");
								else
									strcpy(roadE, line);
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<INTERSECTION_ROAD_SOUTH>") == 0)
						{
							if(getNextLine(line, 127))
							{
								if(strcmp(line, "NULL") == 0)  // Set name of road south
									strcpy(roadS, "");
								else
									strcpy(roadS, line);
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<INTERSECTION_ROAD_WEST>") == 0)
						{
							if(getNextLine(line, 127))
							{
								if(strcmp(line, "NULL") == 0)  // Set name of road west
									strcpy(roadW, "");
								else
									strcpy(roadW, line);
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "</INTERSECTION>") == 0)
						{
							m_iNextIntersectionIndex++; // Increment for next call to this function
							inFile->close();
							delete inFile; // Delete the istream object not the file
							return true; // Got it
						}
					} // end while
				} // end if(sNum == nextSensor)
				else
				{
					iNum++; // Check the next one
				}
			}
		}
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the intersections
}

//-----------------------------------------------------------------------------------
// Get the information on a vehicle
// Args: *type - pointer to a char array to hold vehicle type
//       *id - pointer to an int to hold vehicle ID
//       *xpos - pointer to a double to hold starting X coordinate
//       *ypos - pointer to a double to hold starting Y coordinate
//		 *startDir - pointer to a double to hold start direction (degrees from east)
//		 *acc - pointer to a double to hold the acceleration (meters/sec/sec)
// Returns: true if data is valid or false if all vehicle data has been read.
//-----------------------------------------------------------------------------------
bool TrafficSimDataParser::getVehicleData(char *type, int *id, double *xpos, double *ypos, 
						double *startDir, double *acc)
{
	int vNum = 0;
	char line[128];
	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the current vehicle count
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<VEHICLE>") == 0) // Got one
			{
				if(vNum == m_iNextVehicleIndex)
				{
					// Get data on this one
					while(getNextLine(line, 127))
					{
						// Get the name
						if(strcmp(line, "<VEHICLE_TYPE>") == 0)
						{
							if(getNextLine(line, 127))
							{
								strcpy(type, line); // Set the vehicle type
							}
							else
								return false; // Oops!
						}
						if(strcmp(line, "<VEHICLE_ID>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*id = atoi(line); // Set the vehicle ID
							}
							else
								return false; // Oops!
						}

						else if(strcmp(line, "<VEHICLE_STARTPTX>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*xpos = atof(line); // Set the start X position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<VEHICLE_STARTPTY>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*ypos = atof(line); // Set the start Y position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<VEHICLE_STARTDIR>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*startDir = atof(line); // Set the start direction
								// NOTE: directions are given in degrees measured CCW from due East
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<VEHICLE_ACCELERATION>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*acc = atof(line); // Set the vehicle acceleration
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "</VEHICLE>") == 0)
						{
							m_iNextVehicleIndex++; // Increment for next call to this function
							inFile->close();
							delete inFile; // Delete the istream object not the file
							return true; // Got it
						}
					} // end while
				} // end if(sNum == nextSensor)
				else
				{
					vNum++; // Check the next one
				}
			}
		}
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the vehicles
}

//------------------------------------------------
// Function: getNextLine()
// Purpose: Reads lines from a file and places
//   them in buffer, removing any leading white
//   space.  Skips blank lines. Ignors comment
//   lines starting with <!-- and ending with -->
//   
// Args:  buffer -- char array to read line into.
//        n -- length of buffer.
// Returns: True if a line was successfully read,
//    false if the end of file was encountered.
// Notes: Function provided by instructor.
//------------------------------------------------
bool TrafficSimDataParser::getNextLine(char *buffer, int n)
{
    bool    done = false;
	char    tempBuf[128];
	char	*temp;
    while(!done)
    {
        inFile->getline(tempBuf, n); // Read a line from the file

        if(inFile->good())          // If a line was successfully read check it
        {
           if(strlen(tempBuf) == 0)     // Skip any blank lines
               continue;
		   else if(strncmp(tempBuf, "<!--", 4) == 0) // Skip comment lines
			   continue;
           else done = true;    // Got a valid data line so return with this line
        }
        else
        {
            strcpy(buffer, "");  // Clear the buffer array
            return false;        // Flag end of file
        }
    } // end while
	// Remove white space from end of string
	temp = &tempBuf[strlen(tempBuf)]; // point to closing \0
	temp--; // back up 1 space
	while(isspace(*temp))
	{
		*temp = '\0'; // Make it another NULL terminator
		temp--;  // Back up 1 char
	}
	// Remove white space from front of string
	temp = tempBuf;
	while(isspace(*temp)) temp++; // Skip leading white space
	// Copy remainder of string into the buffer
	strcpy(buffer, temp);
    return true;  // Flag a successful read
}
