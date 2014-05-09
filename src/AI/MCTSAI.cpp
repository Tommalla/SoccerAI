#include <cassert>
#include <stack>
#include <utility>
#include <random>
#include "MCTSAI.hpp"

using namespace engine;

MCTSAI::MCTSAI(const Coord width, const Coord height, const size_t& expandBorder, const size_t& memorySize)
: AI{width, height}
, expandBorder{expandBorder}
, memoryManager{memorySize} {}


void MCTSAI::play(const DirId& move) {
	AI::play(move);
	resetMemory();
}

void MCTSAI::undo() {
	AI::undo();
	resetMemory();
}

bool MCTSAI::playout(Board& s, MCTSStatus* node) {
	node->plays++;
	bool res = false;

	if (!isTimeLeft())
		return res;
	
	if (s.isGameFinished())
		res = s.doesRedWin();
	else {
		if (node->getFirstChild() == nullptr) {	//leaf
			if (node->plays >= expandBorder) {
				expand(s, node);
				res = advance(s, node);
			} else
				res = randomPlayout(s);
		} else
			res = advance(s, node);
	}

	if (res || stopCalculations)	//no virtual loss at the end of time
		node->wins++;
	return res;
}

inline bool MCTSAI::advance(Board& s, MCTSStatus* node) {
	MCTSStatus* son = pickSon(s, node);
	bool change = s.play(son->lastMoveId);
	bool res = playout(s, son);
	s.undo(son->lastMoveId, change);
	return res;
}


bool MCTSAI::randomPlayout(Board& s) {
	//TODO copy Board vs moves history
	//TODO random % vs distribution
	static std::mt19937 mt{std::random_device{}()};
	static std::uniform_int_distribution<uint_fast8_t> dist[] = {
		std::uniform_int_distribution<uint_fast8_t>(0, 1),
		std::uniform_int_distribution<uint_fast8_t>(0, 2),
		std::uniform_int_distribution<uint_fast8_t>(0, 3),
		std::uniform_int_distribution<uint_fast8_t>(0, 4),
		std::uniform_int_distribution<uint_fast8_t>(0, 5),
		std::uniform_int_distribution<uint_fast8_t>(0, 6),
		std::uniform_int_distribution<uint_fast8_t>(0, 7)
	};

	std::stack<std::pair<DirId, bool>> playHistory;
	std::pair<DirId, bool> elem;
	std::vector<DirId> moves;
	bool result;
	int id;

	while (!s.isGameFinished()) {
		if (!isTimeLeft())
			break;
		moves = s.getMoves();
		id = moves.size() == 1 ? 0 : dist[moves.size() - 2](mt);
		playHistory.push({moves[id], s.play(moves[id])});
	}

	result = s.doesRedWin();

	while (!playHistory.empty()) {
		elem = playHistory.top();
		s.undo(elem.first, elem.second);
		playHistory.pop();
	}

	return result;
}

void MCTSAI::expand(Board& s, MCTSStatus* node) {
	auto moves = s.getMoves();
	bool change;

	bool added = memoryManager.addChildren(node, moves.size());
	assert(added);
	MCTSStatus* son = node->getFirstChild();
	for (size_t id = 0; id < moves.size(); ++id, ++son) {
		change = s.play(moves[id]);
		son->lastMoveId = moves[id];
		s.undo(moves[id], change);
	}
}

MCTSStatus* MCTSAI::pickSon(Board& s, MCTSStatus* node) const {
	MCTSStatus* iter = node->getFirstChild();
	MCTSStatus* res = iter;
	double tmp, bestVal = s.isRedActive() ? -INF : INF;
	size_t num = node->getNumChildren();

	for (size_t id = 0; id < num; ++id, ++iter) {
		tmp = UCB(s, iter, node);
		if ((s.isRedActive() ? tmp > bestVal : tmp < bestVal)) {
			bestVal = tmp;
			res = iter;
		}
	}

	return res;
}

double MCTSAI::UCB(Board& s, MCTSStatus* node, MCTSStatus* parent) const {
	double minMax = s.isRedActive() ? 1.0 : -1.0;
	if (node->plays == 0)
		return minMax * engine::INF;
	return (double)node->wins / node->plays +  minMax * sqrt(log(parent->plays) / node->plays);
}

