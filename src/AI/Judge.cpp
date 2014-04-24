#include "Judge.hpp"
#include "../Engine/Board.hpp"

using std::shared_ptr;
using namespace engine;

Judge::Judge(const engine::Coord width, const engine::Coord height)
: width{width}
, height{height} {}

bool Judge::play(const AIFactory::AIType& AI1, const AIFactory::AIType& AI2, const engine::Time& roundTime) const {
	shared_ptr<AI> ai[2] = {AIFactory::create(AI1, width, height), AIFactory::create(AI2, width, height)};
	Board board(width, height);
	Time t[2], beginTime, endTime;
	t[0] = t[1] = 0;

	DirId move;
	for (int id = 0; !board.isGameFinished();) {
		beginTime = getTime();
		ai[id]->setTimeLeft(roundTime - t[id]);
		move = ai[id]->genMove();
		ai[id]->play(move);
		endTime = getTime();

		ai[(id + 1) % 2]->play((DirId)(board.directions.size() - move - 1));

		t[(id + 1) % 2] += getTime() - endTime;
		t[id] += endTime - beginTime;

		for (int i = 0; i < 2; ++i)
			if (t[i] >= roundTime) {
				printf("Timeout!\n");
				return i != 0;
			}

		if (board.play((DirId)(id == 0 ? move : board.directions.size() - move - 1)))
			id = (id + 1) % 2;
	}

	return board.doesRedWin();
}

std::pair< int, int > Judge::compare(AIFactory::AIType AI1, AIFactory::AIType AI2, int battles, const Time& roundTime) const {
	int res[2] = {0, 0};
	for (int t = 0; t < 2; ++t) {
		for (int qty = 0; qty < battles; ++qty)
			if (play(AI1, AI2, roundTime))
				++res[t];

		std::swap(AI1, AI2);
	}
	return {res[0], battles - res[1]};
}


