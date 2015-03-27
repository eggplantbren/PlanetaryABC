#ifndef _Dirichlet_
#define _Dirichlet_

#include <vector>

class Dirichlet
{
	private:
		std::vector<double> u;
		std::vector<double> probs;

		void compute_probs();

	public:
		Dirichlet(int num_possibilities);
		void fromPrior();
		double perturb();

		// Draw from the Dirichlet distribution using the
		// u (with U(0,1) prior) as input
		int generate(double u) const;

		const std::vector<double>& get_probs() const
		{ return probs; }
};

#endif


