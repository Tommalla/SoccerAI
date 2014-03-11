#include <stack>

#include "../Engine/engine.hpp"

class AI {
public:
	AI(const engine::Coord width, const engine::Coord heigth);

	/**
	 * @brief Acknowledges the playout of the move.
	 */
	virtual void play(const engine::Move& move);
	/**
	 * @brief Generates the next move.
	 * This method **has** to be implemented.
	 */
	virtual engine::Move genMove() = 0;
	/**
	 * @brief Undoes the last move.
	 */
	virtual void undo();
private:
	std::stack<engine::Move> history;
};