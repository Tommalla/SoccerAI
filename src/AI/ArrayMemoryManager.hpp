#ifndef ARRAY_MEMORY_MANAGER_HPP
#define ARRAY_MEMORY_MANAGER_HPP
#include "MemoryManager.hpp"

template<class Status>
class ArrayMemoryManager : public MemoryManager<Status> {
protected:
	using MemoryManager<Status>::end;
	using MemoryManager<Status>::size;
	using MemoryManager<Status>::memory;

public:
	ArrayMemoryManager(const size_t& size) : MemoryManager<Status>{size} {}

	bool addChildren(Status* node, const size_t& num);
	Status* allocate();
	void reset();
};

template<class Status>
bool ArrayMemoryManager<Status>::addChildren(Status* node, const size_t& num) {
	if (num > size - end)
		return false;
	node->setChildren(allocate(), num);
	for (size_t i = 0; i < num; ++i)
		resetStatus<Status>(memory + end - 1 + i);
	end += num - 1;
	return true;
}

template<class Status>
Status* ArrayMemoryManager<Status>::allocate() {
	return memory + end++;
}

template<class Status>
void ArrayMemoryManager<Status>::reset() {
	end = 0;
}

#endif // ARRAY_MEMORY_MANAGER_HPP
