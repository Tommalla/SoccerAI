#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>

#include "engine.hpp"

typedef int16_t DirId;

/**
 * @brief Represents a board in the game.
 * Has to be able to perform moves and return info about the state of the game.
 * It needs to remember the last player.
 *
 * The coordinates on the Board start from (1,1) (left upper corner)
 *
 * This class uses assertions heavily to assure the correctness. For performance,
 * compile with -DNDEBUG.
 *
 */
class Board {
public:
	Board(engine::Coord width, engine::Coord height);
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
	bool play(const DirId moveId);
	/**
	 * @brief Undoes a move if it is possible that it was the last move done.
	 */
	void undo(DirId moveId, const bool changePlayer = false);
	/**
	 * @brief Returns the Field the ball is currently on.
	 */
	engine::Field getField() const;
	/**
	 * @brief Returns the Position the ball is currently on.
	 */
	engine::Position getPosition() const;
	/**
	 * @brief Returns moves available from the current position.
	 */
	std::vector<DirId> getMoves() const;
	/**
	 * @brief Returns the board hash after performing move moveId.
	 */
	engine::Hash getHashAfter(const DirId& moveId) const;
	/**
	 * @brief Returns a [supposedly] unique hash for transition from the
	 * current state of the board using move moveId.
	 */
	engine::Hash getMoveHash(const DirId& moveId) const;
	/**
	 * @brief True if the active player is Red. False otherwise.
	 * Invariant: either Blue or Red player is active.
	 */
	bool isRedActive() const;
	engine::Field positionToField(const engine::Position& pos) const;
	engine::Position fieldToPosition(const engine::Field field) const;
	/**
	 * @brief Returns true if the game is finished.
	 */
	bool isGameFinished() const;
	bool doesRedWin() const;
	/**
	 * @brief Returns true if the player can go from current position using dir.
	 */
	bool canGo(const DirId dirId) const;

	engine::Coord getWidth() const;
	engine::Coord getHeight() const;

	/**
	 * @brief Changes the active player.
	 */
	void changeActivePlayer();

	/**
	 * @brief Returns the current hash of Board.
	 */
	engine::Hash getHash() const;
	/**
	 * @brief Returns true if the current player can win in one move.
	 */
	bool canWinInOneMove() const;

	const std::vector<engine::Move> directions;
	const static DirId LEFT_UP = 0;
	const static DirId UP = 1;
	const static DirId RIGHT_UP = 2;
	const static DirId LEFT = 3;
	const static DirId RIGHT = 4;
	const static DirId LEFT_DOWN = 5;
	const static DirId DOWN = 6;
	const static DirId RIGHT_DOWN = 7;

private:
	/**
	 * @brief Returns the id of direction between 2 points. -1 if points aren't adjacent.
	 */
	inline DirId getDirectionBetween(const engine::Field a, const engine::Field b) const;
	/**
	 * @brief Connects field a with some other using the edge dirId.
	 */
	void connect(const engine::Field a, const DirId dirId);
	/**
	 * @brief Returns true if x is a valid field (it's on the map).
	 * @return bool
	 */
	bool isValid(const engine::Field x) const;
	void addGuardAt(engine::Field x);
	void tryConnect(const engine::Field x, const DirId dirId);
	/**
	 * @brief Returns true if there is an edge between fields a and b.
	 */
	bool isEdgeBetween(const engine::Field a, const engine::Field b) const;
	bool isEdgeFrom(const engine::Field a, const DirId dirId) const;
	/**
	 * @brief This method checks if the game is finished in its' current state and if so, sets
	 * the appropriate player as the winner.
	 *
	 * @return True if game is finished.
	 */
	bool updateGameFinished();

	uint8_t* edges;
	engine::Hash* hash;
	engine::Hash playerRedHash;
	engine::Hash* moveHash;
	engine::Hash currentHash;
	engine::Field position;
	const engine::Coord width, height;
	bool playerRed;
	bool redWins;
	bool gameFinished;
};

#endif // BOARD_HPP
