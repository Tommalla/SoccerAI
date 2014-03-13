#include <cassert>

#include "Board.hpp"

using std::vector;
using namespace engine;

Board::Board(const Coord width, const Coord height)
: directions{-width - 1, -width, -width + 1,
		-1, +1,
		width - 1, width, width + 1}
, edges{new uint8_t[width * height]}
, position{(height / 2) * width + width / 2}
, width{width}
, height{height}
, playerRed{true} {}	//red starts

Board::~Board() {
	delete[] edges;
}

bool Board::play(const Move move) {
	Field dst = position + move;
	assert(isValid(dst));
	assert(!isEdgeBetween(position, dst));

	bool res = !edges[dst];

	connect(position, dst);
	position = dst;

	return res;
}

Field Board::getField() const {
	return position;
}

vector<Move> Board::getMoves() const {
	vector<Move> res;

	for (int i = 0; i < directionsQty; ++i) {
		Field dst = position + directions[i];
		if (isValid(dst) && !isEdgeBetween(position, dst))
			res.push_back(directions[i]);
	}

	return res;
}

bool Board::isRedActive() const {
	return playerRed;
}

int Board::getDirectionBetween(const Field a, const Field b) const {
	assert(isValid(a));
	assert(isValid(b));
	Field tmp = a - b;
	for (int i = 0; i < directionsQty; ++i)
		if (directions[i] == tmp)
			return i;
	return -1;
}

bool Board::isEdgeBetween(const Field a, const Field b) const {
	assert(isValid(a));
	assert(isValid(b));
	int dir = getDirectionBetween(a, b);
	if (dir == -1)
		return false;

	return (1 << dir) & edges[a];
}

void Board::connect(const Field a, const Field b) {
	assert(isValid(a));
	assert(isValid(b));
	assert(!isEdgeBetween(a, b));

	int dir = getDirectionBetween(a, b);
	assert(dir >= 0);

	edges[a] |= 1 << dir;
	edges[b] |= 1 << dir;
}

bool Board::canGoTo(const Field x) const {
	assert(isValid(x));
	int dir = getDirectionBetween(position, x);
	return dir >= 0 && !isEdgeBetween(position, x);
}

bool Board::isValid(const Field x) const {
	//FIXME optimize this
	return (x >= width && x <= width * (height - 1)) ||
		(x >= width / 2 - 1 && x <= width / 2 + 1) ||
		(x >= width * (height - 1) + width / 2 - 1 && x <= width * (height - 1) + width / 2 + 1);
}








