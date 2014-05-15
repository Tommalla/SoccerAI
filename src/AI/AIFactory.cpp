#include <algorithm>

#include "AIFactory.hpp"
#include "TreeAlphaBetaAI.hpp"
#include "GraphAlphaBetaAI.hpp"
#include "SequentialTreeMCTSAI.hpp"
#include "GraphMapMCTSAI.hpp"
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
			res = shared_ptr<AI>(new GraphAlphaBetaAI(width, height, objectiveFunctions::simpleDistance, defaultMemorySize));
			break;
		case AIType::MCTS_SEQUENTIAL_TREE:
			res = shared_ptr<AI>(new SequentialTreeMCTSAI(width, height, 30, defaultMemorySize));
			break;
		case AIType::MCTS_GRAPH_MAP:
			res = shared_ptr<AI>(new GraphMapMCTSAI(width, height, 30, defaultMemorySize));
			break;
		default:
			throw WrongAITypeException();
	}

	return res;
}

AIFactory::AIType AIFactory::stringToType(std::string str) {
	std::transform(begin(str), end(str), begin(str), ::tolower);

	if (str[0] == 'r' || str == "random")
		return AIType::RANDOM;

	if (str[0] == 't' || str == "treealphabeta")
		return AIType::TREE_ALPHA_BETA;

	if (str[0] == 'g' || str == "graphalphabeta")
		return AIType::GRAPH_ALPHA_BETA;

	if (str[0] == 's' || str == "sequentialtreemcts")
		return AIType::MCTS_SEQUENTIAL_TREE;

	if (str[0] == 'm' || str == "graphmapmcts")
		return AIType::MCTS_GRAPH_MAP;

	return AIType::WRONG;
}

