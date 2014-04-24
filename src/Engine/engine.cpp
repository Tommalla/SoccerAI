#include <chrono>
#include "engine.hpp"

engine::Time engine::getTime() {
	// Magic...
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
