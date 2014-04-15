#include <cassert>
#include <cstdio>

#include "AI.hpp"

using namespace engine;
using std::make_pair;

AI::AI(const engine::Coord width, const engine::Coord height)
: board{width, height} {}

void AI::play(const DirId& move) {
	history.push(make_pair(move, board.play(move)));
}

void AI::undo() {
	assert(!history.empty());
	auto m = history.top();
	history.pop();

	board.undo(m.first, m.second);
}

void AI::setTimeLeft(const unsigned int time) {}	//NOOP



