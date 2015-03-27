#include "Dirichlet.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

using namespace std;
using namespace DNest3;

Dirichlet::Dirichlet(int num_possibilities)
:u(num_possibilities)
,probs(num_possibilities)
{

}

void Dirichlet::fromPrior()
{
	for(size_t i=0; i<u.size(); i++)
		u[i] = randomU();
	compute_probs();
}

double Dirichlet::perturb()
{
	int which = randInt(u.size());
	u[which] += randh();
	wrap(u[which], 0., 1.);

	compute_probs();
	return 0.;
}

void Dirichlet::compute_probs()
{
	double tot = 0.;
	for(size_t i=0; i<probs.size(); i++)
	{
		probs[i] = -log(1. - u[i]);
		tot += probs[i];
	}

	// Normalise
	for(size_t i=0; i<probs.size(); i++)
		probs[i] /= tot;
}

int Dirichlet::generate(double u) const
{
	double cumulative_prob = 0.;
	for(size_t i=0; i<probs.size(); i++)
	{
		cumulative_prob += probs[i];
		if(u <= cumulative_prob)
			return static_cast<int>(i);
	}
	return static_cast<int>(probs.size());
}

