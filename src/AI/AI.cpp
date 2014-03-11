#include <cassert>

#include "AI.hpp"

using namespace engine;

AI::AI(const engine::Coord width, const engine::Coord heigth) {
	//TODO empty for now
}

void AI::play(const Move& move) {
	//TODO (need Board implementation for this to work)
	history.push(move);
}

void AI::undo() {
	assert(!history.empty());
	Move m = history.top();
	history.pop();

	//TODO undo move after Board's been implemented
}


