#include <cassert>
#include <cmath>

#include "AlphaBetaAI.hpp"

using std::function;
using std::min;
using std::max;

AlphaBetaAI::AlphaBetaAI(const engine::Coord width, const engine::Coord height, const function<int(const Board&)>& value)
: AI(width, height)
, value{value}
, maxDepth{0}
, fieldsUsed{0}
, fields{(width + 1) * (height + 1)} {}

DirId AlphaBetaAI::genMove() {
	AI::genMove();
	Board copy{board};
	auto moves = board.getMoves();
	int bestVal = -1;
	DirId res = 0;
	bool change;

	assert(!moves.empty());
	assert(!board.isGameFinished());

	timeAvailable = timeLeft * fieldsUsed / fields / 10;
	fprintf(stderr, "%d / %d, time available: %lld\n", fieldsUsed, fields, timeAvailable);
	beginTime = engine::getTime();
	operationsCounter = 0;
	stopCalculations = false;

	for (maxDepth = 1; !stopCalculations && bestVal < engine::INF; ++maxDepth) {
		for (auto m: moves) {
			change = copy.play(m);
			int tmp = gen(copy, -engine::INF, engine::INF, 0);
			copy.undo(m, change);

			if (bestVal == -1 || tmp >= bestVal) {
				bestVal = tmp;
				res = m;
			}
		}
	}

	fprintf(stderr, "maxDepth = %d\n", maxDepth);
	return res;
}

int AlphaBetaAI::gen(Board& s, int alpha, int beta, const unsigned int depth) {
	//time control
	if (++operationsCounter >= timeControlOps) {
		operationsCounter = 0;
		engine::Time t = engine::getTime();
		if (t - beginTime >= timeAvailable) {
			stopCalculations = true;
			return value(s);
		}
	}

	if (s.isGameFinished() || depth >= maxDepth) {
		return value(s);
	}

	auto moves = s.getMoves();
	bool minNode = !s.isRedActive();
	int r = engine::INF * (minNode ? 1 : -1);
	bool change;

	//can move this to template...
	for (const auto& m: moves) {
		change = s.play(m);

		int x = gen(s, (minNode ? alpha : max(r, alpha)), (minNode ? min(r, beta) : beta), depth + 1);
		if (minNode ? x <= alpha : x >= beta) {
			s.undo(m, change);
			return x;
		}
		r = minNode ? min(r, x) : max(r, x);

		s.undo(m, change);

		if (stopCalculations)
			return value(s);
	}

	return r;
}

void AlphaBetaAI::play(const DirId& move) {
	AI::play(move);
	++fieldsUsed;
}


