#include "Random.h"

const size_t Random::RandomNumber(const size_t& a, const size_t& b)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int> distribution(a, b);
	return distribution(gen);
}