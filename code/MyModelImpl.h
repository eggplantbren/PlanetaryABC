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
,u_A(Data::get_instance().get_total())
,u_R(Data::get_instance().get_total(), vector<double>(K_max))
,u_P(Data::get_instance().get_total(), vector<double>(K_max))
,u_dI(Data::get_instance().get_total(), vector<double>(K_max))
{

}

template<class Distribution>
void MyModel<Distribution>::fromPrior()
{
	dist.fromPrior();

	for(size_t i=0; i<u_K.size(); i++)
	{
		u_K[i] = randomU();
		u_A[i] = randomU();
		for(int j=0; j<K_max; j++)
		{
			u_R[i][j] = randomU();
			u_P[i][j] = randomU();
			u_dI[i][j] = randomU();
		}
	}

	thickness = 0.5*M_PI*randomU();
}

template<class Distribution>
double MyModel<Distribution>::perturb_u_K()
{
	vector<double>* which;
	if(randomU() <= 0.5)
		which = &(u_K);
	else
		which = &(u_A);

	int i;
	int reps = static_cast<int>(floor(pow(10., 3.*randomU())));

	for(int k=0; k<reps; k++)
	{
		i = randInt(which->size());
		(*which)[i] = randomU();
	}

	return 0.;
}


template<class Distribution>
double MyModel<Distribution>::perturb_u_R()
{
	vector< vector<double> >* which;
	if(randomU() <= 0.33333)
		which = &(u_R);
	else if(randomU() <= 0.5)
		which = &(u_P);
	else
		which = &(u_dI);

	int i, j;
	int reps = static_cast<int>(floor(pow(10., 3.*randomU())));

	for(int k=0; k<reps; k++)
	{
		i = randInt(which->size());
		j = randInt((*which)[i].size());
		(*which)[i][j] = randomU();
	}

	return 0.;
}


template<class Distribution>
double MyModel<Distribution>::perturb()
{
	double logH = 0.;

	int which = randInt(4);

	if(which == 0)
		logH += dist.perturb();
	else if(which == 1)
		logH += perturb_u_K();
	else if(which == 2)
		logH += perturb_u_R();
	else
	{
		thickness += 0.5*M_PIrandh();
		wrap(thickness, 0., 0.5*M_PI);
	}

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
	vector<int> hist = compute_hist();
	for(size_t i=0; i<hist.size(); i++)
		out<<hist[i]<<' ';
}

template<class Distribution>
string MyModel<Distribution>::description() const
{
	return string("");
}

