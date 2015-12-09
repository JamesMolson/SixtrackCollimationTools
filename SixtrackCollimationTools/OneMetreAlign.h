/**
* OneMetreAlign.h (SR, June 2004)
*
*/

#include "Aperture.h"

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

using namespace std;

#ifndef OneMetreAlign_h
#define OneMetreAlign_h 1

class OneMetreAlign
{
private:

	/**
	* Position where aperture is defined.
	*/
	vector<double> Pos;

	/**
	* Corresponding apertures.
	*/
	vector<Aperture> Apert;

	/**
	* Corresponding alignment statements.
	*/
	vector<double> DxAlign,	DyAlign;

	/**
	* Extended position and aperture vector with additional
	*/
	vector<double> Pos_ex;

	/**
	* definitions at 0.0 and 1.0, for aperture interpolation.
	*/
	vector<Aperture> Apert_ex;

	/**
	* Defined once for all the fist time that 'GetAperture' is called
	*/
	vector<double> DxAlign_ex, DyAlign_ex;

	/**
	* Aperture in vector format - useful later
	*/
	//vector<double> Apert_vec; 

	Aperture Atmp;

	/**
	* Index of positions with defined aperture
	*/
	//vector<int> ind;

	/**
	* Temporary vector for various internal uses
	*/
	vector<double> Atmp_vec;

	double DxA, DyA;

public:

	OneMetreAlign();
	~OneMetreAlign();

	// If alignment is not defined, put it to zero!
	void DefineAperture(double p, double a1, double a2, double a3, double a4);
	void DefineAperture(double p, Aperture Ap);
	void DefineAperture(double p, vector<double> A4);

	void DefineApertureAlign(double p, double a1, double a2, double a3, double a4, double Dx, double Dy);
	void DefineApertureAlign(double p, Aperture Ap, double Dx, double Dy);
	void DefineApertureAlign(double p, vector<double> A4, double Dx, double Dy);

	void GetApertDef(vector<double> *Position, vector<Aperture> *ThisApert);

	/**
	* Get aperture at a given position
	*/
	Aperture GetAperture(double p);

	double GetAlignX(double p);
	double GetAlignY(double p);

	void empty();
	void status();
};

#endif

