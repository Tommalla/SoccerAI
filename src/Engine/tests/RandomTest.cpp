#undef NDEBUG

#include <cstdio>
#include <cassert>
#include <functional>
#include <random>
#include "../engine.hpp"

const int num = 10000000;
const int upperBound = 20;

engine::Time generateRandom(std::function<int(void)> f) {
	engine::Time begin = engine::getTime();
	int tmp;
	for (int i = 0; i < num; ++i)
		tmp = f() * tmp;
	return engine::getTime() - begin;
}

int main() {
	printf("Random\n");
	for (int i = 0; i < 5; ++i)
		printf("%lu\n", engine::random());

	printf("\nDeterministic random\n");
	uint_fast64_t t[] = {
		14514284786278117030ull,
		4620546740167642908ull,
		13109570281517897720ull,
		17462938647148434322ull,
		355488278567739596ull
	};

	for (int i = 0; i < 5; ++i)
		assert(engine::deterministicRandom() == t[i]);

	printf("\nGenerating %d random numbers from 0 to %d\n", num, upperBound);

	std::uniform_int_distribution<int> dist{0, upperBound};
	std::mt19937 mt;

	engine::Time results[] = {
		generateRandom([] () -> int {return rand() % (upperBound + 1);}),
		generateRandom([&] () -> int {return dist(mt);}),
		generateRandom([&] () -> int {return mt() % (upperBound + 1);})
	};

	printf("Stdlib: %lldms\nC++11: %lldms\nC++11 with modulo: %lldms\n",
	       results[0], results[1], results[2]);
	return 0;
}