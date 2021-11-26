#ifndef _RNG_H_
#define _RNG_H_

#include <random>
#include <cmath>
#include <chrono>

// Generates a default normal distribution based pseudorandom number generator
class Rng {
	private:
		std::default_random_engine generator;
		std::normal_distribution<double> rng;

	public:
		Rng();
		double generateRandom();
		double generateRandom(double maxSD);
};

#endif