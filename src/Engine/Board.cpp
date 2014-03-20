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
	Field f, lastField, midRow;
	lastField = width * height - 1;
	midRow = width / 2;
	for (f = 3; f < midRow + 1; ++f) {
		connect(f, f + 1);	//upper goalpost
		connect(f + width * (height - 1), f + width * (height - 1) + 1);	//bottom goalpost
	}

	for (f = 0 + width; f < midRow - 1 + width; ++f) {
		connect(f, f + 1);	//top line (left)
		connect(f + width * (height - 3), f + width * (height - 3) + 1);	//bottom line (left)

		connect(3 * width - f - 1, 3 * width - f - 2);	//top line (right)
		connect(lastField - f, lastField - f - 1);	//bottom line (right)
	}

	//goalpost left-right borders
	connect(midRow - 1, midRow - 1 + width);
	connect(midRow + 1, midRow + 1 + width);
	connect(lastField - midRow + 1, (height - 1) * width - 1 - midRow + 1);
	connect(lastField - midRow - 1, (height - 1) * width - 1 - midRow - 1);

	for (f = width; f < (height - 2) * width; f += width) {
		connect(f, f + width);	//left border
		connect(f + width - 1, f + 2 * width - 1);	//right border
	}

	//extra hackish moves around the goalpost
	connect(midRow - 1, midRow - 2 + width);
	connect(midRow + 1, midRow + 2 + width);
 	connect(lastField - midRow + 1, lastField - width - midRow + 2);
	connect(lastField - midRow - 1, lastField - width - midRow - 2);
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
	return play(getDirectionBetween(position, position + move));
}

bool Board::play(const DirId moveId) {
	Field dst = position + directions[moveId];
	bool res = !edges[dst];

	assert(isValid(dst));
	assert(!isEdgeFrom(position, moveId));

	connect(position, moveId);
	position = dst;

	if (res)
		playerRed = !playerRed;

	return res;
}

void Board::undo(const Move move, const bool changePlayer) {
	undo(getDirectionBetween(position, position + move), changePlayer);
}

void Board::undo(const DirId moveId, const bool changePlayer) {
	assert(moveId >= 0);

	Field dst = position + directions[moveId];
	assert(isValid(dst));
	assert(isEdgeFrom(position, moveId));

	edges[position] ^= 1 << moveId;

	position = dst;
	if (changePlayer)
		playerRed = !playerRed;
}


Field Board::getField() const {
	return position;
}

Position Board::getPosition() const {
	return fieldToPosition(position);
}

vector<Move> Board::getMoves() const {
	vector<Move> res;

	for (DirId id = 0; id < (DirId)directions.size(); ++id) {
		if (canGo(id))
			res.push_back(directions[id]);
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

DirId Board::getDirectionBetween(const Field a, const Field b) const {
	assert(isValid(a));
	assert(isValid(b));
	Field tmp = b - a;
	for (int i = 0; i < (int)directions.size(); ++i)
		if (directions[i] == tmp)
			return i;
	return -1;
}

void Board::connect(const Field a, const Field b) {
	assert(!isEdgeBetween(a, b));
	connect(a, getDirectionBetween(a, b));
}

void Board::connect(const Field a, const DirId dirId) {
	assert(dirId >= 0);
	assert(isValid(a));
	assert(!isEdgeFrom(a, dirId));

	Field dst = a + directions[dirId];
	assert(isValid(dst));

	edges[a] |= 1 << dirId;
	edges[dst] |= 1 << (directions.size() - 1 - dirId);
}

bool Board::canGo(const DirId dirId) const {
	Field dst = position + directions[dirId];
	return dirId >= 0 && isValid(dst) && isEdgeFrom(position, dirId) &&
	!(isOnBorder(position) && isOnBorder(dst));
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

bool Board::isEdgeBetween(const Field a, const Field b) const {
	int dir = getDirectionBetween(a, b);
	return isEdgeFrom(a, dir);
}

bool Board::isEdgeFrom(const Field a, const DirId dirId) const {
	assert(isValid(a));
	assert(isValid(a + directions[dirId]));

	if (dirId == -1)
		return false;
	return (1 << dirId) & edges[a];
}