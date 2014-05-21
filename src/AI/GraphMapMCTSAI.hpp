#ifndef GRAPH_MAP_MCTSAI_HPP
#define GRAPH_MAP_MCTSAI_HPP
#include <unordered_map>
#include <unordered_set>

#include "MCTSAI.hpp"
#include "PseudoDynamicArrayMemoryManager.hpp"

class GraphMapMCTSAI: public MCTSAI {
	typedef std::unordered_map<engine::Hash, MCTSStatus*> MapType;
public:
	GraphMapMCTSAI(const engine::Coord width, const engine::Coord height, const double& c,
		       const size_t& expandBorder, const size_t& memorySize);

protected:
	virtual void expand(Board& s, MCTSStatus* node);
	virtual std::tuple<MCTSStatus*, MCTSStatus*, DirId> pickSon(Board& s, MCTSStatus* node) const;

protected:
	virtual DirId generateMove();
	virtual void resetMemory();
	virtual bool isLeaf(Board& s, MCTSStatus* node);

private:
	MCTSStatus* getOrCreateNode(const engine::Hash& hash);
	void reuseDFS(Board& s);
	void reuseEdgeDFS(Board& s);
	void removeUnusedValues(MapType& from, const std::unordered_set<engine::Hash>& omit);

	MapType map;
	std::unordered_set<engine::Hash> reuseSet;
	std::unordered_set<engine::Hash> reuseEdgeSet;
	MapType edgeMap;
	PseudoDynamicArrayMemoryManager<MCTSStatus> statsMemory;
};

#endif // GRAPH_MAP_MCTSAI_HPP