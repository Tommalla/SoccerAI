#include <cstdio>
#include <cassert>
#include "../engine.hpp"

int main() {
	int a, b;
	uint8_t c;
	a = 10;
	b = 0;
	c = 7;
	assert(engine::numberOfSetBits(a) == 2);
	assert(engine::numberOfSetBits(b) == 0);
	assert(engine::numberOfSetBits(c) == 3);
	return 0;
}