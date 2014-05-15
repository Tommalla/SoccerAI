#undef NDEBUG

#include <cstdio>
#include <set>
#include <ctime>
#include <cstdlib>
#include <cassert>

#include "../Board.hpp"

using namespace std;

int main() {
	srand(time(NULL));
	for (int i = 0; i < 100000; ++i) {
		Board b{8, 10};
		set<engine::Hash> s;
		s.insert(b.getHash());
		while (!b.isGameFinished()) {
			auto moves = b.getMoves();
			b.play(moves[rand() % moves.size()]);
			assert(s.find(b.getHash()) == s.end());
			s.insert(b.getHash());
		}
	}
	return 0;
}