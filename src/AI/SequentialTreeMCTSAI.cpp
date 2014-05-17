#include <cassert>
#include <stack>
#include <utility>

#include "SequentialTreeMCTSAI.hpp"

using namespace engine;

SequentialTreeMCTSAI::SequentialTreeMCTSAI(const Coord width, const Coord height, const double& c, const size_t& expandBorder, const size_t& memorySize)
: MCTSAI{width, height, c, expandBorder, memorySize}
, memoryManager{memorySize} {}

DirId SequentialTreeMCTSAI::generateMove() {
	TreeMCTSStatus* root = memoryManager.allocate();
	expand(board, root);
	while (!stopCalculations)
		playout(board, root);

	TreeMCTSStatus* iter = root->getFirstChild();
	TreeMCTSStatus* res = iter;
	size_t num = root->getNumChildren();
	double best = 0.0;
	for (size_t i = 0; i < num; ++i, ++iter) {
		double tmp = (double)iter->wins / iter->plays;
		engine::printDebug("Possible: %d -> %.3lf (%lu/%lu)\n", iter->lastMoveId, tmp, iter->wins, iter->plays);
		if (tmp > best) {
			best = tmp;
			res = iter;
		}
	}

	return res->lastMoveId;
}

void SequentialTreeMCTSAI::resetMemory() {
	memoryManager.reset();
}

void SequentialTreeMCTSAI::expand(Board& s, MCTSStatus* node) {
	auto moves = s.getMoves();

	TreeMCTSStatus* v = static_cast<TreeMCTSStatus*>(node);

	bool added = memoryManager.addChildren(v, moves.size());
	assert(added);
	TreeMCTSStatus* son = v->getFirstChild();
	for (size_t id = 0; id < moves.size(); ++id, ++son)
		son->lastMoveId = moves[id];
}

std::pair<MCTSStatus*, DirId> SequentialTreeMCTSAI::pickSon(Board& s, MCTSStatus* node) const {
	TreeMCTSStatus* v = static_cast<TreeMCTSStatus*>(node);
	TreeMCTSStatus* iter = v->getFirstChild();
	TreeMCTSStatus* res = iter;
	double tmp, bestVal = s.isRedActive() ? -INF : INF;
	size_t num = v->getNumChildren();

	for (size_t id = 0; id < num; ++id, ++iter) {
		tmp = UCB(s, iter, node);
		if ((s.isRedActive() ? tmp > bestVal : tmp < bestVal)) {
			bestVal = tmp;
			res = iter;
		}
	}

	return {res, res->lastMoveId};
}

bool SequentialTreeMCTSAI::isLeaf(Board& s, MCTSStatus* node) {
	TreeMCTSStatus* v = static_cast<TreeMCTSStatus*>(node);
	return v->getFirstChild() == nullptr;
}

