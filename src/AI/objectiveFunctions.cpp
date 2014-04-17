#include <cstdio>

#include "objectiveFunctions.hpp"

int objectiveFunctions::simpleDistance(const Board& b) {
	if (b.isGameFinished())
		return engine::INF * (b.doesRedWin() ? 1 : -1);
	return b.getHeight() - b.getPosition().second;
}

