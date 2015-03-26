#ifndef _Exponential_
#define _Exponential_

#include <vector>

class Exponential
{
	private:
		double mu;
		std::vector<double> probs;

		void compute_probs();

	public:
		Exponential(int K_max);
		void fromPrior();
		double perturb();

		// Draw from the Exponential distribution using the
		// u (with U(0,1) prior) as input
		int generate(double u) const;
};

#endif


