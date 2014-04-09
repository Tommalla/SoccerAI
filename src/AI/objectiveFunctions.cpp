#include "objectiveFunctions.hpp"

int objectiveFunctions::simpleDistance(const Board& b) {
	return b.getPosition().second;
}

