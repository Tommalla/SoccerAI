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
	 * @deprecated
	 * @brief Plays the move. If the move's invalid, it will be found
	 * by an assertion (if it's enabled).
	 *
	 * @return True if performing this move finishes the current player's turn.
	 * False otherwise.
	 */
	bool play(const engine::Move move);
	/**
	 * @brief Plays the move. If the move's invalid, it will be found
	 * by an assertion (if it's enabled).
	 *
	 * @return True if performing this move finishes the current player's turn.
	 * False otherwise.
	 */
	bool play(const DirId moveId);
	/**
	 * @deprecated
	 * @brief Undoes a move if it is possible that it was the last move done.
	 */
	void undo(const engine::Move move, const bool changePlayer = false);
	/**
	 * @brief Undoes a move if it is possible that it was the last move done.
	 */
	void undo(const DirId moveId, const bool changePlayer = false);
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
	std::vector<engine::Move> getMoves() const;
	/**
	 * @brief True if the active player is Red. False otherwise.
	 * Invariant: either Blue or Red player is active.
	 */
	bool isRedActive() const;
	engine::Field positionToField(const engine::Position& pos) const;
	engine::Position fieldToPosition(const engine::Field field) const;
	/**
	 * @brief Returns true if there is an edge between fields a and b.
	 */
	bool isEdgeBetween(const engine::Field a, const engine::Field b) const;
	bool isEdgeFrom(const engine::Field a, const DirId dirId) const;

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
	 * @deprecated
	 * @brief Connects field a and b with an edge (adequate to move).
	 */
	void connect(const engine::Field a, const engine::Field b);
	/**
	 * @brief Returns true if the player can go from current position using dir.
	 */
	bool canGo(const DirId dirId) const;
	/**
	 * @brief Returns true if x is a valid field (it's on the map).
	 * @return bool
	 */
	bool isValid(const engine::Field x) const;
	void addGuardAt(engine::Field x);
	void tryConnect(const engine::Field x, const DirId dirId);

	uint8_t* edges;
	engine::Field position;
	const engine::Coord width, height;
	bool playerRed;
};
