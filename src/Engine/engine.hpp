#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <cstdint>
#include <utility>

namespace engine {
	typedef int8_t Coord;
	typedef int Field;
	typedef Field Move;
	typedef std::pair<Coord, Coord> Position;
	typedef long long int Time;

	/**
	 * @brief Returns current system time in milliseconds
	 */
	Time getTime();

	const int INF = 99999999;
};

#endif