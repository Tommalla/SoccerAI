#include <algorithm>
#include <cassert>

#include "Board.hpp"

using std::vector;
using namespace engine;

Board::Board(const Coord width, const Coord height)
: directions{-width - 2, -width - 1, -width,
		-1, +1,
		width, width + 1, width + 2}
, width{(Coord)(width + 1)}
, height{(Coord)(height + 1)} {
	edges = new uint8_t[this->width * this->height];
	position = (this->height / 2) * this->width + this->width / 2;
	playerRed = true; //red starts
	//TODO add borders
}

Board::Board(const Board& other)
: directions{other.directions}
, edges{new uint8_t[other.width * other.height]}
, position{other.position}
, width{other.width}
, height{other.height}
, playerRed{other.playerRed} {}

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

	if (res)
		playerRed = !playerRed;

	return res;
}

void Board::undo(const Move move, const bool changePlayer) {
	Field dst = position + move;
	assert(isValid(dst));
	assert(isEdgeBetween(position, dst));

	int id = getDirectionBetween(position, dst);
	edges[position] ^= 1 << id;

	position = dst;
	if (changePlayer)
		playerRed = !playerRed;

}

Field Board::getField() const {
	return position;
}

vector<Move> Board::getMoves() const {
	vector<Move> res;

	for (const auto& d: directions) {
		Field dst = position + d;
		if (isValid(dst) && !isEdgeBetween(position, dst))
			res.push_back(d);
	}

	return res;
}

bool Board::isRedActive() const {
	return playerRed;
}

Field Board::positionToField(const Position& pos) const {
	return pos.second * width + pos.first;
}

Position Board::fieldToPosition(const Field field) const {
	return Position{field % width, field / width};
}

int Board::getDirectionBetween(const Field a, const Field b) const {
	assert(isValid(a));
	assert(isValid(b));
	Field tmp = b - a;
	for (int i = 0; i < directions.size(); ++i)
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
	edges[b] |= 1 << (directions.size() - 1 - dir);
}

bool Board::canGoTo(const Field x) const {
	assert(isValid(x));
	int dir = getDirectionBetween(position, x);
	return dir >= 0 && !isEdgeBetween(position, x);
}

bool Board::isValid(const Field x) const {
    //FIXME optimize this
	return (x > width && x <= width * (height - 1)) ||
		(x >= width / 2 - 1 && x <= width / 2 + 1) ||
		(x >= width * (height - 1) + width / 2 - 1 && x <= width * (height - 1) + width / 2 + 1);
}

bool Board::isOnBorder(const Field x) const {
	Position pos = fieldToPosition(x);
	return ((pos.first == 0 || pos.first == width) && pos.second > 0 && pos.second < height) ||
		((pos.second == 1 || pos.second == height - 1) && pos.first >= width / 2 - 1 && pos.first <= width / 2 + 1) ||
		((pos.second == 0 || pos.second == height) && pos.first >= width / 2 - 1 && pos.first <= width / 2 + 1);
}









