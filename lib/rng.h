#ifndef _RNG_H_
#define _RNG_H_

#include <random>
#include <cmath>
#include <chrono>

// Generates a default normal distribution based pseudorandom number generator
class Rng {
private:
	std::default_random_engine generator;
	std::normal_distribution<double> rng_normal;
	std::uniform_int_distribution<int> rng_uniform;

public:
	Rng(int start = 0, int end = 10);
	double generateRandom();
	double generateRandom(double maxSD);
	int generateUniformRandom();
};

#endif