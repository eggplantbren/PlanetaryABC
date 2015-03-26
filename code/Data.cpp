#include "Data.h"
#include <fstream>
#include <iostream>

using namespace std;

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

	K_max = counts.size();
	cout<<"# K_max = "<<K_max<<endl;

	fin.close();
}

