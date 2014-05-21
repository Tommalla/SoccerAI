#include "GraphAlphaBetaAI.hpp"

GraphAlphaBetaAI::GraphAlphaBetaAI(const engine::Coord width, const engine::Coord height,
				   const std::function<int(const Board&)>& value, const size_t& memorySize)
: AlphaBetaAI{width, height, value}
, tt{memorySize, [](AlphaBetaStatus* s1, AlphaBetaStatus* s2){return true;}} {}

std::pair< bool, AlphaBetaStatus > GraphAlphaBetaAI::getNode(const engine::Hash& hash) {
	auto res = tt.getOrCreate(hash);
	return {res.first, *res.second};
}

void GraphAlphaBetaAI::saveNode(const AlphaBetaStatus& node) {
	*(tt.getOrCreate(node.hash).second) = node;
}

DirId GraphAlphaBetaAI::generateMove() {
	auto res = AlphaBetaAI::generateMove();
	engine::printDebug("misses = %d/%d\n", tt.misses, tt.hits);
	tt.misses = tt.hits = 0;

	return res;
}

