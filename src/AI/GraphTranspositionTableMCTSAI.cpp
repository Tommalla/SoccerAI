#include "GraphTranspositionTableMCTSAI.hpp"

using std::pair;
using namespace engine;

bool isWorse(GraphMCTSStatus* s1, GraphMCTSStatus* s2) {
	if (s1->value != s2->value)
		return s1->value < s2->value;
	if (s1->plays * s2->plays == 0)
		return s1->plays < s2->plays;
	return (double)s1->wins / s1->plays < (double)s2->wins / s2->plays;
}

GraphTranspositionTableMCTSAI::GraphTranspositionTableMCTSAI(const Coord width, const Coord height, const double& c, const size_t& expandBorder, const size_t& memorySize)
: GraphMCTSAI{width, height, c, expandBorder, memorySize}
, nodesTT{memorySize / 2, isWorse}
, edgesTT{memorySize / 2, isWorse} {}

void GraphTranspositionTableMCTSAI::resetMemory() {
	reuseDFS<true>(board);
	reuseDFS<false>(board);
}

DirId GraphTranspositionTableMCTSAI::generateMove() {
	nodesTT.hits = nodesTT.misses = edgesTT.hits = edgesTT.misses = 0;
	auto res = GraphMCTSAI::generateMove();
	printDebug("misses: %d/%d, %d/%d\n", nodesTT.misses, nodesTT.hits, edgesTT.misses, edgesTT.hits);
	return res;
}

pair<MCTSStatus*, bool> GraphTranspositionTableMCTSAI::getOrCreateNode(const Hash& hash) {
	return getOrCreate(nodesTT, hash);
}

pair<MCTSStatus*, bool> GraphTranspositionTableMCTSAI::getOrCreateEdge(const Hash& hash) {
	return getOrCreate(edgesTT, hash);
}

bool GraphTranspositionTableMCTSAI::assertNodeCreated(const Hash& hash) {
	return nodesTT.getOrCreate(hash).second;
}

bool GraphTranspositionTableMCTSAI::assertEdgeCreated(const Hash& hash) {
	return edgesTT.getOrCreate(hash).second;
}

MCTSStatus* GraphTranspositionTableMCTSAI::getNode(const Hash& hash) const {
	return nodesTT.get(hash);
}

MCTSStatus* GraphTranspositionTableMCTSAI::getEdge(const Hash& hash) const {
	return edgesTT.get(hash);
}

bool GraphTranspositionTableMCTSAI::isNodeCreated(const Hash& hash) const {
	return nodesTT.exists(hash);
}

bool GraphTranspositionTableMCTSAI::isEdgeCreated(const Hash& hash) const {
	return edgesTT.exists(hash);
}

pair<MCTSStatus*, bool> GraphTranspositionTableMCTSAI::getOrCreate(GraphTranspositionTableMCTSAI::TTType& tt, const Hash& hash) {
	auto res = tt.getOrCreate(hash);
	return {res.second, res.first};
}
