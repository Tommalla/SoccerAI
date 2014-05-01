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
	virtual void reset();

private:
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

class AlphaBetaStatus : public StatusTemplate<AlphaBetaStatus> {
public:
	AlphaBetaStatus();
	virtual void reset();

	engine::Hash hash;
	int alpha, beta;
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
void StatusTemplate<Stat>::reset() {
	firstChild = nullptr;
	numChildren = 0;
}

#endif // STATUS_HPP
