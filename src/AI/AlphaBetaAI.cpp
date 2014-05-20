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

		if (newBestVal == -INF)	//we've already lost, so why use any more time?
			break;
	}

	printDebug("maxDepth = %d, bestVal = %d\n", maxDepth, bestVal);
	return res;
}

int AlphaBetaAI::gen(Board& s, int alpha, int beta, const unsigned int depth) {
	auto p = getNode(s.getHash());
	if (p.first == true && p.second.depth >= maxDepth - depth) {
		if (p.second.type == AlphaBetaStatus::BoundType::LOWER)
			alpha = p.second.result;
		else if (p.second.type == AlphaBetaStatus::BoundType::UPPER)
			beta = p.second.result;

		if (p.second.type == AlphaBetaStatus::BoundType::EXACT || alpha >= beta)
			return p.second.result;
	}

	//time control and game end
	if (!isTimeLeft() || s.isGameFinished() || depth >= maxDepth) {
		int v = value(s);
		storeValue(v, depth, alpha, beta, p.second);
		return v;
	}

	auto moves = s.getMoves();
	bool minNode = !s.isRedActive();
	int r = INF * (minNode ? 1 : -1);
	bool change;

	//can move this to template...
	for (const auto& m: moves) {
		change = s.play(m);

		int x = gen(s, (minNode ? alpha : max(r, alpha)), (minNode ? min(r, beta) : beta), depth + 1);
		if (minNode ? x <= alpha : x >= beta) {
			s.undo(m, change);
			storeValue(x, depth, alpha, beta, p.second);
			return x;
		}

		r = minNode ? min(r, x) : max(r, x);

		storeValue(r, depth, alpha, beta, p.second);

		s.undo(m, change);

		if (stopCalculations)
			return value(s);
	}

	return r;
}

void AlphaBetaAI::storeValue(const int value, const unsigned int depth, const int alpha, const int beta, AlphaBetaStatus& node) {
	if (alpha < value) {
		if (value < beta)
			node.type = AlphaBetaStatus::BoundType::EXACT;
		else
			node.type = AlphaBetaStatus::BoundType::UPPER;
	} else
		node.type = AlphaBetaStatus::BoundType::LOWER;

	node.result = value;
	node.depth = maxDepth - depth;
	saveNode(node);
}


void AlphaBetaAI::play(const DirId& move) {
	AI::play(move);
}
