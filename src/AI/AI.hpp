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
	bool isTimeLeft();
	int getFieldsUsed() const;
	int getFields() const;

	std::stack<std::pair<DirId, bool>> history;
	Board board;
	int timeLeft;
	engine::Time timeAvailable;
	bool stopCalculations;

private:
	engine::Time beginTime;
	int operationsCounter;
	const int timeControlOps = 500;
	int fieldsUsed, fields;
	bool alreadyMoved;
};

#endif // AI_HPP