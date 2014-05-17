#ifndef JUDGE_HPP
#define JUDGE_HPP
#include "AIFactory.hpp"

class Judge {
public:
	struct AIResult {
		int moves;	// single edges in the whole game
		int aiMoves;	// single edges made by this aI
		bool won;	// has AI won?
		bool timeout;	// has anybody had a timeout?
	};

	Judge(const engine::Coord width, const engine::Coord height);

	/**
	 * @brief Plays one battle between AI1 and AI2.
	 * @return true if AI1 won, false otherwise
	 */
	AIResult play(const AIFactory::AIType& AI1, const AIFactory::AIType& AI2, const engine::Time& roundTime) const;
	/**
	 * @brief Compares AI1 with AI2 by playing ``battles`` battles between them and then the same amount
	 * with different order of players.
	 *
	 * @return std::pair< int, int >: (battles won by AI1 in normal order, battles won by AI1 in reverse order)
	 */
	std::pair<int, int> compare(AIFactory::AIType AI1, AIFactory::AIType AI2, int battles, const engine::Time& roundTime) const;

private:
	const engine::Coord width, height;
};

#endif