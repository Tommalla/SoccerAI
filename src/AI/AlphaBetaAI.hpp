#ifndef ALPHA_BETA_AI_HPP
#define ALPHA_BETA_AI_HPP
#include <functional>


#include "AI.hpp"
#include "Status.hpp"

class AlphaBetaAI : public AI {
public:
	AlphaBetaAI(const engine::Coord width, const engine::Coord height, const std::function<int(const Board&)>& value);
	virtual void play(const DirId& move);

protected:
	virtual AlphaBetaStatus getNode(const engine::Hash& hash) = 0;	//if there ever is a need to, we might
									//want to change the return value to
									//a shared_ptr to a copy
	virtual void saveNode(const AlphaBetaStatus& node) = 0;

private:
	virtual DirId generateMove();
	int gen(Board& s, int alpha, int beta, const unsigned int depth);

	std::function<int(const Board&)> value;
	//time control
	unsigned int maxDepth;
};

#endif // ALPHA_BETA_AI_HPP