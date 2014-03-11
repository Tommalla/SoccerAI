#include <utility>

namespace engine {
	typedef int Field;
	typedef std::pair<int8_t, int8_t> Direction;

	const Direction directions = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
};