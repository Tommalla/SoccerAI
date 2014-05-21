#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>
#include <bits/algorithmfwd.h>

#include "AI/AI.hpp"
#include "AI/RandomAI.hpp"
#include "AI/AlphaBetaAI.hpp"
#include "AI/objectiveFunctions.hpp"
#include "AI/AIFactory.hpp"

// #define RANDOM_AI
// #define TREE_ALPHA_BETA_AI
// #define GRAPH_ALPHA_BETA_AI
// #define SEQUENTIAL_TREE_MCTS_AI
// #define GRAPH_MAP_MCTS_AI

using namespace std;

inline void printOK() {
	cout << "=\n\n";
}

inline void printNotSupported() {
	cout << "?\n\n";
}

DirId dirMap[] = {Board::RIGHT, Board::RIGHT_UP, Board::UP, Board::LEFT_UP, Board::LEFT,
		  Board::LEFT_DOWN, Board::DOWN, Board::RIGHT_DOWN};
DirId reverseDirMap[8];


int main() {
	for (int i = 0; i < 8; ++i)
		reverseDirMap[dirMap[i]] = i;

	string line;
	string command;
	int w, h, t;

	{
		getline(cin, line);
		stringstream ss(line);
		ss >> command;
		assert(command == "boardsize");
		ss >> w >> h;
		h += 2;
		printOK();
	}

	shared_ptr<AI> ai;
	#ifdef RANDOM_AI
	ai = AIFactory::create(AIFactory::AIType::RANDOM, w, h);
	#endif
	#ifdef TREE_ALPHA_BETA_AI
	ai = AIFactory::create(AIFactory::AIType::TREE_ALPHA_BETA, w, h);
	#endif
	#ifdef GRAPH_ALPHA_BETA_AI
	ai = AIFactory::create(AIFactory::AIType::GRAPH_ALPHA_BETA, w, h);
	#endif
	#ifdef SEQUENTIAL_TREE_MCTS_AI
	ai = AIFactory::create(AIFactory::AIType::MCTS_SEQUENTIAL_TREE, w, h);
	#endif
	#ifdef GRAPH_MAP_MCTS_AI
	ai = AIFactory::create(AIFactory::AIType::MCTS_GRAPH_MAP, w, h);
	#endif
	#ifdef GRAPH_TRANSPOSITION_TABLE_MCTS_AI
	ai = AIFactory::create(AIFactory::AIType::MCTS_GRAPH_TT, w, h);
	#endif

	while (getline(cin, line)) {
		stringstream ss(line);
		ss >> command;

		if (command == "play") {
			DirId d;
			ss >> d;
			ai->play(dirMap[d]);
			printOK();
		} else if (command == "genmove") {
			DirId res = ai->genMove();
			cout << "= " << reverseDirMap[res] << "\n\n";
			ai->play(res);
		} else if (command == "timeleft") {
			ss >> t;
			ai->setTimeLeft(t);
			printOK();
		} else if (command == "undo") {
			printNotSupported();
		} else if (command.empty() == false) {
			printNotSupported();
		}

		command.clear();
	}
	return 0;
}