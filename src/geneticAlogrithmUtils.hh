#ifndef GENETIC_ALGORITHM_UTILS
#define GENETIC_ALGORITHM_UTILS

#include <random>

unsigned long long lRand() {
	std::random_device rd;
	std::mt19937_64 eng(rd());
	std::uniform_int_distribution<unsigned long long> distr;

	return distr(eng);
}

#endif