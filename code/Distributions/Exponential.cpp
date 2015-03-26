#include "Exponential.h"
#include "RandomNumberGenerator.h"

using namespace DNest3;

Exponential::Exponential()
{

}

void Exponential::fromPrior()
{
	mu = 10.*randomU();
}

