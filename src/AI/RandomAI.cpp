#include <cstdlib>
#include <ctime>

#include "RandomAI.hpp"

using std::time;

RandomAI::RandomAI(const engine::Coord width, const engine::Coord height)
: AI(width, height) {
	srand(time(nullptr));
}

DirId RandomAI::genMove() {
	AI::genMove();
	auto possible = board.getMoves();
	return possible[rand() % possible.size()];
}
