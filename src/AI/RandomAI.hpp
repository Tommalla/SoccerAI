#ifndef RANDOM_AI_HPP
#define RANDOM_AI_HPP

#include "AI.hpp"

class RandomAI: public AI {
public:
	RandomAI(const engine::Coord& width, const engine::Coord& height);

protected:
	virtual DirId generateMove();
};

#endif // RANDOM_AI_HPP