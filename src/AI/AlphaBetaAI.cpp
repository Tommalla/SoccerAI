#include <cassert>

#include "AlphaBetaAI.hpp"

using std::function;

AlphaBetaAI::AlphaBetaAI(const engine::Coord width, const engine::Coord height, const function<int(const Board&)>& value)
: AI(width, height)
, value{value} {}


DirId AlphaBetaAI::genMove() {
	Board copy = board;
	auto moves = board.getMoves();
	int bestVal = 99999999;
	DirId res;
	bool change;

	assert(!moves.empty());


	for (auto m: moves) {
		change = copy.play(m);
		int tmp = gen(copy, 0, 0, 0);	//FIXME change values
		copy.undo(m, change);

		if (tmp < bestVal) {
			bestVal = tmp;
			res = m;
		}
	}

	return res;
}

int AlphaBetaAI::gen(Board& s, int alpha, int beta, unsigned int depth) {
	//TODO
}



