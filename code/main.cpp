#include <iostream>
#include "Start.h"
#include "MyModel.h"
#include "Data.h"
#include "Distributions/Exponential.h"

using namespace std;
using namespace DNest3;

int main(int argc, char** argv)
{
	Data::get_instance().load("temp.txt");

	MTSampler< MyModel<Exponential> > sampler
			= setup_mt< MyModel<Exponential> >(argc, argv);
	sampler.run();


	return 0;
}

