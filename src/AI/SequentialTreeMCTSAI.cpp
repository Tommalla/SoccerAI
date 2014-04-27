#include "SequentialTreeMCTSAI.hpp"

SequentialTreeMCTSAI::SequentialTreeMCTSAI(const engine::Coord width, const engine::Coord height, const size_t& expandBorder, const size_t& memorySize)
: MCTSAI{width, height, expandBorder, memorySize} {}

DirId SequentialTreeMCTSAI::generateMove() {
	MCTSStatus* root = getOrCreateStatus(board.getHash());
	expand(board, root);
	for (size_t i = 0; i < 5000; ++i)
		playout(board, root);

	MCTSStatus* iter = root->getFirstChild();
	MCTSStatus* res = iter;
	size_t num = root->getNumChildren();
	double best = 0.0f;
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

MCTSStatus* SequentialTreeMCTSAI::getOrCreateStatus(const engine::Hash& hash) {
	return memoryManager.create(hash);
}

void SequentialTreeMCTSAI::resetMemory() {
	memoryManager.reset();
}



