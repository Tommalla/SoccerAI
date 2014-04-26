#include <cassert>
#include <cstdio>

#include "AI.hpp"

using namespace engine;
using std::make_pair;

AI::AI(const engine::Coord width, const engine::Coord height)
: board{width, height}
, alreadyMoved(false) {}

void AI::play(const DirId& move) {
	if (!alreadyMoved) {
		board.changeActivePlayer();
		alreadyMoved = true;
	}
	history.push(make_pair(move, board.play(move)));
}

DirId AI::genMove() {
	alreadyMoved = true;
	return generateMove();
}

void AI::undo() {
	assert(!history.empty());
	auto m = history.top();
	history.pop();

	board.undo(m.first, m.second);
}

void AI::setTimeLeft(const int time) {
	lastTimeLeft = timeLeft;
	timeLeft = time;
	lastMoveTime = lastTimeLeft - timeLeft;
	if (lastMoveTime < 0)
		lastMoveTime = 0;
}
