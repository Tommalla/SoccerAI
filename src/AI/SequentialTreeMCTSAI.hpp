#ifndef SEQUENTIAL_TREE_MCTSAI_HPP
#define SEQUENTIAL_TREE_MCTSAI_HPP
#include "MCTSAI.hpp"
#include "Status.hpp"

class SequentialTreeMCTSAI : public MCTSAI {
public:
	SequentialTreeMCTSAI(const engine::Coord width, const engine::Coord height, const size_t& expandBorder,
			     const size_t& memorySize);

protected:
	virtual DirId generateMove();
	virtual void resetMemory();
	virtual void expand(Board& s, MCTSStatus* node);
	virtual MCTSStatus* pickSon(Board& s, MCTSStatus* node) const;

	ArrayMemoryManager<TreeMCTSStatus> memoryManager;
};

#endif // SEQUENTIAL_TREE_MCTSAI_HPP