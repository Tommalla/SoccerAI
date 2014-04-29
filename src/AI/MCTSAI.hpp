#ifndef MCTSAI_HPP
#define MCTSAI_HPP

#include "AI.hpp"
#include "Status.hpp"
#include "MemoryManager.hpp"

class MCTSAI: public AI {
public:
	MCTSAI(const engine::Coord width, const engine::Coord height, const size_t& expandBorder,
		const size_t& memorySize);
	virtual void play(const DirId& move);
	virtual void undo();

protected:
	virtual DirId generateMove() = 0;

	//getting statuses (nodes)
	virtual MCTSStatus* getOrCreateStatus(const engine::Hash& hash) = 0;
	virtual void resetMemory() = 0;

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
	void expand(Board& s, MCTSStatus* node);

	MCTSStatus* pickSon(Board& s, MCTSStatus* node) const;

	const size_t expandBorder;
	MemoryManager<MCTSStatus> memoryManager;
private:
	double UCB(Board& s, MCTSStatus* node, MCTSStatus* parent) const;
};

#endif // MCTSAI_HPP