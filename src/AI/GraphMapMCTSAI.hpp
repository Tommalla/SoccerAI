#ifndef GRAPH_MAP_MCTSAI_HPP
#define GRAPH_MAP_MCTSAI_HPP
#include <unordered_map>

#include "MCTSAI.hpp"

class GraphMapMCTSAI: public MCTSAI {
public:
	GraphMapMCTSAI(const engine::Coord width, const engine::Coord height, const size_t& expandBorder, const size_t& memorySize);

protected:
	virtual void expand(Board& s, MCTSStatus* node);
	virtual std::pair<MCTSStatus*, DirId> pickSon(Board& s, MCTSStatus* node) const;

protected:
	virtual DirId generateMove();
	virtual void resetMemory();
	virtual bool isLeaf(Board& s, MCTSStatus* node);

private:
	std::unordered_map<engine::Hash, MCTSStatus*> map;
	MCTSStatus* getOrCreate(const engine::Hash& hash);
};

#endif // GRAPH_MAP_MCTSAI_HPP