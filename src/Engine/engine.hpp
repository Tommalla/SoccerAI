#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <cstdint>
#include <utility>

namespace engine {
	/**
	 * @brief Returns current system time in milliseconds
	 */
	long long int getTime();

	typedef int8_t Coord;
	typedef int Field;
	typedef Field Move;
	typedef std::pair<Coord, Coord> Position;

	const int INF = 99999999;
};

#endif