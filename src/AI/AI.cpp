#include <cassert>

#include "AI.hpp"

using namespace engine;

AI::AI(const engine::Coord width, const engine::Coord height)
: board{width, height} {}

void AI::play(const Move& move) {
	board.play(move);
	history.push(move);
}

void AI::undo() {
	assert(!history.empty());
	Move m = history.top();
	history.pop();

	//TODO undo move after Board's been implemented
}


