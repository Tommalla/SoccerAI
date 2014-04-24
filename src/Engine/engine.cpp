#include <chrono>
#include <cstdarg>
#include <cstdio>
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

