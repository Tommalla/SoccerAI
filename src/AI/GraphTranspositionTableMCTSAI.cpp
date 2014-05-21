#include "GraphTranspositionTableMCTSAI.hpp"

GraphTranspositionTableMCTSAI::GraphTranspositionTableMCTSAI(const engine::Coord width, const engine::Coord height, const double& c, const size_t& expandBorder, const size_t& memorySize)
: GraphMCTSAI{width, height, c, expandBorder, memorySize}
, nodesTT{memorySize / 2, [](GraphMCTSStatus* s){return (s->plays == 0) ? 0.0 : (double)(s->wins) / s->plays;}}
, edgesTT{memorySize / 2, [](GraphMCTSStatus* s){return (s->plays == 0) ? 0.0 : (double)(s->wins) / s->plays;}} {}

void GraphTranspositionTableMCTSAI::resetMemory() {
	//FIXME Reuse Subgraph in the future, nothing for now
}

DirId GraphTranspositionTableMCTSAI::generateMove() {
	nodesTT.hits = nodesTT.misses = edgesTT.hits = edgesTT.misses = 0;
	auto res = GraphMCTSAI::generateMove();
	engine::printDebug("misses: %d/%d, %d/%d\n", nodesTT.misses, nodesTT.hits, edgesTT.misses, edgesTT.hits);
	return res;
}

std::pair<MCTSStatus*, bool> GraphTranspositionTableMCTSAI::getOrCreateNode(const engine::Hash& hash) {
	return getOrCreate(nodesTT, hash);
}

std::pair<MCTSStatus*, bool> GraphTranspositionTableMCTSAI::getOrCreateEdge(const engine::Hash& hash) {
	return getOrCreate(edgesTT, hash);
}

bool GraphTranspositionTableMCTSAI::assertNodeCreated(const engine::Hash& hash) {
	return nodesTT.getOrCreate(hash).second;
}

bool GraphTranspositionTableMCTSAI::assertEdgeCreated(const engine::Hash& hash) {
	return edgesTT.getOrCreate(hash).second;
}

MCTSStatus* GraphTranspositionTableMCTSAI::getNode(const engine::Hash& hash) const {
	return nodesTT.get(hash);
}

MCTSStatus* GraphTranspositionTableMCTSAI::getEdge(const engine::Hash& hash) const {
	return edgesTT.get(hash);
}

bool GraphTranspositionTableMCTSAI::isNodeCreated(const engine::Hash& hash) const {
	return nodesTT.exists(hash);
}

bool GraphTranspositionTableMCTSAI::isEdgeCreated(const engine::Hash& hash) const {
	return edgesTT.exists(hash);
}

std::pair< MCTSStatus*, bool > GraphTranspositionTableMCTSAI::getOrCreate(GraphTranspositionTableMCTSAI::TTType& tt, const engine::Hash& hash) {
	auto res = tt.getOrCreate(hash);
	return {res.second, res.first};
}









