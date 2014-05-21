#ifndef PSEUDO_DYNAMIC_ARRAY_MEMORY_MANAGER_HPP
#define PSEUDO_DYNAMIC_ARRAY_MEMORY_MANAGER_HPP

#include <cassert>

#include "ArrayMemoryManager.hpp"

/**
 * @brief A class that allows for 'dynamic' memory allocation from a pool of predefined size.
 *
 * @warning This class cannot be used polymorphically because of the lack of virtual methods because of templatization.
 *
 */
template<class Status>
class PseudoDynamicArrayMemoryManager: public ArrayMemoryManager<Status> {
protected:
// 	using ArrayMemoryManager<Status>::ArrayMemoryManager;
	using ArrayMemoryManager<Status>::size;
	using ArrayMemoryManager<Status>::memory;

public:
	PseudoDynamicArrayMemoryManager(const size_t& size)
	: ArrayMemoryManager<Status>{size}
	, available{new Status*[size]}
	, availEnd{-1} {
		for (size_t i = 0; i < size; ++i)
			available[++availEnd] = &(memory[i]);
	}

	virtual ~PseudoDynamicArrayMemoryManager() {
		delete[] available;
	}

	Status* allocate();
	void deallocate(Status* node);


private:
	Status** available;
	int availEnd;

};


template<class Status>
Status* PseudoDynamicArrayMemoryManager<Status>::allocate() {
	assert(availEnd >= 0);
	Status* res = available[availEnd--];
	res->reset();
	return res;
}

template<class Status>
void PseudoDynamicArrayMemoryManager<Status>::deallocate(Status* node) {
	assert(availEnd + 1 < size);
	available[++availEnd] = node;
}

#endif // PSEUDO_DYNAMIC_ARRAY_MEMORY_MANAGER_HPP