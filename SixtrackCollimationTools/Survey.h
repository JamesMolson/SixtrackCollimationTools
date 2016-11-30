#ifndef Survey_h
#define Survey_h 1
/*
* fix creator and distructor!
*/

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include <iomanip>
//#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <ctype.h>
#include <math.h>

class Survey
{
private:

	std::vector<double> S, Xsurvey;
	std::vector<double> Xcrossing, Ycrossing;
	std::vector<double> XPcrossing, YPcrossing;
	std::vector<double> COx, COy;

public:

	Survey();
	~Survey();

	void LoadAccelerator(std::string in);
	void LoadAccelerator_Crossing(std::string in);
	void LoadAccelerator_Crossing_XP(std::string in);
	double GetSurvey(double pos);
	double GetCrossX(double pos);
	double GetCrossY(double pos);
	double GetCrossXP(double pos);
	double GetCrossYP(double pos);
	void Clear();

	void LoadCO(std::string in);
	double GetCOx(double pos);
	double GetCOy(double pos);
};

#endif

