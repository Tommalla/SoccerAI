#include <cassert>
#include <random>
#include "RandomAI.hpp"

RandomAI::RandomAI(const engine::Coord& width, const engine::Coord& height)
: AI(width, height) {}


DirId RandomAI::genMove() {
	static std::mt19937 mt{std::random_device{}()};
	AI::genMove();
	auto possible = board.getMoves();
	assert(!possible.empty());
	std::uniform_int_distribution<int> dist{0, (int)possible.size() - 1};
	return possible[dist(mt)];
}
