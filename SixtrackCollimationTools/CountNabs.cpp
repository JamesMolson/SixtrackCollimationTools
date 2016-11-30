/**
* SR, 22-04-2005
* New version of the program to count the ACTUAL number of 
* absorbed particles in the collimators by comparison with 
* the loss locations in the LPI files.
* This program uses the new SixTrack output 'all_absorptions.dat',
* which contains already the absorption locations (an not the
* full list of impacts...).
* The program does the analysis for one file (no loops) and hence
* it is suitable for performing the analysis on batch!
*
* *******************
* FindNabs.cpp
* Like in the script style, it takes as input seed numbers,
* energy, halo type and optics.
* The program compares the LPI files and the impacts files
* to count the actual number of absorbed particles by 
* excluding from the impact files the protons that have 
* touched the aperture somewhere before impacting on
* the collimators. 
* *************************
*/

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

int main (int argc, char* argv[])
{

	if (argc < 5)
	{
		std::cout << "Some input is missing!" << std::endl;
		std::cout << "The command line should look like:" << std::endl;
		std::cout << "-> " << argv[0] << " s1 tracks2.dat EN optics <-" << std::endl;
		exit(EXIT_FAILURE);
	}

	int s1;
	std::string halo, EN, optics;

	s1 = static_cast<int>(atof(argv[1]));
	halo = argv[2];
	EN = argv[3];
	optics = argv[4];

	std::cout << std::endl << " Summary of input parameters: " << std::endl;
	std::cout << std::setw(20) << "Seed:" << std::setw(9) << s1 << std::endl;
	std::cout << std::setw(20) << "Halo type:" << "  " << halo << std::endl;
	std::cout << std::setw(20) << "Beam energy:" << "  " << EN << std::endl;
	std::cout << std::setw(20) << "Optics:" << "  " << optics << std::endl << std::endl;

	int Np_t, Ntu_t, Hflag_t, Nsurv_t;
	double S_t, x_t, xp_t, y_t, yp_t, e_t;
	std::vector<int> NPART, NTURN;
	std::vector<double> POS;
	size_t Nmax = 50000;
	std::vector<int> NPART_lost, NTURN_lost;
	std::vector<double> POS_lost;
	std::vector<int> NPART_real, NTURN_real;
	std::vector<double> POS_real;
	std::vector<int> NPART_fake, NTURN_fake;
	std::vector<double> POS_fake;
	int count_ir7, count_ir3;
	double p;

	std::ostringstream ost;
	std::ifstream in, inn;
	std::ofstream out;
	char c_str[256];
	std::string input, output;


	// Set input/output names for the impact files
	ost << "all_absorptions." << s1 << "." << halo << "." << EN << "." << optics << ".dat";
	input = ost.str();
	ost.str("");
		
	// Read input file, create clean output and prepare required vector
	in.open(input.c_str(), std::ios::in);
	if (!in)
	{
		std::cout << "Impossible to open the file \"" << input << "\"!!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "-> Reading impact file: \"" << input << "\" <-" << std::endl << std::endl;
	in.getline(c_str,256); // Skip the header line
	while (true)
	{
		in >> Np_t >> Ntu_t >> S_t;

		if (!in.good())
		{
			break;
		}

		NPART.push_back(Np_t);
		NTURN.push_back(Ntu_t);
		POS.push_back(S_t);
	}
	in.close();

	// Read the loss file
	// Initialization
	for (size_t i=0; i<Nmax; i++)
	{
		NPART_lost.push_back(0);
		NTURN_lost.push_back(0);
		POS_lost.push_back(0.0);
	}

	ost << "LPI_BeamLoss." << s1 << "." << halo << "." << EN << "." << optics << ".s";
	input = ost.str();
	ost.str("");
	inn.open(input.c_str(), std::ios::in);

	if (!inn)
	{
		std::cout << "Impossible to open the file \"" << input << "\"!!" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "-> Reading loss file: \"" << input << "\" <-" << std::endl << std::endl;

	inn.getline(c_str,256); // Skip the header line
	while (true)
	{
		inn >> Np_t >> Ntu_t >> S_t >> x_t >> xp_t >> y_t >> yp_t >> e_t >> Hflag_t >> Nsurv_t;

		if (!inn.good())
		{
			break;
		}

		NPART_lost[Np_t] = 1;
		NTURN_lost[Np_t] = Ntu_t;
		POS_lost[Np_t] = S_t;
	}
	inn.close();
	
	// Compare the positions of loss particles with the impact locations
	for (size_t i = 0; i < NPART.size(); i++)
	{
		Np_t = NPART[i];

		if (NPART_lost[Np_t] == 0)
		{
			NPART_real.push_back( Np_t );
			NTURN_real.push_back( NTURN[i] );
			POS_real.push_back( POS[i] );
		}
		else
		{
			if ( NTURN[i] <= NTURN_lost[Np_t] && POS[i] < POS_lost[Np_t] )
			{
				NPART_real.push_back( Np_t );
				NTURN_real.push_back( NTURN[i] );
				POS_real.push_back( POS[i] );
			}
			else
			{
				NPART_fake.push_back( Np_t );
				NTURN_fake.push_back( NTURN[i] );
				POS_fake.push_back( POS[i] );
			}
		}
	}

	std::cout << "Number of particles touching the aperture before being lost "
		<< "in a collimator: " << NPART.size()-NPART_real.size() << std::endl << std::endl;

	if ( NPART_real.size() != NPART_fake.size() )
	{
		std::cout << "Warning: sum of real and fake impacts does not give the total" << std::endl
			<< "				 number of absorbed particles!" << std::endl;
	}

	// Count the losses in IR3/IR7
	count_ir3 = 0;
	count_ir7 = 0;

	for (size_t i = 0; i < NPART_real.size(); i++)
	{
		p = POS_real[i];

		if ( p > 6395.8168 && p < 6933.6248 )
		{
			count_ir3++;
		}
		else if ( p > 19725.2584 && p < 20263.0664)
		{
			count_ir7++;
		}
	}

	std::cout << "*******************************************************" << std::endl;
	std::cout << "*  Summary of partile absorptions in the collimators  *" << std::endl; 
	std::cout << "*******************************************************" << std::endl;
	std::cout << "*" << std::setw(40) << "Total number of SixTrack impacts:"<< std::setw(12) << NPART.size() << " *" << std::endl;
	std::cout << "*" << std::setw(40) << "Total number of REAL impacts:" << std::setw(12) << NPART_real.size() << " *" << std::endl;
	std::cout << "*" << std::setw(40) << "Total number of FAKE impacts:" << std::setw(12) << NPART_fake.size() << " *" << std::endl;
	std::cout << "*" << std::setw(40) << "Absorptions in the IR7 collimators:" << std::setw(12) << count_ir7 << " *" << std::endl;
	std::cout << "*" << std::setw(40) << "Absorptions in the IR3 collimators:" << std::setw(12) << count_ir3 << " *" << std::endl;
	std::cout << "*******************************************************" << std::endl;

	// Write output file for REAL impacts
	ost<<"all_absorptions."<<s1<<"."<<halo<<"."<<EN<<"."<<optics<<".real.dat";
	output = ost.str();
	ost.str("");
	std::cout << "Name of the REAL impact file: \""<<output<<"\"."<< std::endl << std::endl;

	out.open(output.c_str());
	out << "%*******************************************************" << std::endl;
	out << "%*  Summary of partile absorptions in the collimators  *" << std::endl; 
	out << "%*******************************************************" << std::endl;
	out << "%*"<< std::setw(40) << "Total number of SixTrack impacts:" << std::setw(12) << NPART.size() << " *" << std::endl;
	out << "%*"<< std::setw(40) << "Total number of REAL impacts:" << std::setw(12) << NPART_real.size() << " *" << std::endl;
	out << "%*"<< std::setw(40) << "Total number of FAKE impacts:" << std::setw(12) << NPART_fake.size() << " *" << std::endl;
	out << "%*"<< std::setw(40) << "Absorptions in the IR7 collimators:" << std::setw(12) << count_ir7 << " *" << std::endl;
	out << "%*"<< std::setw(40) << "Absorptions in the IR3 collimators:" << std::setw(12) << count_ir3 << " *" << std::endl;
	out << "%*******************************************************" << std::endl;
	out << std::setw(6) << "%Np" << std::setw(4) << "Ntu" << std::setw(12) << "Spos [ m ]" << std::endl;
	out.precision(10);

	for (size_t i = 0; i < NPART_real.size(); i++)
	{
		out << std::setw(6) << NPART_real[i]
			<< std::setw(4) << NTURN_real[i]
			<< std::setw(12) << POS_real[i] << std::endl;
	}
	out.close();

	// Write output file for FAKE impacts
	ost << "all_absorptions." << s1 << "." << halo << "." << EN << "." << optics << ".fake.dat";
	output = ost.str();
	ost.str("");
	std::cout << "Name of the FAKE impact file: \"" << output << "\"." << std::endl << std::endl;

	out.open(output.c_str());
	out << "%*******************************************************" << std::endl;
	out << "%*  Summary of partile absorptions in the collimators  *" << std::endl; 
	out << "%*******************************************************" << std::endl;
	out << "%*" << std::setw(40) << "Total number of SixTrack impacts:" << std::setw(12) << NPART.size() << " *" << std::endl;
	out << "%*" << std::setw(40) << "Total number of REAL impacts:" << std::setw(12) << NPART_real.size() << " *" << std::endl;
	out << "%*" << std::setw(40) << "Total number of FAKE impacts:" << std::setw(12) << NPART_fake.size() << " *" << std::endl;
	out << "%*" << std::setw(40) << "Absorptions in the IR7 collimators:" << std::setw(12) << count_ir7 << " *" << std::endl;
	out << "%*" << std::setw(40) << "Absorptions in the IR3 collimators:" << std::setw(12) << count_ir3 << " *" << std::endl;
	out << "%*******************************************************" << std::endl;
	out << std::setw(6) << "%Np" << std::setw(4) << "Ntu" << std::setw(12) << "Spos [ m ]" << std::endl;
	out.precision(10);

	for (size_t i = 0; i < NPART_fake.size(); i++)
	{
		out << std::setw(6) << NPART_fake[i]
			<< std::setw(4) << NTURN_fake[i]
			<< std::setw(12) << POS_fake[i] << std::endl;
	}
	out.close();

	// Clean up vectors for the next file
	NPART.clear();
	NTURN.clear();
	POS.clear();
	NPART_lost.clear();
	NTURN_lost.clear();
	POS_lost.clear();
	NPART_real.clear();
	NTURN_real.clear();
	POS_real.clear();
	NPART_fake.clear();
	NTURN_fake.clear();
	POS_fake.clear();

	return EXIT_SUCCESS;
}

