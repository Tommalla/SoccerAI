#ifndef TRANSPOSITION_TABLE_HPP
#define TRANSPOSITION_TABLE_HPP
#include <algorithm>
#include "MemoryManager.hpp"

template<class Status>
class TranspositionTable : public MemoryManager<Status> {
	using MemoryManager<Status>::end;
	using MemoryManager<Status>::size;
	using MemoryManager<Status>::memory;
	typedef std::function<double(Status*)> ValueFunction;
public:
	TranspositionTable(const size_t& size, const ValueFunction& stateValue);
	std::pair< bool, Status* > getOrCreate(const engine::Hash& hash);
	int misses;
	int hits;

private:
	ValueFunction stateValue;
};

template<class Status>
TranspositionTable<Status>::TranspositionTable(const size_t& size, const ValueFunction& stateValue)
: MemoryManager<Status>{size}
, stateValue{stateValue} {misses = hits = 0;}


template<class Status>
std::pair<bool, Status*> TranspositionTable<Status>::getOrCreate(const engine::Hash& hash) {
	size_t id = hash % size;
	Status* candidate = nullptr;
	double worstVal = engine::INF;
	double tmp;

	++hits;

	for (size_t i = id; i < std::min(id + 4, size); ++i)
		if (memory[i].hash == hash)
			return {true, &(memory[i])};
		else if ((tmp = stateValue(memory + i)) < worstVal) {
			worstVal = tmp;
			candidate = memory + i;
		}

	++misses;
	candidate->reset();
	candidate->hash = hash;
	return {false, candidate};
}


#endif // TRANSPOSITION_TABLE_HPP