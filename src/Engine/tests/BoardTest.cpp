#include <cstdio>
#include <cassert>
#include <string>
#include <vector>

#include "../Board.hpp"
#include "../engine.hpp"

using namespace engine;
using namespace std;

void testGoalPost(const DirId postDir, const DirId lastMove, bool redWins) {
	Board b(8, 12);
	for (int i = 0; i < 5; ++i)
		b.play(postDir);
	b.play(lastMove);
	assert(b.isGameFinished());
	assert(b.doesRedWin() == redWins);
}

void testGoalPostMoves(const DirId postDir, const size_t qty) {
	Board b(8, 12);
	for (int i = 0; i < 5; ++i)
		b.play(postDir);
	assert(b.getMoves().size() == qty);
}

void testTopBottomBorder(const DirId postDir, const DirId dirMove, const DirId impossibleMove) {
	Board b(8, 12);
	for (int i = 0; i < 5; ++i)
		b.play(postDir);
	b.play(dirMove);
	assert(!b.canGo(impossibleMove));
}

int main() {
	Board b(8, 12);
	assert(b.getField() == 82);
	assert(b.isRedActive());

	puts("Testing simple moves and hashing.");

	vector<DirId> ids = {0, 1, 2, 3, 6, 4, 5, 4, 7};
	const char* dirs[] = {"left-up", "up", "right-up", "left", "down", "right", "left-down", "right", "right-down"};
	Position pos[] = {{4, 6}, {4, 5}, {5, 4}, {4, 4}, {4, 5}, {5, 5}, {4, 6}, {5, 6}, {6, 7}};
	engine::Hash hashes[ids.size()];
	size_t ds = b.directions.size();
	size_t qty[] = {ds - 1, ds - 1, ds - 1, ds - 1, ds - 3, ds - 1, ds - 3, ds - 1, ds - 1};
	bool red[] = {0, 1, 0, 1, 1, 0, 0, 1, 0};

	for (size_t i = 0; i < ids.size(); ++i) {
		printf("Moving %s.\n", dirs[i]);
		b.play(ids[i]);
		hashes[i] = b.getHash();
		assert(b.fieldToPosition(b.getField()) == pos[i]);
		assert(b.getMoves().size() == qty[i]);
		assert(b.isRedActive() == red[i]);
	}

	Board d{b};
	for (int i = ids.size() - 1; i >= 1; --i) {
		printf("Undoing %s.\n", dirs[i]);
		b.undo(ids[i], red[i] != red[i - 1]);
		assert(b.fieldToPosition(b.getField()) == pos[i - 1]);
		assert(b.getMoves().size() == qty[i - 1]);
		assert(b.isRedActive() == red[i - 1]);
		assert(b.getHash() == hashes[i - 1]);
	}

	size_t i;
	for (i = ids.size() - 1; i >= ids.size() - 3; --i) {
		printf("Undoing %s.\n", dirs[i]);
		d.undo(ids[i], red[i] != red[i - 1]);
	}

	for(++i; i < ids.size(); ++i) {
		printf("Moving %s.\n", dirs[i]);
		d.play(ids[i]);
		assert(d.fieldToPosition(d.getField()) == pos[i]);
		assert(d.getMoves().size() == qty[i]);
		assert(d.isRedActive() == red[i]);
		assert(d.getHash() == hashes[i]);
	}

	puts("\nTest board edges.");

	Board c(8, 12);
	for (int i = 0; i < 4; ++i)
		c.play(Board::RIGHT);
	assert(c.fieldToPosition(c.getField()) == Position(9, 7));
	assert(c.getMoves().size() == 2);

	puts("\nTest left corner of upper goalpost");
	testGoalPost(Board::UP, Board::LEFT_UP, true);

	puts("\nTest middle of upper goalpost");
	testGoalPost(Board::UP, Board::UP, true);

	puts("\nTest right corner of upper goalpost");
	testGoalPost(Board::UP, Board::RIGHT_UP, true);

	puts("\nTest left corner of lower goalpost");
	testGoalPost(Board::DOWN, Board::LEFT_DOWN, false);

	puts("\nTest middle of lower goalpost");
	testGoalPost(Board::DOWN, Board::DOWN, false);

	puts("\nTest right corner of lower goalpost");
	testGoalPost(Board::DOWN, Board::RIGHT_DOWN, false);

	puts("\nTest top-left border");
	testTopBottomBorder(Board::UP, Board::LEFT, Board::LEFT);
	testTopBottomBorder(Board::UP, Board::LEFT, Board::UP);

	puts("\nTest top goalpost moves available");
	testGoalPostMoves(Board::UP, 7);
	puts("\nTest bottom goalpost moves available");
	testGoalPostMoves(Board::DOWN, 7);

	puts("OK");
	return 0;
}