#ifndef JUDGE_HPP
#define JUDGE_HPP
#include "AIFactory.hpp"

namespace judge {
	struct AIResult {
		int moves;	// single edges in the whole game
		int aiMoves;	// single edges made by this aI
		bool won;	// has AI won?
		bool timeout;	// has anybody had a timeout?
	};

	/**
	 * @brief Plays one battle between AI1 and AI2.
	 * @return true if AI1 won, false otherwise
	 */
	AIResult play(const std::shared_ptr< AI >& AI1, const std::shared_ptr< AI >& AI2, const engine::Coord& width, const engine::Coord& height, const engine::Time& roundTime);

	/**
	 * @brief Compares AI1 with AI2 by playing ``battles`` battles between them and then the same amount
	 * with different order of players.
	 *
	 * @return std::pair< int, int >: (battles won by AI1 in normal order, battles won by AI1 in reverse order)
	 */
	std::pair<int, int> compare(AIFactory::AIType AI1, AIFactory::AIType AI2, const engine::Coord& width, const engine::Coord& height, int battles, const engine::Time& roundTime);
};

#endif