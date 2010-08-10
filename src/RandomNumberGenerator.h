/*
----------------------------------------------------------------------------
This file is part of MSL (Molecular Simulation Library)n
 Copyright (C) 2009 Dan Kulp, Alessandro Senes, Jason Donald, Brett Hannigan

This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, 
 USA, or go to http://www.gnu.org/copyleft/lesser.txt.
----------------------------------------------------------------------------
*/

/*
  Random Number Generation Object
 */

#ifndef RANDOM_H
#define RANDOM_H

// STL Includes
#include <iostream> 
#include <vector>

// GSL Includes
#ifdef __GSL__
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#endif

// MSL Includes
#include "MslTools.h"


namespace MSL { 
class RandomNumberGenerator {
	
	public:
		RandomNumberGenerator();
		~RandomNumberGenerator();

		int operator()(int _upperLimit); // get a random int

		void setRNGType(std::string _type);
		std::string getRNGType();    // Stored in random 
		std::string getRNGTypeGSL(); // Directly from GSL

		void setRNGSeed(int _seed);
		int getRNGSeed();
		void setRNGTimeBasedSeed();

		// get random double (NOTE LOWER limits *INCLUDED*, UPPER limit *NOT* included!)
		double getRandomDouble(); // between 0 and 1 
		double getRandomDouble(double _upperLimit);  // between 0 and _upperLimit
		double getRandomDouble(double _lowerLimit, double _upperLimit); // between _lowerLimit and _upperLimit

		// get random int (NOTE LOWER and UPPER limits *INCLUDED*)
		unsigned long int    getRandomInt(); // between 0 and RAND_MAX
		unsigned long int    getRandomInt(unsigned long int _upperLimit); // between 0 and _upperLimit (included)
		long int             getRandomInt(long int _lowerLimit, long int _upperLimit); // between _lowerLimit and _upperLimit (both included)
		unsigned long int    getRandomIntLimit(int _upperLimit); // DEPRECATED


		/* The following takes a vector of probabilities and return a biased
		   ramdom indes. For example (0.25, 0.5, 0.25) is twice as likely to
		   return 1 than 0 or 2                                              */
		void setDiscreteProb(const std::vector<double> _prob);
		//void setDiscreteProb(const double *_prob,int _size); // old C style array function
		int getRandomDiscreteIndex();

		void printAvailableRNGAlgorithms();
	private:		

		int randSeed;
		std::string randType;
		

#ifndef __GSL__
		std::vector<double> cumulProb;
#else
		const gsl_rng_type *Type;
		gsl_rng *rngObj;
		gsl_ran_discrete_t *gsl_discrete;
#endif
};

inline int RandomNumberGenerator::operator()(int _upperLimit) { return getRandomInt(_upperLimit); }
}

#endif


