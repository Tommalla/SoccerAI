#include "AI.hpp"

class RandomAI: public AI {
public:
	RandomAI(const engine::Coord width, const engine::Coord height);

	virtual DirId genMove();
};