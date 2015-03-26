#ifndef _Exponential_
#define _Exponential_

class Exponential
{
	private:
		double mu;

	public:
		Exponential();
		void fromPrior();
		double perturb();

};

#endif


