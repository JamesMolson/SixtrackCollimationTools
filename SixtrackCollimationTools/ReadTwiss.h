#ifndef ReadTwiss_h
#define ReadTwiss_h 1

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

double ReadTwiss(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, 
		std::vector<std::string> *Pa, std::vector<std::string> *Kn, std::vector<std::string> *Nn, 
		std::vector<std::string> *Pan, std::vector<double> *P, std::vector<double> *L, 
		std::vector<double> *A1, std::vector<double> *A2, std::vector<double> *A3, 
		std::vector<double> *A4, std::vector<ApertureClass_t> *ApertureType);

double ReadTwissNoDrifts(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, 
			std::vector<std::string> *Pa, std::vector<std::string> *Kn, std::vector<std::string> *Nn, 
			std::vector<std::string> *Pan, std::vector<double> *P, std::vector<double> *L, 
			std::vector<double> *A1, std::vector<double> *A2, std::vector<double> *A3, 
			std::vector<double> *A4, std::vector<ApertureClass_t> *ApertureType);

double ReadTwissK(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, 
		std::vector<std::string> *Pa, std::vector<std::string> *Kn, std::vector<std::string> *Nn, 
		std::vector<std::string> *Pan, std::vector<double> *P, std::vector<double> *L, 
		std::vector<double> *KL, std::vector<double> *A1, std::vector<double> *A2, 
		std::vector<double> *A3, std::vector<double> *A4, std::vector<ApertureClass_t> *ApertureType);

// Read also the aperture offset.
// Also used to read the x and y offsets due to the crossing scheme!
double ReadTwissDX(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, std::vector<std::string> *Pa, 
		 std::vector<std::string> *Kn, std::vector<std::string> *Nn, std::vector<std::string> *Pan, 
		 std::vector<double> *P, std::vector<double> *L, std::vector<double> *A1, 
		 std::vector<double> *A2, std::vector<double> *A3, std::vector<double> *A4, 
		 std::vector<double> *DX, std::vector<double> *DY, std::vector<ApertureClass_t> *ApertureType);

double ReadTwissDXNoDrifts(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, std::vector<std::string> *Pa, 
			 std::vector<std::string> *Kn, std::vector<std::string> *Nn, std::vector<std::string> *Pan, 
			 std::vector<double> *P, std::vector<double> *L, std::vector<double> *A1, 
			 std::vector<double> *A2, std::vector<double> *A3, std::vector<double> *A4, 
			 std::vector<double> *DX, std::vector<double> *DY, std::vector<ApertureClass_t> *ApertureType);

/*
* Reads the aperture type and converts it to an integer that gives the type of aperture for future operations.
* @parm ApType A string containing the type of Aperture.
* @return An ApertureClass_t that gives the aperture type as defined below
*/
ApertureClass_t GetApertureType(char* ApType);

#endif

