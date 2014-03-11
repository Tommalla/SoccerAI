#include <memory>

#include "AI.hpp"

namespace AIFactory {
	enum class AIName: char {
		RANDOM,
		ALPHA_BETA
	};

	std::shared_ptr<AI> create(const AIName name);
};
