#include "SequentialTreeMCTSAI.hpp"

SequentialTreeMCTSAI::SequentialTreeMCTSAI(const engine::Coord width, const engine::Coord height, const size_t& expandBorder, const size_t& memorySize)
: MCTSAI{width, height, expandBorder, memorySize} {}

DirId SequentialTreeMCTSAI::generateMove() {
	MCTSStatus* root = createStatus();
	expand(board, root);
	while (!stopCalculations)
		playout(board, root);

	MCTSStatus* iter = root->getFirstChild();
	MCTSStatus* res = iter;
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

MCTSStatus* SequentialTreeMCTSAI::createStatus() {
	return memoryManager.allocate();
}

void SequentialTreeMCTSAI::resetMemory() {
	memoryManager.reset();
}
