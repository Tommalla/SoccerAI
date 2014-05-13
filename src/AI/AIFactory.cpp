#include <algorithm>

#include "AIFactory.hpp"
#include "TreeAlphaBetaAI.hpp"
#include "GraphAlphaBetaAI.hpp"
#include "SequentialTreeMCTSAI.hpp"
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
		case AIType::TREE_ALPHA_BETA:
			res = shared_ptr<AI>(new TreeAlphaBetaAI(width, height, objectiveFunctions::simpleDistance));
			break;
		case AIType::GRAPH_ALPHA_BETA:
			res = shared_ptr<AI>(new GraphAlphaBetaAI(width, height, objectiveFunctions::simpleDistance, 10000000));
			break;
		case AIType::MCTS_SEQUENTIAL_TREE:
			res = shared_ptr<AI>(new SequentialTreeMCTSAI(width, height, 30, 100000));
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

	if (str[0] == 't')
		return AIType::TREE_ALPHA_BETA;

	if (str[0] == 'g')
		return AIType::GRAPH_ALPHA_BETA;

	if (str[0] == 'm')
		return AIType::MCTS_SEQUENTIAL_TREE;

	return AIType::WRONG;
}

