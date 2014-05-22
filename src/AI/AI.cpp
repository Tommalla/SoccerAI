#include <cassert>
#include <cstdio>

#include "AI.hpp"

using namespace engine;
using std::make_pair;

AI::AI(const engine::Coord width, const engine::Coord height)
: board{width, height}
, fieldsUsed{0}
, fields{(width + 1) * (height + 1)}
, alreadyMoved{false} {}

void AI::play(const DirId& move) {
	if (!alreadyMoved) {
		board.changeActivePlayer();
		alreadyMoved = true;
	}
	history.push(make_pair(move, board.play(move)));
	fieldsUsed++;
}

DirId AI::genMove() {
	//don't run the algorithm if the win is obvious
	if (board.canWinInOneMove()) {
		auto moves = board.getMoves();
		bool change;
		size_t i;

		for (i = 0; i < moves.size(); ++i) {
			change = board.play(moves[i]);
			if (board.isGameFinished() && board.doesRedWin())
				break;
			board.undo(moves[i], change);
		}

		board.undo(moves[i], change);
		return moves[i];
	}

	//run the algorithm
	alreadyMoved = true;
	beginTime = getTime();
	operationsCounter = 0;
	stopCalculations = false;
	auto res = generateMove();
	printDebug("Time used: %llu/%llu\n", getTime() - beginTime, timeAvailable);
	return res;
}

void AI::undo() {
	assert(!history.empty());
	auto m = history.top();
	history.pop();

	board.undo(m.first, m.second);
}

void AI::setTimeLeft(const int time) {
	timeLeft = time;
	timeAvailable = timeLeft * fieldsUsed / fields / 10;
	if (timeAvailable == 0)
		timeAvailable = 300;	//0.3s for the beginning
}

bool AI::isTimeLeft() {
	if (++operationsCounter >= timeControlOps) {
		operationsCounter = 0;
		if (getTime() - beginTime >= timeAvailable) {
			stopCalculations = true;
			return false;
		}
	}

	return true;
}

int AI::getFieldsUsed() const {
	return fieldsUsed;
}

int AI::getFields() const {
	return fields;
}
