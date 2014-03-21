#include <cstdio>
#include <cassert>
#include <string>
#include <vector>

#include "../Board.hpp"
#include "../engine.hpp"

using namespace engine;
using namespace std;

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

	puts("OK");
	return 0;
}