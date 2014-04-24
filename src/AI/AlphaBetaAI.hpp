#ifndef ALPHA_BETA_AI_HPP
#define ALPHA_BETA_AI_HPP
#include <functional>

#include "AI.hpp"

class AlphaBetaAI : public AI {
public:
	AlphaBetaAI(const engine::Coord width, const engine::Coord height, const std::function<int(const Board&)>& value);
	virtual DirId genMove();
	virtual void play(const DirId& move);
private:
	int gen(Board& s, int alpha, int beta, const unsigned int depth);

	std::function<int(const Board&)> value;
	//time control
	unsigned int maxDepth;
	engine::Time timeAvailable, beginTime;
	int operationsCounter;
	bool stopCalculations;
	const int timeControlOps = 500;
	int fieldsUsed, fields;
};

#endif // ALPHA_BETA_AI_HPP