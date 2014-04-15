#include <cstdio>

#include "objectiveFunctions.hpp"

int objectiveFunctions::simpleDistance(const Board& b, const bool forRed) {
	if (b.isGameFinished())
		return b.doesRedWin() == forRed ? 99999999 : -99999999;
	return b.getPosition().second;
}

