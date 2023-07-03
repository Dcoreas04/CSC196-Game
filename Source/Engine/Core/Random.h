#pragma once
#include <random>

namespace kiko 
{
	void seedRandom(unsigned int seed){
		srand(seed);
	}

	 int random() {
		return rand();
	}

	 int random(unsigned int max) {
		// 0 - (max + 1)
		return rand() & max;
	}

	 int random(unsigned int min, unsigned int max) {
		// min - max
		 return min + random(max - min);
	 }
}