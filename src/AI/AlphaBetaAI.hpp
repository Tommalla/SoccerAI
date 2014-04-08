#ifndef ALPHA_BETA_AI_HPP
#define ALPHA_BETA_AI_HPP
#include <functional>

#include "AI.hpp"

class AlphaBetaAI : public AI {
public:
	AlphaBetaAI(const engine::Coord width, const engine::Coord height, const std::function<int(const Board&)>& value);
	virtual DirId genMove();
private:
	int gen(Board& s, int alpha, int beta, unsigned int depth);
	std::function<int(const Board&)> value;
};

#endif // ALPHA_BETA_AI_HPP