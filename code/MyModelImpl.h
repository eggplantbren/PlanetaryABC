#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

template<class Distribution>
MyModel<Distribution>::MyModel()
:dist(K_max+1)
,u_K(Data::get_instance().get_total())
{

}

template<class Distribution>
void MyModel<Distribution>::fromPrior()
{
	dist.fromPrior();

	for(size_t i=0; i<u_K.size(); i++)
		u_K[i] = randomU();
}

template<class Distribution>
double MyModel<Distribution>::perturb_u_K()
{
	int i;
	int reps = static_cast<int>(floor(pow(10., 3.*randomU())));

	for(int k=0; k<reps; k++)
	{
		i = randInt(u_K.size());
		u_K[i] = randomU();
	}

	return 0.;
}

template<class Distribution>
double MyModel<Distribution>::perturb()
{
	double logH = 0.;

	int which = randInt(2);

	if(which == 0)
		logH += perturb_u_K();
	else
		logH += dist.perturb();

	return logH;
}

template<class Distribution>
vector<int> MyModel<Distribution>::compute_hist() const
{
	const vector<int> counts = Data::get_instance().get_counts();
	vector<int> hist(counts.size(), 0);

	int K;
	for(size_t i=0; i<u_K.size(); i++)
	{
		K = dist.generate(u_K[i]);
		if(K < static_cast<int>(hist.size()))
			hist[K]++;
	}

	return hist;
}

template<class Distribution>
double MyModel<Distribution>::logLikelihood() const
{
	double logL = 0.;

	const vector<int> counts = Data::get_instance().get_counts();
	vector<int> hist = compute_hist();

	for(size_t i=0; i<counts.size(); i++)
		logL += pow((double)(hist[i] - counts[i]), 2);
	logL = -logL;

	return logL;
}

template<class Distribution>
void MyModel<Distribution>::print(std::ostream& out) const
{
	out<<"";
}

template<class Distribution>
string MyModel<Distribution>::description() const
{
	return string("");
}

