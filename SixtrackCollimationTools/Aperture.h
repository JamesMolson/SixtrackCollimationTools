/**
* Aperture.m (SR, May 2004)
*
* Definition of the 'Aperture' object. 
* This objects contains the definition of 4 numbers that define
* the aperture according to the MADX "RectEllipse" notation.
*
* One can also define the name of an aperture object (possible 
* useful for later studies, when the aperture of some type 
* could be displaced according to some models for the magnet 
* misalignment).
*
* Other members of this class are the following:
*
*	 int IsLost(double x, double y); -> Says if a particle is lost
*
*	 double ApertVsAngle(double alpha); -> gives the radias aperture at the angle theta
*
*
* ***********
* * UPDATES *
* ***********
*
* SR, 24 June 2004: Add RECTANGULAR aperture to treat 
* ================	collimators and other movable elements!
*									 Skew collimators are not included yet!
*
*	 Rectangular aperture is denoted with A3=0 ans A4=0;
* 
*	 Modified member functions: -> IsLost(double, double)
*															-> GiveAperture( double )
*															-> PlotAperture( string )
*								 (Update also the others AS SOON AS POSSIBLE)
*
*
* SR, 25 June 2004: Add ANGLE as aperture property.
* ================	For rectangular apertures, it is assumed that 
*									 A4 is the angle!
*
*
* Remark: For later studies, it will be potentially useful to add
*				 an 'Alignment' property of the aperture, which says
*				 the closed-orbit position as calculated with 'Survey'.
*
*
* SR, 07 September 2004: Add checks to eliminate the unknown aperture types 
* =====================	created in the fitting procedure. This is done 
*												by adding some checks before running the 'IsLost'
*												function.
*
*
* SR, 18 February 2005: The 'GiveAperture' function takes now into account 
* ====================	the TILT angle. The alignment error is not taken into
*											 account. Still have to decide how to treat the alignment...
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

#ifndef Aperture_h
#define Aperture_h 1

using namespace std;

/**
 * Typedef for access to the enum
 */
typedef size_t ApertureClass_t;

/**
 * See the MAD users guide for how these apertures are defined.
 * (current as of V5.02.07)
 * http://madx.web.cern.ch/madx/releases/last-dev/madxuguide.pdf
 * "Physical Aperture: Aperture definition"
 *
 * Interpolated in this case is where one type joins another.
 */
typedef enum
{
    NONE,
    UNKNOWN,
    CIRCLE,
    RECTANGLE,
    ELLIPSE,
    RECTCIRCLE,
    LHCSCREEN,
    RECTELLIPSE,
    RACETRACK,
    OCTAGON,
    INTERPOLATED
} ApertureClass;


class Aperture
{
private:

	/**
	* A vector containing the 4 aperture definition parameters.
	*/
	vector<double> MyApert;

	/**
	* The name of this aperture
	*/
	string MyName;

	/**
	* The type of this aperture.
	* @see ApertureTypes.h
	*/
	ApertureClass_t ApertureType;

	double Dx_align, Dy_align;

	/**
	* The angle of a rectangular aperture.
	*/
	double Angle;

	/**
	* Is this particle lost?
	*/
	bool LostFlag;

	double x_n, y_n;

	bool CorrectDefinition;

public:

	Aperture();
	~Aperture();

	/**
	* Adds an aperture definition using the 4 parameters and the aperture type.
	* @param[in] a1 Aperture definition parameter 1.
	* @param[in] a2 Aperture definition parameter 2.
	* @param[in] a3 Aperture definition parameter 3.
	* @param[in] a4 Aperture definition parameter 4.
	* @param[in] ApertureT The type of this aperture.
	*/
	void PutApert(double a1, double a2, double a3, double a4, ApertureClass_t ApertureT);

	/**
	* Adds an aperture definition using the 4 parameters contained in a vector and the aperture type.
	* @param[in] ThisAp A vector containing the 4 aperture parameters.
	* @param[in] ApertureT The type of this aperture.
	*/
	void PutApert(vector<double> ThisAp, ApertureClass_t ApertureT);

	/**
	* Gets one of the 4 aperture parameters
	* @param[in] n An integer corresponding to the requested aperture parameter from 1 to 4;
	* @return The requested aperture parameter value.
	*/
	double GetApert(int n);

	/**
	* Gets all of the 4 aperture parameters.
	* @return A vector containing all 4 aperture parameters.
	*/
	vector<double> GetApert();

	/**
	* Sets a name for this aperture.
	* @param[in] in The name to set.
	*/
	void GiveName(string in);

	/**
	* Gets the name for this aperture.
	* @return A string containing the name of this aperture.
	*/
	string GetName();

	/**
	* Is a particle lost at this aperture?
	* @param x The x coordinate of the particle.
	* @param y The y coordinate of the particle.
	* @return A bool set to true if the particle is lost.
	*/
	bool IsLostOld(double x, double y);

	/**
	* Is a particle lost at this aperture?
	* This is the updated version to take into account the ApertureType.
	* @param x The x coordinate of the particle.
	* @param y The y coordinate of the particle.
	* @return A bool set to true if the particle is lost.
	*/
	bool IsLost(double x, double y);

	/**
	* Give aperture at a given angle theta
	*/
	double GiveAperture(double q);

	/**
	* Plot the aperture profile
	*/
	void PlotAperture(string output);

	void SetApertAlign(double dx, double dy);
	double GetApertAlignX();
	double GetApertAlignY();

	void SetAngle(double ang);
	double GetAngle();

	/**
	* Resets/clears out this aperture object.
	*/
	void empty();

	/**
	* Gets the type of this aperture.
	*/
	ApertureClass_t GetApertureType();
};

/**
 * Find the aperture type
 * If the type of i and j are the same, return the type.
 * If they are different, return INTERPOLATED
 *
 * Could possibly return the sum of the enum types to determine which types are merging.
 *
 * @param[in] i An index for an entry in ApertureType to perform a comparison on.
 * @param[in] j An index for an entry in ApertureType to perform a comparison on.
 * @return An ApertureClass_t with the type of aperture for this entry.
 */
ApertureClass_t FindApertureType(size_t i, size_t j, std::vector<ApertureClass_t> ApertureType);


#endif

