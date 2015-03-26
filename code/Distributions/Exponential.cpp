#include "Exponential.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"

using namespace DNest3;

Exponential::Exponential()
{

}

void Exponential::fromPrior()
{
	mu = 10.*randomU();
}

double Exponential::perturb()
{
	mu += 10.*randh();
	wrap(mu, 0., 10.);
	return 0.;
}

