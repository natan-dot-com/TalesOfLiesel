#include "./lib/backend/rng.h"

Rng::Rng(int start, int end) {
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	rng_normal = std::normal_distribution<double>(0, 1);
	rng_uniform = std::uniform_int_distribution<int>(start, end);
}

// Generates a random real number.
// - Return value: a random number (double)
double Rng::generateRandom() {
	return this->rng_normal(generator);
}

// Generates a random real number bounded by a maximum standard deviation quantity.
// - Return value: Random number bounded from both sides by maxSD (double)
double Rng::generateRandom(double maxSD) {
	double rand;
	do {
		rand = this->rng_normal(generator);
	} while (rand < (-1) * maxSD || rand > maxSD);
	return rand;
}

int Rng::generateUniformRandom() {
	return this->rng_uniform(generator);
}
