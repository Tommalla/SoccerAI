#include "GraphMCTSAI.hpp"

using std::make_tuple;
using namespace engine;

GraphMCTSAI::GraphMCTSAI(const engine::Coord width, const engine::Coord height, const double& c, const size_t& expandBorder, const size_t& memorySize)
: MCTSAI{width, height, c, expandBorder, memorySize} {}

void GraphMCTSAI::expand(Board& s, MCTSStatus* node) {
	auto moves = s.getMoves();

	for (const auto& m: moves) {
		assertNodeCreated(s.getHashAfter(m));
		assertEdgeCreated(s.getMoveHash(m));
	}
}

std::tuple<MCTSStatus*, MCTSStatus*, DirId> GraphMCTSAI::pickSon(Board& s, MCTSStatus* node) const {
	auto moves = s.getMoves();
	bool redActive = s.isRedActive();
	double tmp, bestVal = redActive ? -engine::INF : engine::INF;
	MCTSStatus* res;
	MCTSStatus* edgeRes;
	DirId resMove;
	MCTSStatus* edgeIt;

	for (const auto& m: moves) {
		tmp = UCB(s, edgeIt = getEdge(s.getMoveHash(m)), node);
		if ((redActive ? tmp > bestVal : tmp < bestVal)) {
			bestVal = tmp;
			res = getNode(s.getHashAfter(m));
			edgeRes = edgeIt;
			resMove = m;
		}
	}

	return make_tuple(res, edgeRes, resMove);
}

DirId GraphMCTSAI::generateMove() {
	MCTSStatus* root = getOrCreateNode(board.getHash()).first;
	expand(board, root);
	int qty = 0;
	while (!stopCalculations) {
		playout(board, root, nullptr);
		++qty;
	}

	auto moves = board.getMoves();
	double best = 0.0;
	DirId res = -1;
	MCTSStatus* iter;
	for (const auto& m: moves) {
		iter = getEdge(board.getMoveHash(m));
		double tmp = (double)iter->wins / iter->plays;
		printDebug("Possible (edge): %d -> %.3lf (%lu/%lu)\n", m, tmp, iter->wins, iter->plays);
		if (res == -1 || tmp > best) {
			best = tmp;
			res = m;
		}
	}

	printDebug("Ran %d plays\n", qty);

	return res;
}

bool GraphMCTSAI::isLeaf(Board& s, MCTSStatus* node) {
	auto moves = s.getMoves();

	for (const auto& m: moves)
		if (!isNodeCreated(s.getHashAfter(m)) || !isEdgeCreated(s.getMoveHash(m)))
			return true;

		return false;
}

std::pair<MCTSStatus*, bool> GraphMCTSAI::getOrCreateNode(const Hash& hash) {
	bool res = assertNodeCreated(hash);
	return {getNode(hash), res};
}

std::pair<MCTSStatus*, bool> GraphMCTSAI::getOrCreateEdge(const Hash& hash) {
	bool res = assertEdgeCreated(hash);
	return {getEdge(hash), res};
}



