#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

template<class Distribution>
MyModel<Distribution>::MyModel()
:K_max(Data::get_instance().get_counts().size() - 1)
,dist(K_max+1)
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
		thickness += 0.5*M_PI*randh();
		wrap(thickness, 0., 0.5*M_PI);
	}

	return logH;
}

template<class Distribution>
vector<int> MyModel<Distribution>::compute_hist() const
{
	// Newton's constant in $R_\odot^3 M_\odot^{-1} {days}^{-2}$.
	double _G = 2945.4625385377644;

	const vector<int> counts = Data::get_instance().get_counts();
	vector<int> hist(counts.size(), 0);

	int K, num_observed;
	double inclination, a, period, b;
	double stellar_mass = 1.;
	double stellar_radius = 1.;
//	cout<<"Thickness = "<<thickness<<endl;

	// Loop over all stars
	for(size_t i=0; i<u_K.size(); i++)
	{
//		cout<<"# Star "<<(i+1)<<": "<<endl;
		K = dist.generate(u_K[i]);
		num_observed = 0;

//		cout<<"Number of planets = "<<K<<"."<<endl;
//		cout<<"Inclination of star: "<<acos(u_A[i])<<endl;
//		cout<<"(inclination, period, a, b, observed)"<<endl;

		// Loop over all planets around this star
		for(int j=0; j<K; j++)
		{
			inclination = acos(u_A[i])
						+ thickness*(u_dI[i][j] - 0.5);
			period = exp(log(5.) + log(100.)*u_P[i][j]);
			a = pow((_G*period*period*stellar_mass)/(4.*M_PI*M_PI), 1./3);
			b = a*cos(inclination)/stellar_radius;
//			cout<<inclination<<' '<<period<<' '<<a<<' '<<b<<' '<<(fabs(b) < 1)<<endl;

			if(fabs(b) < 1)
			{
				// Planet was observed
				num_observed++;
			}
		}
		hist[num_observed]++;
	}
//	cout<<"Histogram: ";
//	for(size_t i=0; i<hist.size(); i++)
//		cout<<hist[i]<<' ';
//	cout<<endl;
//	exit(0);

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
	out<<thickness<<' ';

	vector<double> probs = dist.get_probs();
	for(size_t i=0; i<probs.size(); i++)
		out<<probs[i]<<' ';

	vector<int> hist = compute_hist();
	for(size_t i=0; i<hist.size(); i++)
		out<<hist[i]<<' ';
}

template<class Distribution>
string MyModel<Distribution>::description() const
{
	return string("");
}

