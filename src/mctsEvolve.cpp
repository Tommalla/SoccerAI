#include <cstdio>
#include <future>
#include <thread>
#include <random>
#include <vector>
#include <memory>

#include "AI/SequentialTreeMCTSAI.hpp"
#include "AI/GraphAlphaBetaAI.hpp"
#include "AI/judge.hpp"

using std::thread;
using std::mt19937_64;
using std::random_device;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::shared_ptr;
using std::vector;
using std::future;
using std::async;
using std::launch;
using std::sort;
using namespace engine;
using namespace judge;

const double maxC = 500.0;
const int maxExpandBorder = 100;
const int numThreads = 3;
const int numMCTS = 6;
const Coord width = 8;
const Coord height = 10;
const int roundTime = 60000;

struct Solution {
	double c;
	size_t expandBorder;
};

Solution createRandomSolution() {
	static mt19937_64 mt{random_device{}()};
	static uniform_int_distribution<size_t> intDist{0, maxExpandBorder};
	static uniform_real_distribution<double> doubleDist{0, maxC};

	Solution res;
	res.c = doubleDist(mt);
	res.expandBorder = intDist(mt);

	return res;
}

int score(const Solution& sol) {
	AIResult res = play(shared_ptr<AI>{new SequentialTreeMCTSAI{width, height, sol.c, sol.expandBorder, AIFactory::defaultMemorySize}},
			    AIFactory::create(AIFactory::AIType::TREE_ALPHA_BETA, width, height),
			    width, height, roundTime);
	int result = res.moves + res.aiMoves;
	if (res.won)
		result += 1000;
	else {
		result -= 100;
		if (res.timeout)
			result -= 1000;
	}

	return result;
}

Solution xBreed(const Solution& sol1, int score1, const Solution& sol2, int score2) {
	Solution res;
	if (score1 + score2 == 0)
		score1++;
	res.c = (sol1.c * score1 + sol2.c * score2) / (score1 + score2);
	res.expandBorder = (sol1.expandBorder * score1 + sol2.expandBorder * score2) / (score1 + score2);
	return res;
}

Solution mutate(Solution sol) {
	static mt19937_64 mt{random_device{}()};
	static uniform_real_distribution<double> doubleDist{0, 0.2};
	static uniform_int_distribution<int> intDist{0, 1};

	double cP = doubleDist(mt);
	int cSign = (intDist(mt) == 0) ? -1 : 1;
	double expandBorderP = doubleDist(mt);
	int expandBorderSign = (intDist(mt) == 0) ? -1 : 1;

	sol.c += sol.c * cP * cSign;
	sol.expandBorder += sol.expandBorder * expandBorderP * expandBorderSign;
	return sol;
}

int main () {
	Solution sol[numMCTS];
	int id[numMCTS];
	int scores[numMCTS];
	future<int> f[numMCTS];
	for (int i = 0; i < numMCTS; ++i) {
		sol[i] = createRandomSolution();
		id[i] = i;
	}

	for (int generation = 0; sol[0].expandBorder != sol[1].expandBorder || round(sol[0].c) != round(sol[1].c); ++generation, puts("")) {
		printf("> Generation %d\nStarting threads...\n", generation);
		int j = 0;
		for (int i = 0, num = 0; i < numMCTS; ++i) {
			if (num >= numThreads) {
				f[j].wait();
				printf("Judging %d has finished!\n", j);
				++j;
				--num;
			}

			if (num < numThreads) {
				f[i] = async(launch::async, score, sol[i]);
				++num;
			}
		}

		while (j < numMCTS) {
			f[j].wait();
			printf("Judging %d has finished!\n", j);
			++j;
		}

		for (j = 0; j < numMCTS; ++j)
			scores[j] = f[j].get();

		sort(id, id + numMCTS, [&](const int& a, const int& b){ return scores[a] > scores[b];});
		printf("Solutions with scores:\n");
		for (int i = 0; i < numMCTS; ++i)
			printf("(%d, %lf, %lu)\n", scores[id[i]], sol[id[i]].c, sol[id[i]].expandBorder);

		//create a new generation
		Solution next[numMCTS];
		int i = 0;
		for (;i < 3; ++i)
			next[i] = xBreed(sol[id[0]], scores[id[0]], sol[id[i + 1]], scores[id[i + 1]]);
		for (; i < 4; ++i)
			next[i] = mutate(sol[id[i - 3]]);
		next[i++] = createRandomSolution();
		next[i] = createRandomSolution();
	}

}