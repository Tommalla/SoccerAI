#include <cassert>

#include "../Engine/Board.hpp"
#include "AlphaBetaAI.hpp"

using std::function;
using std::min;
using std::max;

AlphaBetaAI::AlphaBetaAI(const engine::Coord width, const engine::Coord height, const function<int(const Board&, const bool)>& value)
: AI(width, height)
, value{value} {}


DirId AlphaBetaAI::genMove() {
	Board copy{board};
	auto moves = board.getMoves();
	int bestVal = -1;
	DirId res;
	bool change;

	assert(!moves.empty());
	isRed = board.isRedActive();
	fprintf(stderr, "isRed: %d\n", isRed);

	//TODO iterative deepening (change maxDepth)
	for (auto m: moves) {
		change = copy.play(m);
		int tmp = gen(copy, 999999999, -99999999, 0);	//FIXME change values
		copy.undo(m, change);

		if (bestVal == -1 || (change ? tmp > bestVal : tmp < bestVal)) {
			fprintf(stderr, "New best result: %d, %d\n", tmp, m);
			bestVal = tmp;
			res = m;
		}
	}
	
	change = board.play(res);
	fprintf(stderr, "genmove: moves left: %d, isGameFinished: %d, doesRedWin: %d, result: %d, resMove: %d\n", board.getMoves().size(), board.isGameFinished(), 
		board.doesRedWin(), bestVal, res);
	board.undo(res, change);

	return res;
}

int AlphaBetaAI::gen(Board& s, int alpha, int beta, const unsigned int depth) {
	if (s.isGameFinished() || depth >= maxDepth) {
		int tmp = value(s, !isRed);
		fprintf(stderr, "Reached leaf: %d, igf: %d, drw: %d, d: %d\n", tmp, s.isGameFinished(), s.doesRedWin(), depth);
		return tmp;
	}

// 	fprintf(stderr, "Move...\n");
	
	auto moves = s.getMoves();
	bool minNode = isRed != s.isRedActive();
	int r = 99999999 * (minNode ? -1 : 1);
	bool change;

	//can move this to template...
	for (auto m: moves) {
		change = s.play(m);

		int x = gen(s, (minNode ? alpha : max(r, alpha)), (minNode ? min(r, beta) : beta), depth + 1);
		if ((minNode ? x <= alpha : x >= beta)) {
			s.undo(m, change);
			return x;
		}
		r = minNode ? min(r, x) : max(r, x);

		s.undo(m, change);
	}

	return r;
}



