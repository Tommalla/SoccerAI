#include "GraphMapMCTSAI.hpp"

using namespace engine;

GraphMapMCTSAI::GraphMapMCTSAI(const Coord width, const Coord height, const size_t& expandBorder, const size_t& memorySize)
: MCTSAI{width, height, expandBorder, memorySize} {}

void GraphMapMCTSAI::expand(Board& s, MCTSStatus* node) {
	auto moves = s.getMoves();
	Hash hash;

	MCTSStatus newNode;
	newNode.wins = newNode.plays = 0;
	for (const auto& m: moves) {
		hash = s.getHashAfter(m);
		if (map.find(hash) == map.end())
			map[hash] = new MCTSStatus(newNode);
	}
}

std::pair<MCTSStatus*, DirId> GraphMapMCTSAI::pickSon(Board& s, MCTSStatus* node) const {
	auto moves = s.getMoves();
	bool redActive = s.isRedActive();
	double tmp, bestVal = redActive ? -engine::INF : engine::INF;
	MCTSStatus* res;
	DirId resMove;
	MCTSStatus* it;
	Hash hash;

	for (const auto& m: moves) {
		hash = s.getHashAfter(m);

		tmp = UCB(s, it = map.at(hash), node);
		if ((redActive ? tmp > bestVal : tmp < bestVal)) {
			bestVal = tmp;
			res = it;
			resMove = m;
		}
	}

	return {res, resMove};
}

DirId GraphMapMCTSAI::generateMove() {
	MCTSStatus* root = getOrCreate(board.getHash());
	expand(board, root);
	while (!stopCalculations)
		playout(board, root);

	auto moves = board.getMoves();
	double best = 0.0;
	DirId res;
	MCTSStatus* iter;
	for (const auto& m: moves) {
		iter = map.at(board.getHashAfter(m));
		double tmp = (double)iter->wins / iter->plays;
		printDebug("Possible: %d -> %.3lf (%lu/%lu)\n", m, tmp, iter->wins, iter->plays);
		if (tmp > best) {
			best = tmp;
			res = m;
		}
	}

	return res;
}

void GraphMapMCTSAI::resetMemory() {
	for (const auto& k: map)
		delete k.second;

	map.clear();
}

bool GraphMapMCTSAI::isLeaf(Board& s, MCTSStatus* node) {
	auto moves = s.getMoves();
	Hash hash;

	for (const auto& m: moves) {
		hash = s.getHashAfter(m);

		if (map.find(hash) == map.end())
			return true;
	}

	return false;
}

MCTSStatus* GraphMapMCTSAI::getOrCreate(const engine::Hash& hash) {
	if (map.find(hash) != map.end())
		return map.at(hash);
	return (map[hash] = new MCTSStatus());
}

