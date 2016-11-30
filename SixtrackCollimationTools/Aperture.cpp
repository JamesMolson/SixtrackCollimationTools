#include "Aperture.h"

Aperture::Aperture() : MyApert(), MyName(""), ApertureType(0), Dx_align(0), Dy_align(0), Angle(0), LostFlag(false), x_n(0), y_n(0), CorrectDefinition(false)
{
}

Aperture::~Aperture()
{
}

void Aperture::PutApert(double a1, double a2, double a3, double a4, ApertureClass_t ApertureT)
{
	double pi = atan2(0.0,-1.0);

	MyApert.clear();

	/*
	if ( // a3 ==0 || a4 == 0 || // This case now defines the rectangular aperture!
			 (a1 != 0 && a2 == 0) ||
			 (a1 == 0 && a2 != 0) )
	*/
	if(ApertureT == UNKNOWN || ApertureT == NONE )
	{
		std::cout << "ERROR: Invalid aperture definition!!" << std::endl;
		std::cout << a1 << " " << a2 << " " << a3 << " " << a4 << std::endl;
	}
	else
	{
		MyApert.clear();
		MyApert.push_back(a1);
		MyApert.push_back(a2);
		MyApert.push_back(a3);
		MyApert.push_back(a4);
	}

	// For rectangular aperture, A3=0 and A4=angle!
	if ( a3 == 0 )
	{
		Angle = a4 * pi / 180;
	}
}

void Aperture::PutApert(std::vector<double> ThisAp, ApertureClass_t ApertureT)
{
	double pi = atan2(0.0,-1.0);

	MyApert.clear();
	MyApert = ThisAp;
	ApertureType = ApertureT;

	// For rectangular aperture, A3=0 and A4=angle!
	if ( ThisAp[2] == 0 )
	{
		Angle = ThisAp[3] * pi / 180;
	}
}

double Aperture::GetApert(int n)
{
	return MyApert[n-1];
}

void Aperture::GiveName(std::string in)
{
	MyName = in;
}

std::string Aperture::GetName()
{
	return MyName;
}

/**
* New coordinates w.r.t. the aperture centre!
* First traslation, then the rotation!
*
* Check what happens for interpolated aperture, when the 
* resulting aperture does not correspond to one of the known types.
*
* SR, 07-09-2004
* In order to avoid the problems with the 'strange' apertures from 
* the fitting procedure, I add some checks to make the aperture
* definition compatible with 'known' aperture plots!
*/
bool Aperture::IsLostOld(double x, double y)
{
	double a1 = MyApert[0],
		a2 = MyApert[1],
		a3 = MyApert[2],
		a4 = MyApert[3];

	CorrectDefinition = false;
	if ( a1 > a3 && a3 != 0 )
	{
		a1 = a3;
		CorrectDefinition = true;
	}

	if ( a2 > a4 && a4 > 0)
	{
		a2 = a4;
		CorrectDefinition = true;
	}

	// Exclude RaceTrack and Coll!
	if ( a1 != 0. && a2 != 0. && a3 != 0. && a1 < a3 && a2 < a4 )
	{
		a3 = a1;
		a4 = a2;
		CorrectDefinition = true;
	}

	// Collimator with negative angle or angle > .5 (no apertures > 1!)
	// -> This will be recognized as a square, tilted aperture!
	if ( a4 < 0 || a4 > .5 )
	{
		a3 = 0;
		CorrectDefinition = true;
	}
	/*
	// Warning if aperture definition is changed.
	if ( CorrectDefinition ){
		cout<<setw(22)<<"Aperture definition:";
		cout<<setw(10)<<MyApert[0]<<setw(10)<<a2
	<<setw(10)<<MyApert[2]<<setw(10)<<MyApert[3]<<endl;
		cout<<setw(22)<<"corrected to:";
		cout<<setw(10)<<a1<<setw(10)<<a2
	<<setw(10)<<a3<<setw(10)<<a4<<endl;
	}
	*/

	//Put in adjustments for the survey offsets.
	x_n = x - Dx_align;
	y_n = y - Dy_align;

	//Rotate into the rectangular aperture plane
	double theta = atan2(y_n, x_n);
	double R = sqrt( x_n * x_n + y_n * y_n );
	x_n = R * cos( Angle - theta );
	y_n = R * sin( Angle - theta );


	//Finally check if the particle is within the aperture or not
	LostFlag = false;

	// RectEllipse
	if ( a1 != 0.0 && a3 > 0 )
	{
		if ( x_n*x_n/a3/a3 + y_n*y_n/a4/a4 >= 1 || fabs(x_n) >= a1 || fabs(y_n) >= a2)
		{
			LostFlag = true;
		}
	}
	// RaceTrack: remember to use Ap[2]/2!!
	else if (a1 == 0.0)
	{
		if ( fabs(x_n) <= a3 / 2 )
		{
			if (fabs(y_n) >= a4 )
			{
				LostFlag = true;
			}
		}
		else if ( fabs(x_n) > a3/2 )
		{
			if ( (fabs(x_n)-a3/2)*(fabs(x_n)-a3/2)+y_n*y_n >= a4*a4)
			{
				LostFlag = true;
			}
		}
	}
	else if ( a1 != 0.0 && a3 == 0 )
	{
		if ( fabs(x_n) >= a1 || fabs(y_n) >= a2 )
		{
			LostFlag = true;
		}
	}

	return LostFlag;
}

/**
* New version.
* Checks if a particle is lost.
* Uses the ApertureType field to determine the type of aperture, rather than try and calculate it from the aperture parameters.
* See http://madx.web.cern.ch/madx/releases/last-dev/madxuguide.pdf
*/
bool Aperture::IsLost(double x, double y)
{
	double a1 = MyApert[0],
		a2 = MyApert[1],
		a3 = MyApert[2],
		a4 = MyApert[3];

	//Put in adjustments for the survey offsets.
	x_n = x - Dx_align;
	y_n = y - Dy_align;

	//Rotate into the rectangular aperture plane
	double theta = atan2(y_n, x_n);
	double R = sqrt( x_n * x_n + y_n * y_n );
	x_n = R * cos( Angle - theta );
	y_n = R * sin( Angle - theta );


	//Finally check if the particle is within the aperture or not
	LostFlag = false;

	if(ApertureType == CIRCLE)
	{
		//Check we are within the circle
		if(((x_n*x_n) + (y_n*y_n)) >= (a1*a1))
		{
			LostFlag = true;
		}
	}
	else if(ApertureType == RECTELLIPSE)
	{
		//Need to check both the rectangular and elliptical component

		//Start with the ellipse - it defines the horizontal limit in most cases
		//The rectangle generally limits the top of the beamscreen (in the arc at least)
		//Most particles are lost in the area defined by the ellipse
		if((x_n*x_n)/(a3*a3) + (y_n*y_n)/(a4*a4) >= 1)
		{
			LostFlag = true;
		}

		//Then do the rectangle
		if(fabs(x_n) >= a1 || fabs(y_n) >= a2)
		{
			LostFlag = true;
		}
	}
	else if(ApertureType == RACETRACK)
	{
		// RaceTrack: remember to use Ap[2]/2!!
		if ( fabs(x_n) <= a3 / 2 )
		{
			if (fabs(y_n) >= a4 )
			{
				LostFlag = true;
			}
		}
		else if ( fabs(x_n) > a3/2 )
		{
			if ( (fabs(x_n)-a3/2)*(fabs(x_n)-a3/2)+y_n*y_n >= a4*a4)
			{
				LostFlag = true;
			}
		}
	}
	else if(ApertureType == RECTCIRCLE || ApertureType == LHCSCREEN)
	{
		//Circle first this time
		//For RECTCIRCLE the radius is stored in a3 (I think)
		if((x_n*x_n + y_n*y_n) >= (a3*a3))
		{
			LostFlag = true;
		}

		//Then the rectangle
		if(fabs(x_n) >= a1 || fabs(y_n) >= a2)
		{
			LostFlag = true;
		}
	}
	else if(ApertureType == ELLIPSE)
	{
		//Not sure if the parameters are in a1,a2 or a3,a4 - I think it is a3 and a4 - CHECK
		if((x_n*x_n)/(a3*a3) + (y_n*y_n)/(a4*a4) >= 1)
		{
			LostFlag = true;
		}
	}
	else if(ApertureType == RECTANGLE)
	{
		if(fabs(x_n) >= a1 || fabs(y_n) >= a2)
		{
			LostFlag = true;
		}
	}
	else if(ApertureType == OCTAGON)
	{
		//This is just taken from trrun.f90 in MAD-X. - credit to: 2015-Feb-20  18:42:26  ghislain: added octagon shape
		//Compute the tangents.
		double tana1 = tan(a3);
		double tana2 = tan((2*atan2(1,1)) - a4);

		//Make some constants.
		//(hh*tana2 - hw)
		double c1 = (a2*tana2 - a1);

		//hw*tana1
		double c2 = a1*tana1;

		//hh - hw*tana1
		double c3 = a2 - c2;
		double fabsx = fabs(x_n);
		double fabsy = fabs(y_n);

		//First check the rectangle
		if(fabsx >= a1 || fabsy >= a2)
		{
			LostFlag = true;
		}

		if(c1*(fabsy - c2) - c3*(fabsx - a1) <= 0 )
		{
			LostFlag = true;
		}
	}
	else if(ApertureType == INTERPOLATED)
	{
		//cout << "INTERPOLATED - x: " << x << "\ty: " << y << "\ta1: " << a1 << "\ta2: " << a2 << "\ta3: " << a3 << "\ta4: " << a4 << endl;
		//Difficult to deal with
		//Assume rectellipse for now...

		if((x_n*x_n)/(a3*a3) + (y_n*y_n)/(a4*a4) >= 1)
		{
			LostFlag = true;
		}

		//Then do the rectangle
		if(fabs(x_n) >= a1 || fabs(y_n) >= a2)
		{
			LostFlag = true;
		}
	}
	else if(ApertureType == NONE)
	{
		//Do nothing
	}
	else if(ApertureType == UNKNOWN)
	{
		std::cerr << "Unknown aperture type requested - BUG" << std::endl;
		std::cerr << "x: " << x << "\ty: " << y << "\ta1: " << a1 << "\ta2: " << a2 << "\ta3: " << a3 << "\ta4: " << a4 << std::endl;
		std::cerr << "ApertureType: " << ApertureType << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cerr << "This should not be reached - ApertureType error" << std::endl;
		std::cerr << "x: " << x << "\ty: " << y << "\ta1: " << a1 << "\ta2: " << a2 << "\ta3: " << a3 << "\ta4: " << a4 << std::endl;
		std::cerr << "ApertureType: " << ApertureType << std::endl;
		exit(EXIT_FAILURE);
	}

	return LostFlag;
}

double Aperture::GiveAperture(double q)
{
	// WARNING: If this memebr is modified, also PlotAperture should be change accordingly!!!

	double pi = atan2(0.0,-1.0);
	double T, Tc;
	double Dx_tmp = 0, Dy_tmp = 0, DT_tmp = 0;

	double a1 = MyApert[0], 
		a2 = MyApert[1], 
		a3 = MyApert[2],
		a4 = MyApert[3],
		a3r = a3 / 2;	 // ForRaceTrack

	// Angle in radiants
	T = q * pi / 180;
	if (T > pi || T < -pi)
	{
		std::cout << "Please choose and angle between -pi and pi!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Take the angle into accout
	T = T - Angle;

	// Check to avoid unknown combination of RectEllipse apertures.
	// (this will be repeated in IsLost!)
	CorrectDefinition = false;
	if ( a1 > a3 && a3 != 0 )
	{
		a1 = a3;
		CorrectDefinition = true;
	}

	if ( a2 > a4 && a4 > 0)
	{
		a2 = a4;
		CorrectDefinition = true;
	}

	// Exclude RaceTrack and Coll!
	if ( a1 != 0. && a2 != 0. && a3 != 0. && a1 < a3 && a2 < a4 )
	{
		a3 = a1;
		a4 = a2;
		CorrectDefinition = true;
	}

	// Collimator with negative angle or angle > .5 (no apertures > 1!)
	// -> This will be recognized as a square, tilted aperture!
	if ( a4 < 0 || a4 > .5 )
	{
		a3 = 0;
		CorrectDefinition = true;
	}

	/*
	if ( CorrectDefinition ){
		cout<<setw(22)<<"Aperture definition:";
		cout<<setw(10)<<MyApert[0]<<setw(10)<<MyApert[1]
	<<setw(10)<<MyApert[2]<<setw(10)<<MyApert[3]<<endl;
		cout<<setw(22)<<"corrected to:";
		cout<<setw(10)<<a1<<setw(10)<<a2
	<<setw(10)<<a3<<setw(10)<<a4<<endl;
	}
	*/

	// Always use an angle in the first quadrant and
	// assign the corresponding sign to the displacements
	double sign_x = 1.0, sign_y = 1.0;

	if (T > pi/2 || T < -pi/2)
	{
		sign_x = -1.0;
	}

	if (T < 0.0)
	{
		sign_y = -1.0;
	}

	if ( T < -pi/2 )
	{
		T = pi + T;
	}
	else if ( T >= -pi/2 && T < 0 )
	{
		T = -T;
	}
	else if ( T > pi/2 )
	{
		T = pi - T;
	}

	// Elliptical aperture
	if ( a1 == a3 && a2 == a4 )
	{
		Dx_tmp = sign_x * a3 * sqrt(1/(1+a3*a3*tan(T)*tan(T)/a4/a4));
		Dy_tmp = sign_y * fabs(Dx_tmp * tan(T));
	}
	// Cut parallel to x axis
	else if ( a1 == a3 && a2 < a4 )
	{
		Tc = atan(a2/a3/sqrt(1-a2*a2/a4/a4));
		//if ( T <= (Tc-pi) || (T >= -Tc && T <= Tc) || T >= pi-Tc ){		// -> Elliptical part

		// -> Elliptical part
		if ( T <= Tc )
		{
			Dx_tmp = sign_x * a3 / sqrt( 1+a3*a3*tan(T)*tan(T)/a4/a4 );
			Dy_tmp = sign_y * fabs(Dx_tmp * tan(T));
		}
		// -> Straight part
		else
		{
			Dy_tmp = sign_y * a2;
			Dx_tmp = sign_x * fabs(Dy_tmp * tan( pi/2-T ));
		}
	}
	// Cut parallel to y axis
	else if ( a1 < a3 && a2 == a4 )
	{
			Tc = atan( a4*sqrt(1-a1*a1/a3/a3)/a1 );
			//if ( T <= (Tc-pi) || (T >= -Tc && T <= Tc) || T >= pi-Tc ){ // -> Straight part

			// -> Straight part
			if ( T <= Tc )
			{
				Dx_tmp = sign_x * a1;
				Dy_tmp = sign_y * fabs(Dx_tmp * tan(T));
			}
			// -> Elliptical part
			else
			{
				Dx_tmp = sign_x * a3 / sqrt( 1+a3*a3*tan(T)*tan(T)/a4/a4 );
				Dy_tmp = sign_y * fabs(Dx_tmp * tan(T));
			}
	}
	// RaceTrack
	else if ( a1 == 0 && a2 == 0 )
	{
		Tc = atan2( a4, a3r );

		// -> Flat part
		if ( T >= Tc )
		{
			Dx_tmp = sign_x * fabs(a4 * tan( pi/2-T ));
			Dy_tmp = sign_y * a4;
		}
		// -> Circular part
		else
		{
			Dx_tmp = sign_x * (a3r+sqrt(a4*a4-a3r*a3r*tan(T)*tan(T)+a4*a4*tan(T)*tan(T))) / (1+tan(T)*tan(T));
			Dy_tmp = sign_y * Dx_tmp * tan(T);
		}
	}
	// Collimator aperture (rectangular + tilt)
	else if ( a3 == 0 )
	{
		Tc = atan2(a2, a1);

		if (T <= Tc)
		{
			Dx_tmp = sign_x * a1;
			Dy_tmp = sign_y * a1 * fabs( tan(T) );
		}
		else
		{
			Dx_tmp = sign_x * a2 * fabs( tan(pi/2-T) );
			Dy_tmp = sign_y * a2;
		}
	}
	else
	{
		std::cout << "WARNING: The given aperture is not classified among the known types" << std::endl;
		std::cout << "         A1=" << a1 << " A2=" << a2 << " A3=" << a3 << " A4=" << a4 << std::endl;

		// Temporary solution: I give the smallest value of x
		if (a1 > a3)
		{
			Dx_tmp = a1;
		}
		else
		{
			Dx_tmp = a3;
		}

		if (a2 > a4)
		{
			Dx_tmp = a4;
		}
		else
		{
			Dx_tmp = a2;
		}
	}

	DT_tmp = sqrt(Dx_tmp*Dx_tmp+Dy_tmp*Dy_tmp);

	return DT_tmp;
}

void Aperture::PlotAperture(std::string output)
{
	double pi = atan2(0.0,-1.0);

	double T, Tc, T_n, Dx_tmp, Dy_tmp, DT_tmp, q;
	double a1 = MyApert[0], 
		a2 = MyApert[1], 
		a3 = MyApert[2], 
		a4 = MyApert[3], 
		a3r = a3 / 2;
	double sign_x,sign_y;

	size_t N = 200; // number of point to plot

	CorrectDefinition = false;
	if ( a1 > a3 && a3 != 0 )
	{
		a1 = a3;
		CorrectDefinition = true;
	}

	if ( a2 > a4 && a4 > 0)
	{
		a2 = a4;
		CorrectDefinition = true;
	}

	// Exclude RaceTrack and Coll!
	if ( a1 != 0. && a2 != 0. && a3 != 0. && a1 < a3 && a2 < a4 )
	{
		a3 = a1;
		a4 = a2;
		CorrectDefinition = true;
	}

	// Collimator with negative angle or angle > .5 (no apertures > 1!)
	// -> This will be recognized as a square, tilted aperture!
	if ( a4 < 0 || a4 > .5 )
	{
		a3 = 0;
		CorrectDefinition = true;
	}
	/*
	if ( CorrectDefinition ){
		cout<<setw(22)<<"Aperture definition:";
		cout<<setw(10)<<MyApert[0]<<setw(10)<<a2
	<<setw(10)<<MyApert[2]<<setw(10)<<MyApert[3]<<endl;
		cout<<setw(22)<<"corrected to:";
		cout<<setw(10)<<a1<<setw(10)<<a2
	<<setw(10)<<a3<<setw(10)<<a4<<endl;
	}
	*/

	std::ofstream out;
	out.open(output.c_str());

	for (size_t i = 0; i < N; i++)
	{
		q = -180+360*static_cast<double>(i)/static_cast<double>(N);
		T = q * pi / 180;
		T_n = T; // For later use, I need the angle in [-pi:pi]

		sign_x = 1.0;
		sign_y = 1.0;

		if (T > pi/2 || T < -pi/2)
		{
			sign_x = -1.0;
		}

		if (T < 0.0)
		{
			sign_y = -1.0;
		}

		if ( T < -pi/2 )
		{
			T = pi + T;
		}
		else if ( T >= -pi/2 && T < 0 )
		{
			T = -T;
		}
		else if ( T > pi/2 ) 
		{
			T = pi - T;
		}

		// Elliptical aperture
		if ( a1 == a3 && a2 == a4 )
		{
			Dx_tmp = sign_x * a3 * sqrt(1/(1+a3*a3*tan(T)*tan(T)/a4/a4));
			Dy_tmp = sign_y * fabs(Dx_tmp * tan(T));
		}
		// Cut parallel to x axis
		else if ( a1 == a3 && a2 < a4 )
		{
			Tc = atan(a2/a3/sqrt(1-a2*a2/a4/a4));

			if ( T <= Tc )
			{
				Dx_tmp = sign_x * a3 / sqrt( 1+a3*a3*tan(T)*tan(T)/a4/a4 );
				Dy_tmp = sign_y * fabs(Dx_tmp * tan(T));
			}
			else
			{
				Dy_tmp = sign_y * a2;
				Dx_tmp = sign_x * fabs(Dy_tmp * tan( pi/2-T ));
			}
		}
		// Cut parallel to y axis
		else if ( a1 < a3 && a2 == a4 )
		{
			Tc = atan( a4*sqrt(1-a1*a1/a3/a3)/a1 );

			if ( T <= Tc )
			{
				Dx_tmp = sign_x * a1;
				Dy_tmp = sign_y * fabs(Dx_tmp * tan(T));
			}
			else
			{
				Dx_tmp = sign_x * a3 / sqrt( 1+a3*a3*tan(T)*tan(T)/a4/a4 );
				Dy_tmp = sign_y * fabs(Dx_tmp * tan(T));
			}
		}
		// RaceTrack
		else if ( a1 == 0 && a2 == 0 )
		{
			Tc = atan2( a4, a3r );

			if ( T >= Tc )
			{
				Dx_tmp = sign_x * fabs(a4 * tan( pi/2-T ));
				Dy_tmp = sign_y * a4;
			}
			else
			{
				Dx_tmp = sign_x * (a3r+sqrt(a4*a4-a3r*a3r*tan(T)*tan(T)+a4*a4*tan(T)*tan(T))) / (1+tan(T)*tan(T));
				Dy_tmp = sign_y * Dx_tmp * tan(T);
			}
		}
		// Collimator aperture (rectangular + tilt)
		else if ( a3 == 0 )
		{
			Tc = atan2(a2, a1);

			if (T <= Tc)
			{
				Dx_tmp = sign_x * a1;
				Dy_tmp = sign_y * a1 * fabs( tan(T) );
			}
			else
			{
				Dx_tmp = sign_x * a2 * fabs( tan(pi/2-T) );
				Dy_tmp = sign_y * a2;
			}
		}
		else
		{
			std::cout << "WARNING: The given aperture is not classified among the known types" << std::endl;
			std::cout << "         A1=" << a1 << " A2=" << a2 << " A3=" << a3 << " A4=" << a4 << std::endl;
		}

		DT_tmp=sqrt(Dx_tmp*Dx_tmp+Dy_tmp*Dy_tmp);

		// Rotate first, and then displace!
		out << std::setw(8) << q;
		//out<<setw(15)<<T;
		//out<<setw(15)<<Dx_tmp;
		//out<<setw(15)<<Dy_tmp;
		//out<<setw(15)<<Dx_tmp + Dx_align;
		//out<<setw(15)<<Dy_tmp + Dy_align;
		//out<<setw(15)<<Dx_tmp * cos( Angle ) + Dx_align;
		//out<<setw(15)<<Dy_tmp * sin( Angle + pi / 2 )+ Dy_align;
		out << std::setw(15) << DT_tmp * cos( Angle + T_n ) + Dx_align;
		out << std::setw(15) << DT_tmp * sin( Angle + T_n ) + Dy_align;
		out << std::setw(15) << DT_tmp << std::endl; // In aperture frame!
	}
	out.close();
}

void Aperture::SetApertAlign(double dx, double dy)
{
	Dx_align = dx;
	Dy_align = dy;
}

double Aperture::GetApertAlignX()
{
	return Dx_align;
}

double Aperture::GetApertAlignY()
{
	return Dy_align;
}

void Aperture::SetAngle(double ang)
{
	double pi = atan2(0.0,-1.0);
	Angle = ang * pi / 180;
}

double Aperture::GetAngle()
{
	return Angle;
}

void Aperture::empty()
{
	MyApert.clear();
	Dx_align = 0;
	Dy_align = 0;
	Angle = 0;
	ApertureType = 0;
}

ApertureClass_t Aperture::GetApertureType()
{
	return ApertureType;
}

ApertureClass_t FindApertureType(size_t i, size_t j, std::vector<ApertureClass_t> ApertureType)
{
    if(ApertureType[i] == ApertureType[j])
    {
        return ApertureType[i];
    }
    else
    {
        return INTERPOLATED;
    }
}
