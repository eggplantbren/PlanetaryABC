/*
* Copyright (c) 2009, 2010, 2011, 2012 Brendon J. Brewer.
*
* This file is part of DNest3.
*
* DNest3 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DNest3 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with DNest3. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MyModel_
#define _MyModel_

#include "Model.h"
#include <vector>

template<class Distribution>
class MyModel:public DNest3::Model
{
	private:
		static const int K_max = 10;

		// Frequency distribution of number of planets (the goal!)
		Distribution dist;

		// Parameters that determine K (number of planets)
		// for each star
		std::vector<double>  u_K;

		// Viewing angle of each star
		std::vector<double> u_A;

		// Parameters that determine the radius, period, and
		// delta inclination for each planet
		std::vector< std::vector<double> > u_R;
		std::vector< std::vector<double> > u_P;
		std::vector< std::vector<double> > u_dI;

		// Partial perturbs
		double perturb_u_K();
		double perturb_u_R();

		// Calculate simulated histogram/data
		std::vector<int> compute_hist() const;

	public:
		MyModel();

		// Generate the point from the prior
		void fromPrior();

		// Metropolis-Hastings proposals
		double perturb();

		// Likelihood function
		double logLikelihood() const;

		// Print to stream
		void print(std::ostream& out) const;

		// Return string with column information
		std::string description() const;
};

#include "MyModelImpl.h"

#endif

