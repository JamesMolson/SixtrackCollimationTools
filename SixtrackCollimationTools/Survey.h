/*
 * fix creator and distructor!
 *
 *
 *
 *
 *
 *
 *
 *
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
#include <string.h> 
#include <ctype.h>
#include <math.h>

#ifndef Survey_h
#define Survey_h 1

using namespace std;

class Survey {
 private:
  vector<double> S, Xsurvey;
  vector<double> Xcrossing, Ycrossing;
  vector<double> XPcrossing, YPcrossing;
  vector<double> COx, COy;

  public: 
  Survey::Survey();
  Survey::~Survey();
  //
  void Survey::LoadLHC(string in);
  void Survey::LoadLHC_Crossing(string in);
  void Survey::LoadLHC_Crossing_XP(string in);
  double Survey::GetSurvey(double pos);
  double Survey::GetCrossX(double pos);
  double Survey::GetCrossY(double pos);
  double Survey::GetCrossXP(double pos);
  double Survey::GetCrossYP(double pos);
  void Survey::Clear();
  //
  void Survey::LoadCO(string in);
  double Survey::GetCOx(double pos);
  double Survey::GetCOy(double pos);
};

#endif
