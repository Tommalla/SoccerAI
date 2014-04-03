#include <algorithm>
#include <cassert>

#include "Board.hpp"

using std::vector;
using namespace engine;

Board::Board(Coord width, Coord height)
: directions{-width - 4, -width - 3, -width - 2,
		-1, +1,
		width + 2, width + 3, width + 4}
, width{(Coord)(width + 3)}
, height{(Coord)(height + 3)}
, gameFinished{false} {
	width += 3;
	height += 3;
	edges = new uint8_t[width * height];
	for (int i = 0; i < width * height; ++i)
		edges[i] = 0;
	position = (height / 2) * width + width / 2;
	playerRed = true; //red starts

	//FIXME optimize (or not? works and is issued not-very-often)
	//add borders
	Field f, lastField, midRow;
	lastField = width * height - 1;
	midRow = width / 2;
	// top and bottom line
	for (f = 0; f < width - 1; ++f) {
		addGuardAt(f);
		addGuardAt(lastField - width - f - 1);
	}

	// top-left, top-right, bottom-left, bottom-right
	for (f = width; f < width + midRow - 1; ++f) {
		addGuardAt(f);
		addGuardAt(2 * width - 1 - f + width - 1);
		addGuardAt(lastField - width - f - 1);
		addGuardAt(lastField - 2 * width + 1 + f - 2 * width);
	}

	// left and right
	for (f = 2 * width; f < (height - 3) * width; f += width) {
		addGuardAt(f);
		addGuardAt(f + width - 2);
	}
}

Board::Board(const Board& other)
: directions{other.directions}
, edges{new uint8_t[other.width * other.height]}
, position{other.position}
, width{other.width}
, height{other.height}
, playerRed{other.playerRed} {
	for (int i = 0; i < width * height; ++i)
		edges[i] = other.edges[i];
}

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

	res |= updateGameFinished();

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

vector< DirId > Board::getMoves() const {
	vector<DirId> res;

	for (DirId id = 0; id < (DirId)directions.size(); ++id) {
		if (canGo(id))
			res.push_back(id);
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

bool Board::isGameFinished() const {
	return gameFinished;
}

bool Board::doesRedWin() const {
	return gameFinished && playerRed;
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
	return dirId >= 0 && isValid(dst) && !isEdgeFrom(position, dirId);
}

bool Board::isValid(const Field x) const {
	return x >= 0 && x < width * height;
}

void Board::addGuardAt(Field x) {
	tryConnect(x, RIGHT);
	tryConnect(x, DOWN);
	tryConnect(x, RIGHT_DOWN);

	++x;
	tryConnect(x, DOWN);
	tryConnect(x, LEFT_DOWN);

	x += width;
	tryConnect(x, LEFT);
}

void Board::tryConnect(const Field x, const DirId dirId) {
	if (!isEdgeFrom(x, dirId))
		connect(x, dirId);
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

bool Board::updateGameFinished() {
	if (gameFinished)
		return true;

	if (position >= width + width / 2 - 1 && position <= width + width / 2 + 1) {
		playerRed = gameFinished = true;
	} else if (position >= (height - 1) * width - 2 - width / 2 && position <= (height - 1) * width + 1 - width / 2) {
		playerRed = false;
		gameFinished = true;
	} else if (getMoves().size() == 0) {
		gameFinished = true;
		playerRed = !playerRed;
	}

	return gameFinished;
}
