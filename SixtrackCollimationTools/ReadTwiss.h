
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include <iomanip>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include <math.h>

#include "Aperture.h"

#ifndef ReadTwiss_h
#define ReadTwiss_h 1

using namespace std;

double ReadTwiss(string in, vector<string> *K, vector<string> *N, 
		vector<string> *Pa, vector<string> *Kn, vector<string> *Nn, 
		vector<string> *Pan, vector<double> *P, vector<double> *L, 
		vector<double> *A1, vector<double> *A2, vector<double> *A3, 
		vector<double> *A4, vector<ApertureClass_t> *ApertureType);

double ReadTwissNoDrifts(string in, vector<string> *K, vector<string> *N, 
			vector<string> *Pa, vector<string> *Kn, vector<string> *Nn, 
			vector<string> *Pan, vector<double> *P, vector<double> *L, 
			vector<double> *A1, vector<double> *A2, vector<double> *A3, 
			vector<double> *A4, vector<ApertureClass_t> *ApertureType);

double ReadTwissK(string in, vector<string> *K, vector<string> *N, 
		vector<string> *Pa, vector<string> *Kn, vector<string> *Nn, 
		vector<string> *Pan, vector<double> *P, vector<double> *L, 
		vector<double> *KL, vector<double> *A1, vector<double> *A2, 
		vector<double> *A3, vector<double> *A4, vector<ApertureClass_t> *ApertureType);

// Read also the aperture offset.
// Also used to read the x and y offsets due to the crossing scheme!
double ReadTwissDX(string in, vector<string> *K, vector<string> *N, vector<string> *Pa, 
		 vector<string> *Kn, vector<string> *Nn, vector<string> *Pan, 
		 vector<double> *P, vector<double> *L, vector<double> *A1, 
		 vector<double> *A2, vector<double> *A3, vector<double> *A4, 
		 vector<double> *DX, vector<double> *DY, vector<ApertureClass_t> *ApertureType);

double ReadTwissDXNoDrifts(string in, vector<string> *K, vector<string> *N, vector<string> *Pa, 
			 vector<string> *Kn, vector<string> *Nn, vector<string> *Pan, 
			 vector<double> *P, vector<double> *L, vector<double> *A1, 
			 vector<double> *A2, vector<double> *A3, vector<double> *A4, 
			 vector<double> *DX, vector<double> *DY, vector<ApertureClass_t> *ApertureType);

/*
* Reads the aperture type and converts it to an integer that gives the type of aperture for future operations.
* @parm ApType A string containing the type of Aperture.
* @return An ApertureClass_t that gives the aperture type as defined below
*/
ApertureClass_t GetApertureType(char* ApType);

#endif

