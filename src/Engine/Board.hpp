#include <vector>

#include "engine.hpp"

/**
 * @brief Represents a board in the game.
 * Has to be able to perform moves and return info about the state of the game.
 * It needs to remember the last player.
 *
 * This class uses assertions heavily to assure the correctness. For performance,
 * compile with -DNDEBUG.
 *
 */
class Board {
public:
	Board(const engine::Coord width, const engine::Coord height);
	Board(const Board& other);
	Board& operator=(const Board& other) = delete;

	~Board();
	/**
	 * @brief Plays the move. If the move's invalid, it will be found
	 * by an assertion (if it's enabled).
	 *
	 * @return True if performing this move finishes the current player's turn.
	 * False otherwise.
	 */
	bool play(const engine::Move move);
	/**
	 * @brief Undoes a move if it is possible that it was the last move done.
	 */
	void undo(const engine::Move move, const bool changePlayer = false);
	/**
	 * @brief Returns the field the ball is currently on.
	 */
	engine::Field getField() const;
	/**
	 * @brief Returns moves available from the current position.
	 */
	std::vector<engine::Move> getMoves() const;
	/**
	 * @brief True if the active player is Red. False otherwise.
	 * Invariant: either Blue or Red player is active.
	 */
	bool isRedActive() const;
	engine::Field positionToField(const engine::Position& pos) const;
	engine::Position fieldToPosition(const engine::Field field) const;

	const std::vector<engine::Move> directions;
    //TODO add const static values for direction names

private:
	/**
	 * @brief Returns the id of direction between 2 points. -1 if points aren't adjacent.
	 */
	inline int getDirectionBetween(const engine::Field a, const engine::Field b) const;
	/**
	 * @brief Returns true if there is an edge between fields a and b.
	 */
	bool isEdgeBetween(const engine::Field a, const engine::Field b) const;
	/**
	 * @brief Connects field a and b with an edge (adequate to move).
	 */
	void connect(const engine::Field a, const engine::Field b);
	/**
	 * @brief Returns true if x is reachable from our current position - it is a
	 * neighbour and there is no edge between us and x and x is a valid position.
	 */
	bool canGoTo(const engine::Field x) const;
	/**
	 * @brief Returns true if x is a valid field (it's on the map).
	 * @return bool
	 */
	bool isValid(const engine::Field x) const;
	/**
	 * @brief Returns true if point is on border.
	 */
	bool isOnBorder(const engine::Field x) const;

	uint8_t* edges;
	engine::Field position;
	const engine::Coord width, height;
	bool playerRed;
};
