#include <cstdio>
#include "../engine.hpp"

int main() {
	for (int i = 0; i < 5; ++i)
		printf("%lu\n", engine::random());
	return 0;
}