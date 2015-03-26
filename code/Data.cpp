#include "Data.h"
#include <fstream>
#include <iostream>

using namespace std;

Data Data::instance;

Data::Data()
{

}

void Data::load(const char* filename)
{
	// Open the file
	fstream fin(filename, ios::in);
	int temp;

	// Clear the data
	counts.clear();
	while(fin>>temp)
		counts.push_back(temp);

	fin.close();
}

