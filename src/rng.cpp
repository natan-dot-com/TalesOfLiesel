#include "rng.h"

Rng::Rng() {
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	rng = std::normal_distribution<double>(0, 1);
}

// Generates a random real number.
// - Return value: a random number (double)
double Rng::generateRandom() {
	return this->rng(generator);
}

// Generates a random real number bounded by a maximum standard deviation quantity.
// - Return value: Random number bounded from both sides by maxSD (double)
double Rng::generateRandom(double maxSD) {
	double rand;
	do {
		rand = this->rng(generator);
	} while (rand < (-1) * maxSD || rand > maxSD);
	return rand;
}