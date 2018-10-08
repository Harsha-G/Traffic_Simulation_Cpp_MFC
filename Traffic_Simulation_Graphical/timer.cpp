#include "stdafx.h"
//#include "Header.h"
//
//timer::timer(int reset_time_) {
//	reset_time = reset_time_;
//}
//
//void timer::start() {
//
//	struct _timeb   tStruct;
//	double          thisTime;
//	double          outputTime;
//	bool            done = false;  // while loop flag
//
//	struct _timeb
//	{
//		int   dstflag;   // holds a non-zero value if daylight saving time is in effect
//		long  millitm;   // time in milliseconds since the last one-second hack
//		long  time;      // time in seconds since 00:00:00 1/1/1970
//		long  timezone;  // difference in minutes moving west from UTC
//	};
//
//	_ftime(&tStruct);	// Get start time
//	thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);
//	outputTime = thisTime + reset_time;
//
//	while (!done)
//	{
//		_ftime(&tStruct);
//		thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);
//
//		if (thisTime >= outputTime)
//		{
//			return ;
//		}
//	}
//}