#include "Exponential.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>

using namespace DNest3;

Exponential::Exponential(int K_max)
:probs(K_max)
{

}

void Exponential::fromPrior()
{
	mu = 10.*randomU();
	compute_probs();
}

double Exponential::perturb()
{
	mu += 10.*randh();
	wrap(mu, 0., 10.);
	compute_probs();
	return 0.;
}

void Exponential::compute_probs()
{
	double tot = 0.;
	for(size_t i=0; i<probs.size(); i++)
	{
		probs[i] = exp(-(double)i/mu);
		tot += probs[i];
	}

	// Normalise
	for(size_t i=0; i<probs.size(); i++)
		probs[i] /= tot;
}

