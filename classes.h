/*classes.h*/

//
// Classes for use with Chicago Crime Analysis program, e.g. "CrimeReport" 
// and "CrimeCode".
//
// << Mission Marcus >>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 02
//

#pragma once

#include <iostream>
#include <string>

using namespace std;


class CrimeCode
{
private: // all our private variables
	string code;
	string primary;
	string secondary;
	int occurrences;

public:

	CrimeCode(string c, string p, string s)
	{
		code = c;
		primary = p;
		secondary = s;
		occurrences = 0;
	}

	string getCode() const
	{
		return code;
	}

	string getPrimary() const
	{
		return primary;
	}

	string getSecondary() const
	{
		return secondary;
	}

	void increment() // increment up occurrences
	{
		occurrences = occurrences + 1;
	}

	int getOccurrences() const // return occurrences
	{
		return occurrences;
	}

	void printInfo() // print crimes first way
	{
		cout << code << ":\t" << primary << ":" << secondary << endl;
	}

	void printInfo2() // print crimes the second way
	{
		cout << code << ":\t" << occurrences << ", " << primary << ": " << secondary << endl;
	}


};

class CrimeReport // crime report class
{
private:
	string dateTime;
	string code;
	string arrest;
	string domestic;
	int beat;
	int district;
	int ward;
	int community;
	int year;

public:

	CrimeReport(string d, string c, string a, string dom, int be, int dis, int wa, int comy)
	{
		dateTime = d;
		code = c;
		arrest = a;
		domestic = dom;
		beat = be;
		district = dis;
		ward = wa;
		community = comy;

	}

	void printInfo3()
	{
		cout << code << ":\t" << dateTime << ", " << beat << ", " << district << ", " << ward << ", " << community;

		if (arrest == "true" || arrest == "TRUE")
		{
			cout << ", arrested";
		}

		if (domestic == "true" || domestic == "TRUE")
		{
			cout << ", domestic violence";
		}

		cout << endl;
	}

};

