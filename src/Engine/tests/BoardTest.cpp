#include <cstdio>
#include <cassert>

#include "../Board.hpp"
#include "../engine.hpp"

using namespace engine;

int main() {
	Board b(8, 12);
	assert(b.getField() == 6 * 8 + 4);
	b.play(b.directions[0]);
	assert(b.fieldToPosition(b.getField()) == Position(3, 5));
	assert(b.getMoves().size() == b.directionsQty - 1);

	puts("OK");
	return 0;
}