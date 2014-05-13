#include <cassert>
#include <cmath>

#include "AlphaBetaAI.hpp"

using std::function;
using std::min;
using std::max;
using namespace engine;

AlphaBetaAI::AlphaBetaAI(const engine::Coord width, const engine::Coord height, const function<int(const Board&)>& value)
: AI(width, height)
, value{value}
, maxDepth{0} {}

DirId AlphaBetaAI::generateMove() {
	Board copy{board};
	auto moves = board.getMoves();
	int bestVal, newBestVal;
	DirId res = 0, newRes = 0;
	bool change;

	assert(!moves.empty());
	assert(!board.isGameFinished());

	for (maxDepth = 1, bestVal = newBestVal = -1; !stopCalculations && bestVal < INF; ++maxDepth, newBestVal = -1) {
		for (auto m: moves) {
			change = copy.play(m);
			int tmp = gen(copy, -INF, INF, 0);
			copy.undo(m, change);

			if (newBestVal == -1 || tmp >= newBestVal) {
				newBestVal = tmp;
				newRes = m;
			}
		}

		if (!stopCalculations || (newBestVal != -1 && bestVal < newBestVal)) {
			bestVal = newBestVal;
			res = newRes;
		}
	}

	printDebug("maxDepth = %d, bestVal = %d\n", maxDepth, bestVal);
	return res;
}

int AlphaBetaAI::gen(Board& s, int alpha, int beta, const unsigned int depth) {
	//time control and game end
	if (!isTimeLeft() || s.isGameFinished() || depth >= maxDepth)
		return value(s);

	AlphaBetaStatus stat = getNode(s.getHash());

	auto moves = s.getMoves();
	bool minNode = !s.isRedActive();
	int r = INF * (minNode ? 1 : -1);
	bool change;

	//can move this to template...
	for (const auto& m: moves) {
		change = s.play(m);

		int x = gen(s, (minNode ? stat.alpha : max(r, stat.alpha)), (minNode ? min(r, stat.beta) : stat.beta), depth + 1);
		if (minNode ? x <= stat.alpha : x >= stat.beta) {
			s.undo(m, change);
			if (minNode)
				stat.alpha = x;
			else
				stat.beta = x;
			saveNode(stat);
			return x;
		}
		r = minNode ? min(r, x) : max(r, x);

		if (minNode)
			stat.beta = min(stat.beta, r);
		else
			stat.alpha = max(stat.alpha, r);
		saveNode(stat);

		s.undo(m, change);

		if (stopCalculations)
			return value(s);
	}

	return r;
}

void AlphaBetaAI::play(const DirId& move) {
	AI::play(move);
}
