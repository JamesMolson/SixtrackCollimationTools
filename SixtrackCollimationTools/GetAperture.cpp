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
		cout << "ERROR in the input definition!" << endl;
		cout << "Command line should look like:" << endl;
		cout << "-> GetAperture ApertureFile.dat <-" << endl;
		return 0;
	}

	//////////////////////////////
	// Setup the aperture model //
	//////////////////////////////

	// Load the Accelerator sequence with apertures
	vector<OneMetre> Accelerator;
	vector<string> Keyword, Name, Parent;
	vector<string> KeywordNoQuotes, NameNoQuotes, ParentNoQuotes;
	vector<double> Position, Length, Apert1, Apert2, Apert3, Apert4;

	// Read twiss file with apertures (no drifts!)
	//	ReadTwissNoDrifts("allaper_inj_20041008.b1", &Keyword, &Name, &Parent, &KeywordNoQuotes, 

	cout << "Reading aperture file " << argv[1] << endl;

	double AcceleratorLength = ReadTwissNoDrifts(argv[1], &Keyword, &Name, &Parent, &KeywordNoQuotes, &NameNoQuotes, &ParentNoQuotes, &Position, &Length, &Apert1, &Apert2, &Apert3, &Apert4);

	size_t OldPrecision = cout.precision(16);
	cout << "Found accelerator length from MAD headers: " << AcceleratorLength << endl;
	cout.precision(OldPrecision);

	AssignOneMetre(&Accelerator, Keyword, Name, Parent, Position, Length, Apert1, Apert2, Apert3, Apert4, AcceleratorLength);

	cout << "Length of the read sequence: " << Accelerator.size() << " metres." << endl << endl;

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

	// Write Aperture vs s every 10 cm
	ofstream out_Accelerator("AcceleratorAperture.dat");
	out_Accelerator<<"%1=s [km]; 2=Ax [m]; 3=Ay [m]; 4=A45deg [m]"<<endl;

	Aperture Atmp;
	double s;

	for (size_t i = 0; i < Accelerator.size(); i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			s = static_cast<double>(i) + static_cast<double>(j) / 10;
			Atmp = Accelerator[static_cast<size_t>(s)].GetAperture(static_cast<double>(j)/10);
			out_Accelerator.precision(7);
			out_Accelerator << setw(12) << s;
			out_Accelerator.precision(6);
			out_Accelerator <<setw(14) << Atmp.GiveAperture( 0.0 );
			out_Accelerator <<setw(14) << Atmp.GiveAperture( 90.0 );
			out_Accelerator <<setw(14) << Atmp.GiveAperture( 45.0 );
			out_Accelerator << endl;
			Atmp.empty();
		}
	}
	out_Accelerator.close();

	return 0;
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

