#ifndef ALPHA_BETA_AI_HPP
#define ALPHA_BETA_AI_HPP
#include <functional>

#include "AI.hpp"

class AlphaBetaAI : public AI {
public:
	AlphaBetaAI(const engine::Coord width, const engine::Coord height, const std::function<int(const Board&, const bool)>& value);
	virtual DirId genMove();
private:
	int gen(Board& s, int alpha, int beta, const unsigned int depth);
	std::function<int(const Board&, const bool)> value;

	unsigned int maxDepth = 99999999;
	bool isRed;
};

#endif // ALPHA_BETA_AI_HPP