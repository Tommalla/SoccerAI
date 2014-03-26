#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

#include "AI/AI.hpp"

using namespace std;

inline void printOK() {
	cout << "=\n\n";
}

inline void printNotSupported() {
	cout << "?\n\n";
}

int main() {
	string line;
	string command;

	cin >> command;
	assert(command == "boardsize");
	int w, h;
	cin >> w >> h;
	printOK();

	while (getline(cin, line)) {
		stringstream ss(line);
		ss >> command;

		if (command == "play") {
			printNotSupported();
		} else if (command == "gen_move") {
			printNotSupported();
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