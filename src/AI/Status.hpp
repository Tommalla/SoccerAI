#ifndef STATUS_HPP
#define STATUS_HPP
#include <cstddef>
#include "../Engine/engine.hpp"
#include "../Engine/Board.hpp"

template<class Stat>
class StatusTemplate {
public:
	StatusTemplate();
	Stat* getFirstChild() const;
	size_t getNumChildren() const;
	void setChildren(Stat* firstChild, const size_t& numChildren);
	void setHash(const engine::Hash& hash);
	engine::Hash getHash() const;
	virtual void reset();

private:
	engine::Hash hash;
	Stat* firstChild;
	size_t numChildren;
};

class MCTSStatus : public StatusTemplate<MCTSStatus> {
public:
	MCTSStatus();
	virtual void reset();
	uint32_t wins, plays;
	DirId lastMoveId;
};

template<class Stat>
StatusTemplate<Stat>::StatusTemplate()
: firstChild{nullptr}
, numChildren{0} {}

template<class Stat>
Stat* StatusTemplate<Stat>::getFirstChild() const {
	return firstChild;
}

template<class Stat>
size_t StatusTemplate<Stat>::getNumChildren() const {
	return numChildren;
}

template<class Stat>
void StatusTemplate<Stat>::setChildren(Stat* firstChild, const size_t& numChildren) {
	this->firstChild = firstChild;
	this->numChildren = numChildren;
}

template<class Stat>
void StatusTemplate<Stat>::setHash(const engine::Hash& hash) {
	this->hash = hash;
}

template<class Stat>
engine::Hash StatusTemplate<Stat>::getHash() const {
	return hash;
}

template<class Stat>
void StatusTemplate<Stat>::reset() {
	firstChild = nullptr;
	numChildren = 0;
	hash = 0;
}

#endif // STATUS_HPP
