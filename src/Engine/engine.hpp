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

	/**
	 * @brief Returns current system time in milliseconds
	 */
	Time getTime();
	void printDebug(const char *format, ...);

	const int INF = 99999999;
};

#endif