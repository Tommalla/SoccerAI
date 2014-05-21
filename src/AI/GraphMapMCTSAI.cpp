#include "GraphMapMCTSAI.hpp"

using std::make_tuple;
using namespace engine;

GraphMapMCTSAI::GraphMapMCTSAI(const Coord width, const Coord height, const double& c, const size_t& expandBorder, const size_t& memorySize)
: MCTSAI{width, height, c, expandBorder, memorySize}
, statsMemory{memorySize} {}

void GraphMapMCTSAI::expand(Board& s, MCTSStatus* node) {
	auto moves = s.getMoves();
	Hash hash;
	Hash edgeHash;

	for (const auto& m: moves) {
		hash = s.getHashAfter(m);
		edgeHash = s.getMoveHash(m);

		if (map.find(hash) == map.end())
			map[hash] = statsMemory.allocate();
		if (edgeMap.find(edgeHash) == edgeMap.end())
			edgeMap[edgeHash] = statsMemory.allocate();
	}
}

std::tuple<MCTSStatus*, MCTSStatus*, DirId> GraphMapMCTSAI::pickSon(Board& s, MCTSStatus* node) const {
	auto moves = s.getMoves();
	bool redActive = s.isRedActive();
	double tmp, bestVal = redActive ? -engine::INF : engine::INF;
	MCTSStatus* res;
	MCTSStatus* edgeRes;
	DirId resMove;
	MCTSStatus* edgeIt;
	Hash hash, edgeHash;

	for (const auto& m: moves) {
		hash = s.getHashAfter(m);
		edgeHash = s.getMoveHash(m);

		tmp = UCB(s, edgeIt = edgeMap.at(edgeHash), node);
		if ((redActive ? tmp > bestVal : tmp < bestVal)) {
			bestVal = tmp;
			res = map.at(hash);
			edgeRes = edgeIt;
			resMove = m;
		}
	}

	return make_tuple(res, edgeRes, resMove);
}

DirId GraphMapMCTSAI::generateMove() {
	MCTSStatus* root = getOrCreateNode(board.getHash());
	expand(board, root);
	int qty = 0;
	while (!stopCalculations) {
		playout(board, root, nullptr);
		++qty;
	}

	auto moves = board.getMoves();
	double best = 0.0;
	DirId res;
	MCTSStatus* iter;
	for (const auto& m: moves) {
		iter = edgeMap.at(board.getMoveHash(m));
		double tmp = (double)iter->wins / iter->plays;
		printDebug("Possible (edge): %d -> %.3lf (%lu/%lu)\n", m, tmp, iter->wins, iter->plays);
		if (tmp > best) {
			best = tmp;
			res = m;
		}
	}

	printDebug("Ran %d plays\n", qty);

	return res;
}

void GraphMapMCTSAI::resetMemory() {
	reuseSet.clear();
	reuseEdgeSet.clear();
	reuseDFS(board);
	reuseEdgeDFS(board);

	printDebug("reuseSet.size() = %lu, map.size() = %lu\nreuseEdgeSet.size() = %lu, edgeMap.size() = %lu\n",
		   reuseSet.size(), map.size(), reuseEdgeSet.size(), edgeMap.size());

	removeUnusedValues(map, reuseSet);
	removeUnusedValues(edgeMap, reuseEdgeSet);
}

bool GraphMapMCTSAI::isLeaf(Board& s, MCTSStatus* node) {
	auto moves = s.getMoves();
	Hash hash, edgeHash;

	for (const auto& m: moves) {
		hash = s.getHashAfter(m);
		edgeHash = s.getMoveHash(m);

		if (map.find(hash) == map.end() || edgeMap.find(edgeHash) == edgeMap.end())
			return true;
	}

	return false;
}

MCTSStatus* GraphMapMCTSAI::getOrCreateNode(const engine::Hash& hash) {
	if (map.find(hash) != map.end())
		return map.at(hash);
	return (map[hash] = statsMemory.allocate());
}

void GraphMapMCTSAI::reuseDFS(Board& s) {
	auto moves = s.getMoves();
	bool change;
	Hash hash;

	for (const auto& m: moves) {
		change = s.play(m);
		hash = s.getHash();

		MapType::iterator iter = map.find(hash);
		if (iter != map.end() && reuseSet.find(iter->first) == reuseSet.end()) {
			reuseSet.insert(hash);
			reuseDFS(s);
		}

		s.undo(m, change);
	}
}

void GraphMapMCTSAI::reuseEdgeDFS(Board& s) {
	auto moves = s.getMoves();
	Hash edgeHash;

	for (const auto& m: moves) {
		edgeHash = s.getMoveHash(m);

		MapType::iterator iter = edgeMap.find(edgeHash);
		if (iter != edgeMap.end() && reuseEdgeSet.find(iter->first) == reuseEdgeSet.end()) {
			reuseEdgeSet.insert(edgeHash);
			bool change = s.play(m);
			reuseEdgeDFS(s);
			s.undo(m, change);
		}
	}
}

void GraphMapMCTSAI::removeUnusedValues(GraphMapMCTSAI::MapType& from, const std::unordered_set< Hash >& omit) {
	for (MapType::iterator iter = from.begin(), tmpIter; iter != from.end();)
		if (omit.find(iter->first) == omit.end()) {
			statsMemory.deallocate(iter->second);
			tmpIter = iter;
			++iter;
			from.erase(tmpIter);
		} else
			++iter;
}
