#include "Exponential.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"

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
}

