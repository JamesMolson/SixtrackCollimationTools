/**
 * Write the Accelerator aperture along the ring for various 
 * azimuthal angles.
 */

#include "ReadTwiss.h"
#include "Aperture.h"
#include "OneMetre.h"
#include "AssignOneMetre.h"

double CheckPos(double pp, double AcceleratorLength); // See CheckPos.cpp

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "ERROR in the input definition!" << std::endl;
		std::cout << "Command line should look like:" << std::endl;
		std::cout << "-> " << argv[0] << " ApertureFile.dat <-" << std::endl;
		exit(EXIT_FAILURE);
	}

	//////////////////////////////
	// Setup the aperture model //
	//////////////////////////////

	// Load the Accelerator sequence with apertures
	std::vector<OneMetre> Accelerator;
	std::vector<std::string> Keyword, Name, Parent;
	std::vector<std::string> KeywordNoQuotes, NameNoQuotes, ParentNoQuotes;
	std::vector<double> Position, Length, Apert1, Apert2, Apert3, Apert4;
	std::vector<ApertureClass_t> ApertureType;

	// Read twiss file with apertures (no drifts!)
	//	ReadTwissNoDrifts("allaper_inj_20041008.b1", &Keyword, &Name, &Parent, &KeywordNoQuotes, 

	std::cout << "Reading aperture file " << argv[1] << std::endl;

	double AcceleratorLength = ReadTwissNoDrifts(argv[1], &Keyword, &Name, &Parent, &KeywordNoQuotes, &NameNoQuotes, &ParentNoQuotes, &Position, &Length, &Apert1, &Apert2, &Apert3, &Apert4, &ApertureType);

	size_t OldPrecision = std::cout.precision(16);
	std::cout << "Found accelerator length from MAD headers: " << AcceleratorLength << std::endl;
	std::cout.precision(OldPrecision);

	//AssignOneMetre(&Accelerator, Keyword, Name, Parent, Position, Length, Apert1, Apert2, Apert3, Apert4, ApertureType, AcceleratorLength);
	AssignOneMetre(&Accelerator, Keyword, Position, Length, Apert1, Apert2, Apert3, Apert4, ApertureType, AcceleratorLength);

	std::cout << "Length of the read sequence: " << Accelerator.size() << " metres." << std::endl << std::endl;

	// Clean-up here the variable no longer needed:
	Keyword.clear();
	Name.clear();
	Parent.clear();
	KeywordNoQuotes.clear();
	NameNoQuotes.clear();
	ParentNoQuotes.clear();
	Position.clear();
	Length.clear();
	Apert1.clear();
	Apert2.clear();
	Apert3.clear();
	Apert4.clear();
	ApertureType.clear();

	// Write Aperture vs s every 10 cm
	std::ofstream out_Accelerator("AcceleratorAperture.dat");
	std::cout << "Writing output to AcceleratorAperture.dat" << std::endl;
	out_Accelerator << "%1=s [km]; 2=Ax [m]; 3=Ay [m]; 4=A45deg [m]" << std::endl;

	Aperture Atmp;
	double s;

	for (size_t i = 0; i < Accelerator.size(); i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			s = static_cast<double>(i) + static_cast<double>(j) / 10;
			Atmp = Accelerator[static_cast<size_t>(s)].GetAperture(static_cast<double>(j)/10);
			out_Accelerator.precision(7);
			out_Accelerator << std::setw(12) << s;
			out_Accelerator.precision(6);
			out_Accelerator << std::setw(14) << Atmp.GiveAperture( 0.0 );
			out_Accelerator << std::setw(14) << Atmp.GiveAperture( 90.0 );
			out_Accelerator << std::setw(14) << Atmp.GiveAperture( 45.0 );
			out_Accelerator << std::endl;
			Atmp.empty();
		}
	}
	out_Accelerator.close();

	return EXIT_SUCCESS;
}

double CheckPos (double pp, double AcceleratorLength)
{
	if ( pp < 0.0 )
	{
		pp = AcceleratorLength + pp;
	}

	if ( pp > AcceleratorLength )
	{
		pp = pp - AcceleratorLength;
	}

	return pp;
}

