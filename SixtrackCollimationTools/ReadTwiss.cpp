#include "ReadTwiss.h"

double ReadTwiss(string in, vector<string> *K, vector<string> *N, 
		 vector<string> *Pa, vector<string> *Kn, vector<string> *Nn, 
		 vector<string> *Pan, vector<double> *P, vector<double> *L, 
		 vector<double> *A1, vector<double> *A2, vector<double> *A3, 
		 vector<double> *A4, vector<ApertureClass_t> *ApertureType)

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
	string str_tmp;

	int len;
	ostringstream ost;

	ifstream InputFile(in.c_str());

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != string::npos)
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
		A1->push_back(atof(tA1));
		A2->push_back(atof(tA2));
		A3->push_back(atof(tA3));
		A4->push_back(atof(tA4));
		ApertureType->push_back(GetApertureType(ApType));

		// Element names without quotes
		ost.str("");
		len=(int)strlen(tK);

		for (int i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tN);

		for (int i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tT);

		for (int i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());

	}
	InputFile.close();

	cout << endl;
	cout << "Reading from \"" << in << "\"" << endl;
	cout << "Total number of read elements: " << K->size() << endl;
	cout << endl;

	return AcceleratorLength;
}

double ReadTwissNoDrifts(string in, vector<string> *K, vector<string> *N, 
			 vector<string> *Pa, vector<string> *Kn, vector<string> *Nn, 
			 vector<string> *Pan, vector<double> *P, vector<double> *L, 
			 vector<double> *A1, vector<double> *A2, vector<double> *A3, 
			 vector<double> *A4, vector<ApertureClass_t> *ApertureType)

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
	string str_tmp;

	int len;
	ostringstream ost;

	ifstream InputFile(in.c_str());

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}

	while (InputFile.getline(chr_tmp,256))
	{
		sscanf(chr_tmp,"%s%s%s%s%s%s%s%s%s%s",tK,tN,tT,tP,tL,tA1,tA2,tA3,tA4,ApType);

		str_tmp = tK;

		if ( str_tmp.find("DRIFT",0) == string::npos )
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
			ApertureType->push_back(GetApertureType(ApType));
		}
 
		// Element names without quotes
		ost.str("");
		len=(int)strlen(tK);

		for (int i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tN);

		for (int i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tT);

		for (int i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());

	}
	InputFile.close();

	cout << endl;
	cout << "Reading from \"" << in << "\"" << endl;
	cout << "Total number of read elements: " << K->size() << endl;
	cout << endl;

	return AcceleratorLength;
}


double ReadTwissK(string in, vector<string> *K, vector<string> *N, 
		vector<string> *Pa, vector<string> *Kn, vector<string> *Nn, 
		vector<string> *Pan, vector<double> *P, vector<double> *L, 
		vector<double> *KL, vector<double> *A1, vector<double> *A2, 
		vector<double> *A3, vector<double> *A4, vector<ApertureClass_t> *ApertureType)
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
	string str_tmp;

	int len;
	ostringstream ost;

	ifstream InputFile(in.c_str());

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != string::npos)
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
		A1->push_back(atof(tA1));
		A2->push_back(atof(tA2));
		A3->push_back(atof(tA3));
		A4->push_back(atof(tA4));
		ApertureType->push_back(GetApertureType(ApType));
 
		// Element names without quotes
		ost.str("");
		len=(int)strlen(tK);

		for (int i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tN);

		for (int i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tT);

		for (int i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());

	}
	InputFile.close();

	cout << endl;
	cout << "Reading from \"" << in << "\"" << endl;
	cout << "Total number of read elements: " << K->size() << endl;
	cout << endl;

	return AcceleratorLength;
}

double ReadTwissDX(string in, vector<string> *K, vector<string> *N, vector<string> *Pa, 
		 vector<string> *Kn, vector<string> *Nn, vector<string> *Pan, 
		 vector<double> *P, vector<double> *L, vector<double> *A1, 
		 vector<double> *A2, vector<double> *A3, vector<double> *A4, 
		 vector<double> *DX, vector<double> *DY, vector<ApertureClass_t> *ApertureType)
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
	string str_tmp;

	int len;
	ostringstream ost;

	ifstream InputFile(in.c_str());

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != string::npos)
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
		A1->push_back(atof(tA1));
		A2->push_back(atof(tA2));
		A3->push_back(atof(tA3));
		A4->push_back(atof(tA4));
		DX->push_back(atof(tDX));
		DY->push_back(atof(tDY));
		ApertureType->push_back(GetApertureType(ApType));

		// Element names without quotes
		ost.str("");
		len=(int)strlen(tK);

		for (int i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tN);

		for (int i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tT);

		for (int i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());

	}
	InputFile.close();

	cout << endl;
	cout << "Reading from \"" << in << "\"" << endl;
	cout << "Total number of read elements: " << K->size() << endl;
	cout << endl;

	return AcceleratorLength;
}

double ReadTwissDXNoDrifts(string in, vector<string> *K, vector<string> *N, vector<string> *Pa, 
			 vector<string> *Kn, vector<string> *Nn, vector<string> *Pan, 
			 vector<double> *P, vector<double> *L, vector<double> *A1, 
			 vector<double> *A2, vector<double> *A3, vector<double> *A4, 
			 vector<double> *DX, vector<double> *DY, vector<ApertureClass_t> *ApertureType)
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
	string str_tmp;

	int len;
	ostringstream ost;

	ifstream InputFile(in.c_str());

	//First try and pull out the accelerator length variable
	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("@ LENGTH",0) != string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}
	//Ugly, but gets the job done
	string AcceleratorLengthString = str_tmp.substr(str_tmp.rfind(" ")+1,str_tmp.length()-str_tmp.rfind(" ")).c_str();
	AcceleratorLength = atof(AcceleratorLengthString.c_str());

	while (InputFile.getline(chr_tmp,256))
	{
		str_tmp = chr_tmp;

		if (str_tmp.find("KEYWORD",0) != string::npos)
		{
			InputFile.getline(chr_tmp,256);
			break;
		}
	}

	while (InputFile.getline(chr_tmp,256))
	{
		sscanf(chr_tmp,"%s%s%s%s%s%s%s%s%s%s%s%s",tK,tN,tT,tP,tL,tA1,tA2,tA3,tA4,tDX,tDY,ApType);

		str_tmp = tK;

		if ( str_tmp.find("DRIFT",0) == string::npos )
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
			ApertureType->push_back(GetApertureType(ApType));
		}

		// Element names without quotes
		ost.str("");
		len=(int)strlen(tK);

		for (int i = 1; i < len-1; i++)
		{
			ost << tK[i];
		}

		Kn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tN);

		for (int i = 1; i < len-1; i++)
		{
			ost << tN[i];
		}

		Nn->push_back(ost.str());
		ost.str("");
		len=(int)strlen(tT);

		for (int i = 1; i < len-1; i++)
		{
			ost << tT[i];
		}

		Pan->push_back(ost.str());
	}
	InputFile.close();

	cout << endl;
	cout << "Reading from \"" << in << "\"" << endl;
	cout << "Total number of read elements: " << K->size() << endl;
	cout << endl;

	return AcceleratorLength;
}

ApertureClass_t GetApertureType(char* ApType)
{
	string ApTemp = ApType;
	if(ApTemp == "\"CIRCLE\"")
	{
		return CIRCLE;
	}
	else if(ApTemp == "\"RECTANGLE\"")
	{
		return RECTANGLE;
	}
	else if(ApTemp == "\"ELLIPSE\"")
	{
		return ELLIPSE;
	}
	else if(ApTemp == "\"RECTCIRCLE\"")
	{
		return RECTCIRCLE;
	}
	else if(ApTemp == "\"LHCSCREEN\"")
	{
		return LHCSCREEN;
	}
	else if(ApTemp == "\"RECTELLIPSE\"")
	{
		return RECTELLIPSE;
	}
	else if(ApTemp == "\"RACETRACK\"")
	{
		return RACETRACK;
	}
	else if(ApTemp == "\"OCTAGON\"")
	{
		return OCTAGON;
	}
	else
	{
		return UNKNOWN;
	}
}
