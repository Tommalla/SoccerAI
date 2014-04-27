#include <cstdio>
#include <functional>
#include <random>
#include "../engine.hpp"

const int num = 10000000;
const int upperBound = 20;

engine::Time generateRandom(std::function<int(void)> f) {
	engine::Time begin = engine::getTime();
	int tmp;
	for (int i = 0; i < num; ++i)
		tmp = f();
	return engine::getTime() - begin;
}

int main() {
	for (int i = 0; i < 5; ++i)
		printf("%lu\n", engine::random());

	printf("Generating %d random numbers from 0 to %d\n", num, upperBound);

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