#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:u_K(Data::get_instance().get_total(), vector<double>(K_max))
{

}

void MyModel::fromPrior()
{
	for(size_t i=0; i<u_K.size(); i++)
		for(size_t j=0; j<u_K[i].size(); j++)
			u_K[i][j] = randomU();
}

double MyModel::perturb_u_K()
{
	int i, j;
	int reps = static_cast<int>(floor(pow(10., 3.*randomU())));

	for(int k=0; k<reps; k++)
	{
		i = randInt(u_K.size());
		j = randInt(u_K[i].size());
		u_K[i][j] = randomU();
	}

	return 0.;
}

double MyModel::perturb()
{
	double logH = 0.;

	logH += perturb_u_K();

	return logH;
}

double MyModel::logLikelihood() const
{
	return 0.;
}

void MyModel::print(std::ostream& out) const
{

}

string MyModel::description() const
{
	return string("");
}

