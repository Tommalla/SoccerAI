#ifndef AIFACTORY_HPP
#define AIFACTORY_HPP
#include <memory>

#include "AI.hpp"

namespace AIFactory {
	class WrongAITypeException : public std::exception {
		const char * what () noexcept {
			return "Wrong AI name";
		}
	};

	enum class AIType {
		RANDOM,
		ALPHA_BETA,
		WRONG
	};

	std::shared_ptr<AI> create(const AIFactory::AIType& type, const engine::Coord width, const engine::Coord height);
	AIType stringToType(std::string str);
};

#endif // AIFACTORY_HPP