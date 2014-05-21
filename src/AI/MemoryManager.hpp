#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP
#include <cstddef>

#include "../Engine/engine.hpp"

template<class Status>
class MemoryManager {
public:
	MemoryManager(const size_t& size);
	MemoryManager(const MemoryManager& other) = delete;
	MemoryManager(MemoryManager&& other) = delete;
	MemoryManager& operator=(const MemoryManager& other) = delete;
	MemoryManager&& operator=(MemoryManager&& other) = delete;
	virtual ~MemoryManager();

protected:
	size_t end;
	const size_t size;
	Status* memory;
};

template<class Status>
MemoryManager<Status>::MemoryManager(const size_t& size)
: end{0}
, size{size}
, memory{new Status[size]} {}

template<class Status>
MemoryManager<Status>::~MemoryManager() {
	delete[] memory;
}

#endif // MEMORY_MANAGER_HPP