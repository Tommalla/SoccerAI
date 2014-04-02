#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>
#include <bits/algorithmfwd.h>

#include "AI/AI.hpp"

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

	cin >> command;
	assert(command == "boardsize");
	int w, h;
	cin >> w >> h;
	printOK();

	unique_ptr<AI> ai; //= unique_ptr<AI>(new SomeAI(w, h, params));

	while (getline(cin, line)) {
		stringstream ss(line);
		ss >> command;

		if (command == "play") {
			DirId d;
			ss >> d;
			ai->play(dirMap[d]);
			printNotSupported();
		} else if (command == "gen_move") {
			cout << reverseDirMap[ai->genMove()] << "\n\n";
		} else if (command == "time_left") {
			printNotSupported();
		} else if (command == "undo") {
			printNotSupported();
		} else {
			printNotSupported();
		}

		command.clear();
	}
	return 0;
}