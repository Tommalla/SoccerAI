#include "Judge.hpp"
#include "../Engine/Board.hpp"

using std::shared_ptr;

Judge::Judge(const engine::Coord width, const engine::Coord height)
: width{width}
, height{height} {}

bool Judge::play(const AIFactory::AIType& AI1, const AIFactory::AIType& AI2) const {
	shared_ptr<AI> ai[2] = {AIFactory::create(AI1, width, height), AIFactory::create(AI2, width, height)};
	Board board(width, height);

	DirId move;
	for (int id = 0; !board.isGameFinished();) {
		move = ai[id]->genMove();
		ai[id]->play(move);
		ai[(id + 1) % 2]->play((DirId)(board.directions.size() - move - 1));
		if (board.play((DirId)(id == 0 ? move : board.directions.size() - move - 1)))
			id = (id + 1) % 2;
	}

	return board.doesRedWin();
}

std::pair< int, int > Judge::compare(AIFactory::AIType AI1, AIFactory::AIType AI2, int battles) const {
	int res[2] = {0, 0};
	for (int t = 0; t < 2; ++t) {
		for (int qty = 0; qty < battles; ++qty)
			if (play(AI1, AI2))
				++res[t];

		std::swap(AI1, AI2);
	}
	return {res[0], battles - res[1]};
}


