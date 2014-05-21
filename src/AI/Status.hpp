#ifndef STATUS_HPP
#define STATUS_HPP
#include <cstddef>
#include "../Engine/engine.hpp"
#include "../Engine/Board.hpp"

class GraphStatus {
public:
	GraphStatus();
	engine::Hash hash;
};


class MCTSStatus {
public:
	MCTSStatus();

	uint32_t wins, plays;
};

class TreeMCTSStatus : public MCTSStatus {
	template<class Status>
	friend void resetStatus(Status* stat);
public:
	TreeMCTSStatus();
	TreeMCTSStatus* getFirstChild() const;
	size_t getNumChildren() const;
	void setChildren(TreeMCTSStatus* firstChild, const size_t& numChildren);

	DirId lastMoveId;

private:
	TreeMCTSStatus* firstChild;
	size_t numChildren;
};

class AlphaBetaStatus : public GraphStatus {
public:
	enum class BoundType: uint8_t {
		UPPER,
		LOWER,
		EXACT
	};

	AlphaBetaStatus();

	int result;
	unsigned int depth;
	BoundType type;
};


template<class Status>
inline void resetStatus(Status* stat);

template<>
inline void resetStatus<GraphStatus>(GraphStatus* stat) {
	stat->hash = 0;
}

template<>
inline void resetStatus<MCTSStatus>(MCTSStatus* stat) {
	stat->plays = stat->wins = 0;
}

template<>
inline void resetStatus<TreeMCTSStatus>(TreeMCTSStatus* stat) {
	resetStatus<MCTSStatus>(stat);
	stat->lastMoveId = -1;
	stat->firstChild = nullptr;
	stat->numChildren = 0;
}

template<>
inline void resetStatus<AlphaBetaStatus>(AlphaBetaStatus* stat) {
	resetStatus<GraphStatus>(stat);
	stat->result = 0;
}

#endif // STATUS_HPP
