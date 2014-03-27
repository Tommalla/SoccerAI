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

int main() {
	Board b(8, 12);
	assert(b.getField() == 82);
	assert(b.isRedActive());

	puts("Testing simple moves.");

	vector<int> ids = {0, 1, 2, 3, 6, 4, 5, 4, 7};
	const char* dirs[] = {"left-up", "up", "right-up", "left", "down", "right", "left-down", "right", "right-down"};
	Position pos[] = {{4, 6}, {4, 5}, {5, 4}, {4, 4}, {4, 5}, {5, 5}, {4, 6}, {5, 6}, {6, 7}};
	size_t ds = b.directions.size();
	size_t qty[] = {ds - 1, ds - 1, ds - 1, ds - 1, ds - 3, ds - 1, ds - 3, ds - 1, ds - 1};
	bool red[] = {0, 1, 0, 1, 1, 0, 0, 1, 0};

	for (size_t i = 0; i < ids.size(); ++i) {
		printf("Moving %s.\n", dirs[i]);
		b.play(b.directions[ids[i]]);
		assert(b.fieldToPosition(b.getField()) == pos[i]);
		assert(b.getMoves().size() == qty[i]);
		assert(b.isRedActive() == red[i]);
	}

	puts("\nTest board edges.");

	Board c(8, 12);
	for (int i = 0; i < 4; ++i)
		c.play(c.directions[4]);
	assert(c.fieldToPosition(c.getField()) == Position(9, 7));
	assert(c.getMoves().size() == 2);

	puts("\nTest left corner of upper goalpost");
	testGoalPost(Board::UP, Board::LEFT_UP, true);

	puts("\nTest middle of upper goalpost");
	testGoalPost(Board::UP, Board::UP, true);

	puts("\nTest right corner of upper goalpost");
	testGoalPost({Board::UP, Board::UP, Board::UP, Board::UP, Board::UP, Board::RIGHT_UP}, true);

	puts("\nTest left corner of lower goalpost");
	testGoalPost({Board::DOWN, Board::DOWN, Board::DOWN, Board::DOWN, Board::DOWN, Board::LEFT_DOWN}, false);

	puts("\nTest middle of lower goalpost");
	testGoalPost({Board::DOWN, Board::DOWN, Board::DOWN, Board::DOWN, Board::DOWN, Board::DOWN}, false);

	puts("\nTest right corner of lower goalpost");
	testGoalPost({Board::DOWN, Board::DOWN, Board::DOWN, Board::DOWN, Board::DOWN, Board::RIGHT_DOWN}, false);

	puts("OK");
	return 0;
}