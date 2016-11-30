/**
* Definition of a series of functions to define and plot 
* the aperture of the all LHC sequence.
*
* Alternative: Generate a 'Sequence' object instead of usinf functions??
*/
#ifndef AssignOneMetre_h
#define AssignOneMetre_h 1

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <vector>

#include <iomanip>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <math.h>

#include "Aperture.h"
#include "OneMetre.h"
#include "OneMetreAlign.h"
#include "ReadTwiss.h"

void AssignOneMetre(std::vector<OneMetre> *TheSequence, std::vector<std::string> K, std::vector<double> P, std::vector<double> L, 
			std::vector<double> A1, std::vector<double> A2, std::vector<double> A3, 
			std::vector<double> A4, std::vector<size_t> ApertureType, double AccLength);

void AssignOneMetreAlign(std::vector<OneMetreAlign> *TheSequence, std::vector<std::string> K, std::vector<double> P, std::vector<double> L, 
			std::vector<double> A1, std::vector<double> A2, std::vector<double> A3, 
			std::vector<double> A4, std::vector<double> DxA, std::vector<double> DyA, std::vector<size_t> ApertureType, double AccLength);

// Write on a file the aperture from (s1-1) to (s2+1)
// Give only the points where the aperture is defined
void PlotSomeMetres(std::vector<OneMetre> TheSequence, double s1, double s2, std::string output, double AccLength);
void PlotAll(std::vector<OneMetre> TheSequence, std::string output);

// Intepolate the define aperture to get the information every Ds
void PlotSomeMetres(std::vector<OneMetre> TheSequence, double s1, double s2, double Ds, std::string output, double AccLength);
void PlotAll(std::vector<OneMetre> TheSequence, double Ds, std::string output);

#endif

