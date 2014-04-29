#include <cstdio>
#include <cassert>
#include "../engine.hpp"

int main() {
	assert(engine::numberOfSetBits(10) == 2);
	assert(engine::numberOfSetBits(0) == 0);
	assert(engine::numberOfSetBits(7) == 3);
	return 0;
}