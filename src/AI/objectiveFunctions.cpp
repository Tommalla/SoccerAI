#include <cstdio>

#include "objectiveFunctions.hpp"

int objectiveFunctions::simpleDistance(const Board& b) {
// 	fprintf(stderr, "%d\n", b.isGameFinished());
	return b.isGameFinished() && !b.doesRedWin() ? 0 : b.getPosition().second;
}

