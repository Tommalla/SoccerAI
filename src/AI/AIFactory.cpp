#include <algorithm>

#include "AIFactory.hpp"
#include "AlphaBetaAI.hpp"
#include "RandomAI.hpp"
#include "objectiveFunctions.hpp"

using std::shared_ptr;
using engine::Coord;

shared_ptr<AI> AIFactory::create(const AIType& type, const Coord width, const Coord height) {
	shared_ptr<AI> res;

	switch (type) {
		case AIType::RANDOM:
			res = shared_ptr<AI>(new RandomAI(width, height));
			break;
		case AIType::ALPHA_BETA:
			res = shared_ptr<AI>(new AlphaBetaAI(width, height, objectiveFunctions::simpleDistance));
			break;
		default:
			throw WrongAITypeException();
	}

	return res;
}

AIFactory::AIType AIFactory::stringToType(std::string str) {
	std::transform(begin(str), end(str), begin(str), ::tolower);

	if (str[0] == 'r')
		return AIType::RANDOM;

	if (str[0] == 'a')
		return AIType::ALPHA_BETA;

	return AIType::WRONG;
}

