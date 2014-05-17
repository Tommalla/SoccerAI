#ifndef SEQUENTIAL_TREE_MCTSAI_HPP
#define SEQUENTIAL_TREE_MCTSAI_HPP
#include "MCTSAI.hpp"
#include "Status.hpp"

class SequentialTreeMCTSAI : public MCTSAI {
public:
	SequentialTreeMCTSAI(const engine::Coord width, const engine::Coord height, const double& c, const size_t& expandBorder,
			     const size_t& memorySize);

protected:
	virtual DirId generateMove();
	virtual void resetMemory();
	virtual void expand(Board& s, MCTSStatus* node);
	virtual std::pair<MCTSStatus*, DirId> pickSon(Board& s, MCTSStatus* node) const;
	virtual bool isLeaf(Board& s, MCTSStatus* node);

	ArrayMemoryManager<TreeMCTSStatus> memoryManager;
};

#endif // SEQUENTIAL_TREE_MCTSAI_HPP