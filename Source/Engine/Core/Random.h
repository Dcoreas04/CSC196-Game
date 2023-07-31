#pragma once
#include <random>

namespace kiko 
{
	inline void seedRandom(unsigned int seed){
		srand(seed);
	}

	inline int random() {
		return rand();
	}

	 inline int random(unsigned int max) {
		// 0 - (max + 1)
		return rand() & max;
	}

	 inline int random(unsigned int min, unsigned int max) {
		// min - max
		 return min + random(max - min);
	 }

	 inline float randomF() {
		 return random() / (float)RAND_MAX;
	}
	
	 inline float randomF(float max) {
		 return randomF() * max;
	 }

	 inline float randomF(float max, float min) {
		 return min + randomF() * (max - min);
	 }
}