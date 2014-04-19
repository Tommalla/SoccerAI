#include <cstdio>
#include <string>

#include "AI/Judge.hpp"

using namespace std;

int main(const int argc, const char** argv) {
	if (argc != 4)
		puts("Wrong usage! Correct usage is: ./judge <battles quantity> <AI 1 name> <AI 2 name>");
	int battles = atoi(argv[1]);
	Judge j(8, 10);
	auto res = j.compare(AIFactory::stringToType(argv[2]), AIFactory::stringToType(argv[3]), battles);
	printf("\tAI1 Wins | AI2 Wins | AI1 Wins rev | AI2 Wins rev\n%s\t%d\t\t%d\t\t%d\t\t%d\n", argv[2],
	       res.first, battles - res.first, res.second, battles - res.second);
	printf("%s is better!\n", (res.first + res.second > battles) ? argv[2] : ((res.first + res.second == battles) ? "no one" : argv[3]));
	return 0;
}