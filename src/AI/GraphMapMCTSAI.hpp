#ifndef GRAPH_MAP_MCTSAI_HPP
#define GRAPH_MAP_MCTSAI_HPP
#include <unordered_map>
#include <unordered_set>

#include "GraphMCTSAI.hpp"
#include "PseudoDynamicArrayMemoryManager.hpp"

class GraphMapMCTSAI: public GraphMCTSAI {
	typedef std::unordered_map<engine::Hash, MCTSStatus*> MapType;
public:
	GraphMapMCTSAI(const engine::Coord width, const engine::Coord height, const double& c,
		       const size_t& expandBorder, const size_t& memorySize);

protected:
	virtual void resetMemory();
	virtual bool isLeaf(Board& s, MCTSStatus* node);
	virtual bool assertNodeCreated(const engine::Hash& hash);
	virtual bool assertEdgeCreated(const engine::Hash& hash);
	virtual MCTSStatus* getNode(const engine::Hash& hash) const;
	virtual MCTSStatus* getEdge(const engine::Hash& hash) const;

private:
	bool assertCreated(MapType& map, const engine::Hash& hash);
	bool isInMap(const MapType& map, const engine::Hash& hash) const;
	void reuseDFS(Board& s);
	void reuseEdgeDFS(Board& s);
	void removeUnusedValues(MapType& from, const std::unordered_set<engine::Hash>& omit);

	MapType nodeMap;
	std::unordered_set<engine::Hash> reuseSet;
	std::unordered_set<engine::Hash> reuseEdgeSet;
	MapType edgeMap;
	PseudoDynamicArrayMemoryManager<MCTSStatus> statsMemory;
};

#endif // GRAPH_MAP_MCTSAI_HPP