#include "GraphMapMCTSAI.hpp"

using std::make_tuple;
using namespace engine;

GraphMapMCTSAI::GraphMapMCTSAI(const Coord width, const Coord height, const double& c, const size_t& expandBorder, const size_t& memorySize)
: GraphMCTSAI{width, height, c, expandBorder, memorySize}
, statsMemory{memorySize} {}

void GraphMapMCTSAI::resetMemory() {
	reuseSet.clear();
	reuseEdgeSet.clear();
	reuseDFS(board);
	reuseEdgeDFS(board);

	printDebug("reuseSet.size() = %lu, map.size() = %lu\nreuseEdgeSet.size() = %lu, edgeMap.size() = %lu\n",
		   reuseSet.size(), nodeMap.size(), reuseEdgeSet.size(), edgeMap.size());

	removeUnusedValues(nodeMap, reuseSet);
	removeUnusedValues(edgeMap, reuseEdgeSet);
}

bool GraphMapMCTSAI::assertNodeCreated(const Hash& hash) {
	return assertCreated(nodeMap, hash);
}

bool GraphMapMCTSAI::assertEdgeCreated(const Hash& hash) {
	return assertCreated(edgeMap, hash);
}

MCTSStatus* GraphMapMCTSAI::getNode(const Hash& hash) const {
	return nodeMap.at(hash);
}

MCTSStatus* GraphMapMCTSAI::getEdge(const Hash& hash) const {
	return edgeMap.at(hash);
}

bool GraphMapMCTSAI::isNodeCreated(const Hash& hash) const {
	return isInMap(nodeMap, hash);
}

bool GraphMapMCTSAI::isEdgeCreated(const Hash& hash) const {
	return isInMap(edgeMap, hash);
}

bool GraphMapMCTSAI::assertCreated(GraphMapMCTSAI::MapType& map, const Hash& hash) {
	if (isInMap(map, hash))
		return true;
	map[hash] = statsMemory.allocate();
	return false;
}

bool GraphMapMCTSAI::isInMap(const GraphMapMCTSAI::MapType& map, const Hash& hash) const {
	return map.find(hash) != map.end();
}

void GraphMapMCTSAI::reuseDFS(Board& s) {
	auto moves = s.getMoves();
	bool change;
	Hash hash;

	for (const auto& m: moves) {
		change = s.play(m);
		hash = s.getHash();

		MapType::iterator iter = nodeMap.find(hash);
		if (iter != nodeMap.end() && reuseSet.find(iter->first) == reuseSet.end()) {
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
