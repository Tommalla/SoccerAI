#ifndef MCTSAI_HPP
#define MCTSAI_HPP
#include "AI.hpp"
#include "Status.hpp"
#include "ArrayMemoryManager.hpp"

class MCTSAI: public AI {
public:
	MCTSAI(const engine::Coord width, const engine::Coord height, const size_t& expandBorder,
		const size_t& memorySize);
	virtual void play(const DirId& move);
	virtual void undo();

protected:
	virtual DirId generateMove() = 0;

	//getting statuses (nodes)
	virtual void resetMemory() = 0;

	virtual bool isLeaf(Board& s, MCTSStatus* node) = 0;

	//MCTS logic
	/**
	 * @brief Performs a Monte-Carlo playout in node with state s.
	 * @return True if red wins. False otherwise.
	 */
	bool playout(Board& s, MCTSStatus* node);
	/**
	 * @brief A subprocedure of playout. Picks the best son and runs playout on it.
	 * Assumption: node is not a leaf.
	 *
	 * @return The result of playout.
	 */
	inline bool advance(Board& s, MCTSStatus* node);
	/**
	 * @brief Performs a random playout beginning from state s.
	 * @return True if red wins. False otherwise.
	 */
	bool randomPlayout(Board& s);
	/**
	 * @brief Expands leaf node with state s.
	 */
	virtual void expand(Board& s, MCTSStatus* node) = 0;
	virtual std::pair<MCTSStatus*, DirId> pickSon(Board& s, MCTSStatus* node) const = 0;

	double UCB(Board& s, MCTSStatus* node, MCTSStatus* parent) const;

	const size_t expandBorder;
};

#endif // MCTSAI_HPP