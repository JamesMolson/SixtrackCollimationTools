#ifndef _APERTURETYPES_H_
#define _APERTURETYPES_H_ 1

#include <vector>

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

#endif

