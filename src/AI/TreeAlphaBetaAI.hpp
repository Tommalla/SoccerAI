#ifndef TREE_ALPHA_BETA_AI_HPP
#define TREE_ALPHA_BETA_AI_HPP
#include "AlphaBetaAI.hpp"

class TreeAlphaBetaAI: public AlphaBetaAI {
public:
	TreeAlphaBetaAI(const engine::Coord width, const engine::Coord height, const std::function<int(const Board&)>& value);

protected:
	virtual std::pair<bool, AlphaBetaStatus> getNode(const engine::Hash& hash);
	virtual void saveNode(const AlphaBetaStatus& node);
};

#endif // TREE_ALPHA_BETA_AI_HPP
