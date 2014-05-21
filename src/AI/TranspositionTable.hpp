#ifndef TRANSPOSITION_TABLE_HPP
#define TRANSPOSITION_TABLE_HPP
#include <algorithm>
#include "MemoryManager.hpp"

template<class Status>
class TranspositionTable : public MemoryManager<Status> {
	using MemoryManager<Status>::end;
	using MemoryManager<Status>::size;
	using MemoryManager<Status>::memory;
	typedef std::function<bool(Status*, Status*)> CompareFunction;

public:
	class NoSuchElement : public std::exception {
		const char * what () noexcept {
			return "Element not found in TT.";
		}
	};

	TranspositionTable(const size_t& size, const CompareFunction& isWorse);
	std::pair< bool, Status* > getOrCreate(const engine::Hash& hash);
	bool exists(const engine::Hash& hash) const;
	Status* get(const engine::Hash& hash) const;

	int misses;
	int hits;

private:
	CompareFunction isWorse;
};

template<class Status>
TranspositionTable<Status>::TranspositionTable(const size_t& size, const CompareFunction& isWorse)
: MemoryManager<Status>{size}
, isWorse {isWorse} {misses = hits = 0;}


template<class Status>
std::pair<bool, Status*> TranspositionTable<Status>::getOrCreate(const engine::Hash& hash) {
	size_t id = hash % size;
	size_t searchEnd = std::min(id + 4, size);
	Status* candidate = nullptr;

	++hits;

	for (size_t i = id; i < searchEnd; ++i)
		if (memory[i].hash == hash)
			return {true, &(memory[i])};
		else if (candidate == nullptr || isWorse(memory + i, candidate))
			candidate = memory + i;

	++misses;
	resetStatus<Status>(candidate);
	candidate->hash = hash;
	return {false, candidate};
}

template<class Status>
bool TranspositionTable<Status>::exists(const engine::Hash& hash) const {
	size_t id = hash % size;
	size_t searchEnd = std::min(id + 4, size);

	for (size_t i = id; i < searchEnd; ++i)
		if (memory[i].hash == hash)
			return true;

	return false;
}

template<class Status>
Status* TranspositionTable<Status>::get(const engine::Hash& hash) const {
	size_t id = hash % size;
	size_t searchEnd = std::min(id + 4, size);

	for (size_t i = id; i < searchEnd; ++i)
		if (memory[i].hash == hash)
			return memory + i;

	throw NoSuchElement{};
}


#endif // TRANSPOSITION_TABLE_HPP