#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>
#include <bits/algorithmfwd.h>

#include "AI/AI.hpp"
#include "AI/RandomAI.hpp"

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

	unique_ptr<AI> ai = unique_ptr<AI>(new RandomAI(w, h));

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
			printNotSupported();
		} else if (command == "undo") {
			printNotSupported();
		} else if (command.empty() == false) {
			printNotSupported();
		}

		command.clear();
	}
	return 0;
}