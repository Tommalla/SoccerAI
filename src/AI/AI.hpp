#ifndef AI_HPP
#define AI_HPP
#include <stack>

#include "../Engine/engine.hpp"
#include "../Engine/Board.hpp"

class AI {
public:
	AI(const engine::Coord width, const engine::Coord height);
	virtual ~AI() {}

	/**
	 * @brief Acknowledges the playout of the move.
	 */
	virtual void play(const DirId& move);
	/**
	 * @brief Generates the next move.
	 * This method **has** to be implemented.
	 */
	DirId genMove();
	/**
	 * @brief Undoes the last move.
	 */
	virtual void undo();
	/**
	 * @brief Sets the amount of time left in some arbitrary (yet common for all AIs) unit.
	 */
	virtual void setTimeLeft(const int time);

protected:
	virtual DirId generateMove() = 0;

	std::stack<std::pair<DirId, bool>> history;
	Board board;
	int timeLeft, lastTimeLeft, lastMoveTime;
	engine::Time timeAvailable;
	int fieldsUsed, fields;

private:
	bool alreadyMoved;
};

#endif // AI_HPP