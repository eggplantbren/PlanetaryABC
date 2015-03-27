#include <iostream>
#include "Start.h"
#include "MyModel.h"
#include "Data.h"
#include "Distributions/Dirichlet.h"

using namespace std;
using namespace DNest3;

int main(int argc, char** argv)
{
	Data::get_instance().load("counts.txt");

	MTSampler< MyModel<Dirichlet> > sampler
			= setup_mt< MyModel<Dirichlet> >(argc, argv);
	sampler.run();


	return 0;
}

