#include <cstdint>

#include <utility>

namespace engine {
	typedef int8_t Coord;
	typedef int Field;
	typedef std::pair<Coord, Coord> Move;

	const Move directions[] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
};