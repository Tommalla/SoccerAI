#include <random>
#include "MCTSAI.hpp"

using std::get;
using namespace engine;

MCTSAI::MCTSAI(const Coord width, const Coord height, const double& c, const size_t& expandBorder, const size_t& memorySize)
: AI{width, height}
, expandBorder{expandBorder}
, c{c} {}


void MCTSAI::play(const DirId& move) {
	AI::play(move);
	resetMemory();
}

void MCTSAI::undo() {
	AI::undo();
	resetMemory();
}

bool MCTSAI::playout(Board& s, MCTSStatus* node, MCTSStatus* edge) {
	node->plays++;
	if (edge != nullptr)
		edge->plays++;
	bool res = false;

	if (!isTimeLeft())
		return res;

	if (s.isGameFinished())
		res = s.doesRedWin();
	else {
		if (isLeaf(s, node)) {	//leaf
			if (node->plays >= expandBorder) {
				expand(s, node);
				res = advance(s, node);
			} else
				res = randomPlayout(s);
		} else
			res = advance(s, node);
	}

	if (res || stopCalculations) {	//no virtual loss at the end of time
		node->wins++;
		if (edge != nullptr)
			edge->wins++;
	}
	return res;
}

inline bool MCTSAI::advance(Board& s, MCTSStatus* node) {
	auto son = pickSon(s, node);
	bool change = s.play(get<2>(son));
	bool res = playout(s, get<0>(son), get<1>(son));
	s.undo(get<2>(son), change);
	return res;
}

bool MCTSAI::randomPlayout(Board& s) {
	//TODO copy Board vs moves history
	static std::mt19937 mt{std::random_device{}()};

	std::stack<std::pair<DirId, bool>> playHistory;
	std::pair<DirId, bool> elem;
	std::vector<DirId> moves;
	bool result;
	int id;

	while (!s.isGameFinished() && !s.canWinInOneMove()) {
		if (!isTimeLeft())
			break;
		moves = s.getMoves();
		id = mt() % moves.size() /*moves.size() == 1 ? 0 : dist[moves.size() - 2](mt)*/;
		playHistory.push({moves[id], s.play(moves[id])});
	}

	if (s.isGameFinished())
		result = s.doesRedWin();
	else
		result = s.isRedActive();

	while (!playHistory.empty()) {
		elem = playHistory.top();
		s.undo(elem.first, elem.second);
		playHistory.pop();
	}

	return result;
}

double MCTSAI::UCB(Board& s, MCTSStatus* node, MCTSStatus* parent) const {
	double minMax = c * (s.isRedActive() ? 1.0 : -1.0);
	if (node->plays == 0)
		return minMax * engine::INF;
	return (double)node->wins / node->plays +  minMax * sqrt(log(parent->plays) / node->plays);
}

