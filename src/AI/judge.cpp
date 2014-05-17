#include "judge.hpp"
#include "../Engine/Board.hpp"

using std::shared_ptr;
using namespace engine;

judge::AIResult judge::play(const shared_ptr< AI >& AI1, const shared_ptr< AI >& AI2, const Coord& width, const Coord& height, const Time& roundTime) {
	shared_ptr<AI> ai[2] = {AI1, AI2};
	Board board(width, height);
	Time t[2], beginTime, endTime;
	t[0] = t[1] = 0;
	AIResult res;
	res.moves = res.aiMoves = 0;
	res.won = res.timeout = false;

	DirId move;
	for (int id = 0; !board.isGameFinished();) {
		beginTime = getTime();
		ai[id]->setTimeLeft(roundTime - t[id]);

		move = ai[id]->genMove();
		ai[id]->play(move);

		endTime = getTime();

		res.moves++;
		if (id == 0)
			res.aiMoves++;

		ai[(id + 1) % 2]->play((DirId)(board.directions.size() - move - 1));

		t[(id + 1) % 2] += getTime() - endTime;
		t[id] += endTime - beginTime;

		for (int i = 0; i < 2; ++i)
			if (t[i] >= roundTime) {
				res.won = i != 0;
				res.timeout = true;
				printf("Timeout!\n");
				return res;
			}

		if (board.play((DirId)(id == 0 ? move : board.directions.size() - move - 1)))
			id = (id + 1) % 2;
	}

	res.won = board.doesRedWin();

	return res;
}

std::pair< int, int > judge::compare(AIFactory::AIType AI1, AIFactory::AIType AI2, const Coord& width, const Coord& height, int battles, const Time& roundTime) {
	int res[2] = {0, 0};
	for (int t = 0; t < 2; ++t) {
		for (int qty = 0; qty < battles; ++qty)
			if (play(AIFactory::create(AI1, width, height), AIFactory::create(AI2, width, height), width, height, roundTime).won)
				++res[t];

		std::swap(AI1, AI2);
	}
	return {res[0], battles - res[1]};
}


