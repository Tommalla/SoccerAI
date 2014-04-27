#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <cstdint>
#include <utility>

#ifdef NDEBUG
const bool debug = false;
#else
const bool debug = true;
#endif

namespace engine {
	typedef int8_t Coord;
	typedef int Field;
	typedef Field Move;
	typedef std::pair<Coord, Coord> Position;
	typedef long long int Time;
	typedef uint_fast64_t Hash;

	/**
	 * @brief Returns current system time in milliseconds
	 */
	Time getTime();
	void printDebug(const char *format, ...);
	/**
	 * @brief Returns a random number from the range of [0;2^64 - 1]
	 * @return uint_fast64_t
	 */
	uint_fast64_t random();
	/**
	 * @brief The same as engine::random(), only with a predefined, constant seed.
	 */
	uint_fast64_t deterministicRandom();

	/**
	 * @brief Returns the number of set bits in an integer type.
	 */
	template<class Type>
	uint8_t numberOfSetBits(Type i) {
		i = i - ((i >> 1) & 0x55555555);
		i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
		return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
	}

	const int INF = 99999999;
};

#endif