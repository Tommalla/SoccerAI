#include <stack>

#include "../Engine/engine.hpp"
#include "../Engine/Board.hpp"

#ifndef AI_HPP
#define AI_HPP

class AI {
public:
	AI(const engine::Coord width, const engine::Coord height);

	/**
	 * @brief Acknowledges the playout of the move.
	 */
	virtual void play(const DirId& move);
	/**
	 * @brief Generates the next move.
	 * This method **has** to be implemented.
	 */
	virtual DirId genMove() = 0;
	/**
	 * @brief Undoes the last move.
	 */
	virtual void undo();
protected:
	std::stack<std::pair<DirId, bool>> history;
	Board board;
};

#endif // AI_HPP