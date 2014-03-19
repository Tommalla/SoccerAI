#include <algorithm>
#include <cassert>

#include "Board.hpp"

using std::vector;
using namespace engine;

Board::Board(Coord width, Coord height)
: directions{-width - 2, -width - 1, -width,
		-1, +1,
		width, width + 1, width + 2}
, width{(Coord)(width + 1)}
, height{(Coord)(height + 1)} {
	++width;
	++height;
	edges = new uint8_t[width * height];
	position = (height / 2) * width + width / 2;
	playerRed = true; //red starts

	//add borders
	Field f;
	for (f = 3; f < 5; ++f) {
		connect(f, f + 1);	//upper goalpost
		connect(f + width * (height - 1), f + width * (height - 1) + 1);	//bottom goalpost
	}

	for (f = 0 + width; f < 3 + width; ++f) {
		connect(f, f + 1);	//top line (left)
		connect(f + width * (height - 3), f + width * (height - 3) + 1);	//bottom line (left)

		connect(3 * width - f - 1, 3 * width - f - 2);	//top line (right)
		connect(width * height - 1 - f, width * height - 1 - f - 1);	//bottom line (right)
	}

	connect(3, 3 + width);
	connect(5, 5 + width);
	connect(height * width - 1 - 3, (height - 1) * width - 1 - 3);
	connect(height * width - 1 - 5, (height - 1) * width - 1 - 5);

	for (f = width; f < (height - 2) * width; f += width) {
		connect(f, f + width);	//left border
		connect(f + width - 1, f + 2 * width - 1);	//right border
	}
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
		if (canGoTo(dst))
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

bool Board::isEdgeBetween(const Field a, const Field b) const {
	assert(isValid(a));
	assert(isValid(b));
	int dir = getDirectionBetween(a, b);
	if (dir == -1)
		return false;

	return (1 << dir) & edges[a];
}

int Board::getDirectionBetween(const Field a, const Field b) const {
	assert(isValid(a));
	assert(isValid(b));
	Field tmp = b - a;
	for (int i = 0; i < (int)directions.size(); ++i)
		if (directions[i] == tmp)
			return i;
	return -1;
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
	int dir = getDirectionBetween(position, x);
	return dir >= 0 && isValid(x) && !isEdgeBetween(position, x) &&
	!(isOnBorder(position) && isOnBorder(x));
}

bool Board::isValid(const Field x) const {
	//FIXME optimize this
	return (x >= width && x <= width * (height - 1)) ||
		(x >= width / 2 - 1 && x <= width / 2 + 1) ||
		(x >= width * (height - 1) + width / 2 - 1 && x <= width * (height - 1) + width / 2 + 1);
}

bool Board::isOnBorder(const Field x) const {
	Position pos = fieldToPosition(x);
	Coord w = width - 1;
	Coord h = height - 1;
	return ((pos.first == 0 || pos.first == w) && pos.second > 0 && pos.second < h) ||
		((pos.second == 1 || pos.second == h - 1) && pos.first >= w / 2 - 1 && pos.first <= w / 2 + 1) ||
		((pos.second == 0 || pos.second == h) && pos.first >= w / 2 - 1 && pos.first <= w / 2 + 1);
}
