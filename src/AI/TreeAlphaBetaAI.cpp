#include "TreeAlphaBetaAI.hpp"

TreeAlphaBetaAI::TreeAlphaBetaAI(const engine::Coord width, const engine::Coord height, const std::function<int(const Board&)>& value)
: AlphaBetaAI(width, height, value) {}

AlphaBetaStatus TreeAlphaBetaAI::getNode(const engine::Hash& hash) {
	AlphaBetaStatus res{};
	res.hash = hash;
	return res;
}

void TreeAlphaBetaAI::saveNode(const AlphaBetaStatus& node) {}	//NOOP


