/*main.cpp*/

//
// Chicago Crime Analysis program in modern C++.
//
// <<Mission Marcus>>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 02
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "classes.h"

using namespace std;


int main()
{
	string  crimeCodesFilename, crimesFilename;

	cin >> crimeCodesFilename;
	cout << crimeCodesFilename << endl;

	cin >> crimesFilename;
	cout << crimesFilename << endl;

	ifstream  codesFile(crimeCodesFilename);
	ifstream  crimesFile(crimesFilename);

	cout << std::fixed;
	cout << std::setprecision(2);

	if (!codesFile.good())
	{
		cout << "**ERROR: cannot open crime codes file: '" << crimeCodesFilename << "'" << endl;
		return -1;
	}
	if (!crimesFile.good())
	{
		cout << "**ERROR: cannot open crimes file: '" << crimesFilename << "'" << endl;
		return -1;
	}

	std::vector<CrimeCode> crimesC; // our vector
	std::vector<CrimeReport> crimesR; // our report vector
	string line;
	string line2;

	int countCodes = 0; // this is to count how many codes we have..

	getline(codesFile, line);

	while (getline(codesFile, line))  // while we have lines.. 
	{
		stringstream ss(line);

		string code;
		string primary;
		string secondary;

		getline(ss, code, ',');
		getline(ss, primary, ',');
		getline(ss, secondary, ',');


		crimesC.push_back(CrimeCode(code, primary, secondary)); // push back a crimecode object
		countCodes++; // increment

	}

	getline(crimesFile, line2); // get rid of the first line.. 

	int countCrimes = 0; // use this to count the crimes.. 

	string firstDate;
	string secondDate;

	while (getline(crimesFile, line2))
	{
		stringstream ss(line2);


		if (countCrimes == 0) // if we're at the first date
		{
			getline(ss, firstDate, ','); // make it the first date
		}

		getline(ss, secondDate, ','); // at the end.. this will be the last date bound

		countCrimes++; // count up the crimes.
	}



	int countLine = 0; // make a new count line


	string line3;

	ifstream  crimesFile2(crimesFilename); // open another ifstream to re-read the file

	getline(crimesFile2, line3); // get rid of the first line


	std::sort(crimesC.begin(), crimesC.end(), [=](CrimeCode &crimes, CrimeCode &crimes2) // sort the crimes by crime code
	{
		if (crimes.getCode() > crimes2.getCode())
		{
			return false;
		}
		else
		{
			return true;
		}
	});




	while (getline(crimesFile2, line3)) // read in all crimes
	{
		stringstream ss(line3);

		string date;
		string code;
		string arrest;
		string domestic;
		string beat;
		string district;
		string ward;
		string community;

		getline(ss, date, ',');
		getline(ss, code, ',');
		getline(ss, arrest, ',');
		getline(ss, domestic, ',');
		getline(ss, beat, ',');
		getline(ss, district, ',');
		getline(ss, ward, ',');
		getline(ss, community, ',');


		auto iterator = std::find_if(crimesC.begin(), crimesC.end(), [=](CrimeCode &c)
		{
			if (c.getCode() == code)
			{
				c.increment();
				return true;
			}
			else
			{
				return false;
			}
		}); // im using this to find_if we have a crime and then increment that crime.


		int dis = stoi(district);
		int bea = stoi(beat);
		int wa = stoi(ward);
		int comm = stoi(community);

		crimesR.push_back(CrimeReport(date, code, arrest, domestic, bea, dis, wa, comm));

		countLine++; // increment lines counted


	}

	cout << "** Crime Analysis **" << endl; // print this out
	cout << "\n";
	cout << "Date range: " << firstDate << " - " << secondDate << endl;
	cout << "\n# of crime codes: " << countCodes << endl;


	crimesC[0].printInfo(); // print first 3 crimes
	crimesC[1].printInfo();
	crimesC[2].printInfo();

	cout << "..."; // print ...
	cout << "\n";

	crimesC[countCodes - 3].printInfo(); // print last 3 crimes
	crimesC[countCodes - 2].printInfo();
	crimesC[countCodes - 1].printInfo();

	cout << "\n"; // print out number of crimes
	cout << "# of crimes: " << countCrimes << endl;

	crimesR[0].printInfo3();
	crimesR[1].printInfo3();
	crimesR[2].printInfo3();


	cout << "..."; // print...
	cout << "\n";

	crimesR[countLine - 3].printInfo3();
	crimesR[countLine - 2].printInfo3();
	crimesR[countLine - 1].printInfo3();



	cout << "\n** Top-5 Crimes **" << endl; // print this
	cout << "Code:\t" << "Total, Description" << endl;



	std::sort(crimesC.begin(), crimesC.end(), [=](const CrimeCode &crimes, const CrimeCode &crimes2) // sort by number of currences within crimes
	{
		if (crimes.getOccurrences() > crimes2.getOccurrences())
		{
			return true;
		}
		else
		{
			return false;
		}
	});

	for (int x = 0; x < 5; x++) // print the top 5.
	{
		crimesC[x].printInfo2();
	}


	cout << "\n** Done **";


	return 0; // return
}

