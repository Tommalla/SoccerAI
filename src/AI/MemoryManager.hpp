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
	~MemoryManager();

	Status* create(const engine::Hash& hash);
	bool addChildren(Status* node, const size_t& num);
	void reset();
private:
	Status* allocate();
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

template<class Status>
Status* MemoryManager<Status>::create(const engine::Hash& hash) {
	Status* res = allocate();
	res->setHash(hash);
	return res;
}

template<class Status>
bool MemoryManager<Status>::addChildren(Status* node, const size_t& num) {
	if (num > size - end)
		return false;
	node->setChildren(allocate(), num);
	for (size_t i = 0; i < num; ++i)
		(memory + end - 1 + i)->reset();
	end += num - 1;
	return true;
}

template<class Status>
Status* MemoryManager<Status>::allocate() {
	return memory + end++;
}

template<class Status>
void MemoryManager<Status>::reset() {
	end = 0;
}



#endif // MEMORY_MANAGER_HPP
