#ifndef SEQUENTIAL_TREE_MCTSAI_HPP
#define SEQUENTIAL_TREE_MCTSAI_HPP
#include "MCTSAI.hpp"

class SequentialTreeMCTSAI : public MCTSAI {
public:
	SequentialTreeMCTSAI(const engine::Coord width, const engine::Coord height, const size_t& expandBorder,
			     const size_t& memorySize);

protected:
	virtual DirId generateMove();
	virtual MCTSStatus* getOrCreateStatus(const engine::Hash& hash);
	virtual void resetMemory();

};

#endif // SEQUENTIAL_TREE_MCTSAI_HPP