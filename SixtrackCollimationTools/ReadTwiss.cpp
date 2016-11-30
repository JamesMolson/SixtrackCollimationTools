#include "ReadTwiss.h"
#include "string.h"

double ReadTwiss(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, 
		 std::vector<std::string> *Pa, std::vector<std::string> *Kn, std::vector<std::string> *Nn, 
		 std::vector<std::string> *Pan, std::vector<double> *P, std::vector<double> *L, 
		 std::vector<double> *A1, std::vector<double> *A2, std::vector<double> *A3, 
		 std::vector<double> *A4, std::vector<ApertureClass_t> *ApertureType)

{
	K->clear();
	N->clear();
	Pa->clear();
	P->clear();
	L->clear();
	A1->clear();
	A2->clear();
	A3->clear();
	A4->clear();
	ApertureType->clear();

	double AcceleratorLength = 0;
	char tK[256], tN[256], tT[256], tP[256], tL[256], tA1[256], tA2[256], tA3[256], tA4[256];
	char ApType[256];

	char chr_tmp[256];
	std::string str_tmp;

	size_t len;
	std::ostringstream ost;

	std::ifstream InputFile(in.c_str());

	if(!InputFile.good())
	{
		std::cerr << "Could not open input aperture file: " << in << std::endl;
		std::cerr << "Exiting" << std::endl;
		exit(EXIT_FAILURE);
	}

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	std::string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}

	while (InputFile.getline(chr_tmp,256))
	{
		sscanf(chr_tmp,"%s%s%s%s%s%s%s%s%s%s",tK,tN,tT,tP,tL,tA1,tA2,tA3,tA4,ApType);

		K->push_back(tK);
		N->push_back(tN);
		Pa->push_back(tT);
		P->push_back(atof(tP));
		L->push_back(atof(tL));

		//If we are in a circular aperture, A2,A3,A4 will be zero.
		//Set all of these to the A1 value (radius) to make interpolation easier
		if(GetApertureTypeClass(ApType) == CIRCLE)
		{
			A1->push_back(atof(tA1));
			A2->push_back(atof(tA1));
			A3->push_back(atof(tA1));
			A4->push_back(atof(tA1));
		}
		else
		{
			A1->push_back(atof(tA1));
			A2->push_back(atof(tA2));
			A3->push_back(atof(tA3));
			A4->push_back(atof(tA4));
		}

		ApertureType->push_back(GetApertureTypeClass(ApType));

		// Element names without quotes
		ost.str("");
		len=strlen(tK);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=strlen(tN);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=strlen(tT);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());

	}
	InputFile.close();

	std::cout << std::endl;
	std::cout << "Reading from \"" << in << "\"" << std::endl;
	std::cout << "Total number of read elements: " << K->size() << std::endl;
	std::cout << std::endl;

	return AcceleratorLength;
}

double ReadTwissNoDrifts(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, 
			 std::vector<std::string> *Pa, std::vector<std::string> *Kn, std::vector<std::string> *Nn, 
			 std::vector<std::string> *Pan, std::vector<double> *P, std::vector<double> *L, 
			 std::vector<double> *A1, std::vector<double> *A2, std::vector<double> *A3, 
			 std::vector<double> *A4, std::vector<ApertureClass_t> *ApertureType)

{
	K->clear();
	N->clear();
	Pa->clear();
	P->clear();
	L->clear();
	A1->clear();
	A2->clear();
	A3->clear();
	A4->clear();
	ApertureType->clear();

	double AcceleratorLength = 0;
	char tK[256], tN[256], tT[256], tP[256], tL[256], tA1[256], tA2[256], tA3[256], tA4[256];
	char ApType[256];

	char chr_tmp[256];
	std::string str_tmp;

	size_t len;
	std::ostringstream ost;

	std::ifstream InputFile(in.c_str());

	if(!InputFile.good())
	{
		std::cerr << "Could not open input aperture file: " << in << std::endl;
		std::cerr << "Exiting" << std::endl;
		exit(EXIT_FAILURE);
	}

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	std::string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}

	while (InputFile.getline(chr_tmp,256))
	{
		sscanf(chr_tmp,"%s%s%s%s%s%s%s%s%s%s",tK,tN,tT,tP,tL,tA1,tA2,tA3,tA4,ApType);
		str_tmp = tK;

		if ( str_tmp.find("DRIFT",0) == std::string::npos )
		{
			K->push_back(tK);
			N->push_back(tN);
			Pa->push_back(tT);
			P->push_back(atof(tP));
			L->push_back(atof(tL));

			//If we are in a circular aperture, A2,A3,A4 will be zero.
			//Set all of these to the A1 value (radius) to make interpolation easier
			if(GetApertureTypeClass(ApType) == CIRCLE)
			{
				A1->push_back(atof(tA1));
				A2->push_back(atof(tA1));
				A3->push_back(atof(tA1));
				A4->push_back(atof(tA1));
			}
			else
			{
				A1->push_back(atof(tA1));
				A2->push_back(atof(tA2));
				A3->push_back(atof(tA3));
				A4->push_back(atof(tA4));
			}

			ApertureType->push_back(GetApertureTypeClass(ApType));

		}
 
		// Element names without quotes
		ost.str("");
		len=strlen(tK);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=strlen(tN);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=strlen(tT);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());

	}
	InputFile.close();

	std::cout << std::endl;
	std::cout << "Reading from \"" << in << "\"" << std::endl;
	std::cout << "Total number of read elements: " << K->size() << std::endl;
	std::cout << std::endl;

	return AcceleratorLength;
}


double ReadTwissK(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, 
		std::vector<std::string> *Pa, std::vector<std::string> *Kn, std::vector<std::string> *Nn, 
		std::vector<std::string> *Pan, std::vector<double> *P, std::vector<double> *L, 
		std::vector<double> *KL, std::vector<double> *A1, std::vector<double> *A2, 
		std::vector<double> *A3, std::vector<double> *A4, std::vector<ApertureClass_t> *ApertureType)
{
	K->clear();
	N->clear();
	Pa->clear();
	P->clear();
	L->clear();
	KL->clear();
	A1->clear();
	A2->clear();
	A3->clear();
	A4->clear();
	ApertureType->clear();

	double AcceleratorLength = 0;
	char tK[256], tN[256], tT[256], tP[256], tL[256], tKL[256], tA1[256], tA2[256], tA3[256], tA4[256];
	char ApType[256];

	char chr_tmp[256];
	std::string str_tmp;

	size_t len;
	std::ostringstream ost;

	std::ifstream InputFile(in.c_str());

	if(!InputFile.good())
	{
		std::cerr << "Could not open input aperture file: " << in << std::endl;
		std::cerr << "Exiting" << std::endl;
		exit(EXIT_FAILURE);
	}

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	std::string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}

	while (InputFile.getline(chr_tmp,256))
	{
		sscanf(chr_tmp,"%s%s%s%s%s%s%s%s%s%s%s",tK,tN,tT,tP,tL,tKL,tA1,tA2,tA3,tA4,ApType);

		K->push_back(tK);
		N->push_back(tN);
		Pa->push_back(tT);
		P->push_back(atof(tP));
		L->push_back(atof(tL));
		KL->push_back(atof(tKL));

		//If we are in a circular aperture, A2,A3,A4 will be zero.
		//Set all of these to the A1 value (radius) to make interpolation easier
		if(GetApertureTypeClass(ApType) == CIRCLE)
		{
			A1->push_back(atof(tA1));
			A2->push_back(atof(tA1));
			A3->push_back(atof(tA1));
			A4->push_back(atof(tA1));
		}
		else
		{
			A1->push_back(atof(tA1));
			A2->push_back(atof(tA2));
			A3->push_back(atof(tA3));
			A4->push_back(atof(tA4));
		}

		ApertureType->push_back(GetApertureTypeClass(ApType));
 
		// Element names without quotes
		ost.str("");
		len=strlen(tK);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=strlen(tN);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=strlen(tT);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());

	}
	InputFile.close();

	std::cout << std::endl;
	std::cout << "Reading from \"" << in << "\"" << std::endl;
	std::cout << "Total number of read elements: " << K->size() << std::endl;
	std::cout << std::endl;

	return AcceleratorLength;
}

double ReadTwissDX(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, std::vector<std::string> *Pa, 
		 std::vector<std::string> *Kn, std::vector<std::string> *Nn, std::vector<std::string> *Pan, 
		 std::vector<double> *P, std::vector<double> *L, std::vector<double> *A1, 
		 std::vector<double> *A2, std::vector<double> *A3, std::vector<double> *A4, 
		 std::vector<double> *DX, std::vector<double> *DY, std::vector<ApertureClass_t> *ApertureType)
{
	K->clear();
	N->clear();
	Pa->clear();
	P->clear();
	L->clear();
	A1->clear();
	A2->clear();
	A3->clear();
	A4->clear();
	DX->clear();
	DY->clear();
	ApertureType->clear();

	double AcceleratorLength = 0;
	char tK[256], tN[256], tT[256], tP[256], tL[256], tA1[256], tA2[256], tA3[256], tA4[256], tDX[256], tDY[256];
	char ApType[256];

	char chr_tmp[256];
	std::string str_tmp;

	size_t len;
	std::ostringstream ost;

	std::ifstream InputFile(in.c_str());

	if(!InputFile.good())
	{
		std::cerr << "Could not open input aperture file: " << in << std::endl;
		std::cerr << "Exiting" << std::endl;
		exit(EXIT_FAILURE);
	}

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	std::string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}

	while (InputFile.getline(chr_tmp,256))
	{
		sscanf(chr_tmp,"%s%s%s%s%s%s%s%s%s%s%s%s",tK,tN,tT,tP,tL,tA1,tA2,tA3,tA4,tDX,tDY,ApType);

		str_tmp = tK;
		K->push_back(tK);
		N->push_back(tN);
		Pa->push_back(tT);
		P->push_back(atof(tP));
		L->push_back(atof(tL));
		DX->push_back(atof(tDX));
		DY->push_back(atof(tDY));

		//If we are in a circular aperture, A2,A3,A4 will be zero.
		//Set all of these to the A1 value (radius) to make interpolation easier
		if(GetApertureTypeClass(ApType) == CIRCLE)
		{
			A1->push_back(atof(tA1));
			A2->push_back(atof(tA1));
			A3->push_back(atof(tA1));
			A4->push_back(atof(tA1));
		}
		else
		{
			A1->push_back(atof(tA1));
			A2->push_back(atof(tA2));
			A3->push_back(atof(tA3));
			A4->push_back(atof(tA4));
		}

		ApertureType->push_back(GetApertureTypeClass(ApType));

		// Element names without quotes
		ost.str("");
		len=strlen(tK);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=strlen(tN);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=strlen(tT);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());

	}
	InputFile.close();

	std::cout << std::endl;
	std::cout << "Reading from \"" << in << "\"" << std::endl;
	std::cout << "Total number of read elements: " << K->size() << std::endl;
	std::cout << std::endl;

	return AcceleratorLength;
}

double ReadTwissDXNoDrifts(std::string in, std::vector<std::string> *K, std::vector<std::string> *N, std::vector<std::string> *Pa, 
			 std::vector<std::string> *Kn, std::vector<std::string> *Nn, std::vector<std::string> *Pan, 
			 std::vector<double> *P, std::vector<double> *L, std::vector<double> *A1, 
			 std::vector<double> *A2, std::vector<double> *A3, std::vector<double> *A4, 
			 std::vector<double> *DX, std::vector<double> *DY, std::vector<ApertureClass_t> *ApertureType)
{
	K->clear();
	N->clear();
	Pa->clear();
	P->clear();
	L->clear();
	A1->clear();
	A2->clear();
	A3->clear();
	A4->clear();
	DX->clear();
	DY->clear();
	ApertureType->clear();

	double AcceleratorLength = 0;
	char tK[256], tN[256], tT[256], tP[256], tL[256], tA1[256], tA2[256], tA3[256], tA4[256], tDX[256], tDY[256];
	char ApType[256];

	char chr_tmp[256];
	std::string str_tmp;

	size_t len;
	std::ostringstream ost;

	std::ifstream InputFile(in.c_str());

	if(!InputFile.good())
	{
		std::cerr << "Could not open input aperture file: " << in << std::endl;
		std::cerr << "Exiting" << std::endl;
		exit(EXIT_FAILURE);
	}

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	std::string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != std::string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}

	while (InputFile.getline(chr_tmp,256))
	{
		sscanf(chr_tmp,"%s%s%s%s%s%s%s%s%s%s%s%s",tK,tN,tT,tP,tL,tA1,tA2,tA3,tA4,tDX,tDY,ApType);

		str_tmp = tK;

		if ( str_tmp.find("DRIFT",0) == std::string::npos )
		{
			K->push_back(tK);
			N->push_back(tN);
			Pa->push_back(tT);
			P->push_back(atof(tP));
			L->push_back(atof(tL));
			A1->push_back(atof(tA1));
			A2->push_back(atof(tA2));
			A3->push_back(atof(tA3));
			A4->push_back(atof(tA4));
			DX->push_back(atof(tDX));
			DY->push_back(atof(tDY));
			ApertureType->push_back(GetApertureTypeClass(ApType));
		}

		// Element names without quotes
		ost.str("");
		len=strlen(tK);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=strlen(tN);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=strlen(tT);

		for (size_t i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());
	}
	InputFile.close();

	std::cout << std::endl;
	std::cout << "Reading from \"" << in << "\"" << std::endl;
	std::cout << "Total number of read elements: " << K->size() << std::endl;
	std::cout << std::endl;

	return AcceleratorLength;
}

