#ifndef GRAPH_ALPHA_BETA_AI_HPP
#define GRAPH_ALPHA_BETA_AI_HPP
#include "AlphaBetaAI.hpp"
#include "TranspositionTable.hpp"

class GraphAlphaBetaAI: public AlphaBetaAI {
public:
	GraphAlphaBetaAI(const engine::Coord width, const engine::Coord height,
			 const std::function<int(const Board&)>& value, const size_t& memorySize);
	virtual DirId generateMove();

protected:
	virtual std::pair<bool, AlphaBetaStatus> getNode(const engine::Hash& hash);
	virtual void saveNode(const AlphaBetaStatus& node);

	TranspositionTable<AlphaBetaStatus> tt;
};

#endif // GRAPH_ALPHA_BETA_AI_HPP