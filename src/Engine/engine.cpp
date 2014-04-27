#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <random>
#include "engine.hpp"

engine::Time engine::getTime() {
	// Magic...
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void engine::printDebug(const char* format, ...) {
	if (debug) {
		va_list args;

		va_start (args, format);
		vfprintf(stderr, format, args);
		va_end (args);
	}
}

uint_fast64_t engine::random() {
	static std::mt19937_64 mt{std::random_device{}()};
	return mt();
}

uint_fast64_t engine::deterministicRandom() {
	static std::mt19937_64 mt;
	return mt();
}

