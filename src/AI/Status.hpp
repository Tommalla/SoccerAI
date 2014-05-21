#ifndef STATUS_HPP
#define STATUS_HPP
#include <cstddef>
#include "../Engine/engine.hpp"
#include "../Engine/Board.hpp"

template<class Status>
inline void resetStatus(Status* stat) {
	static_assert(sizeof(Status) == 0, "No specialization for this type of argument!");
}

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

class GraphMCTSStatus: public GraphStatus, public MCTSStatus {
public:
	GraphMCTSStatus();

	uint8_t value;
};

class TreeMCTSStatus : public MCTSStatus {
	friend void resetStatus<TreeMCTSStatus>(TreeMCTSStatus* stat);
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


template<>
inline void resetStatus<GraphStatus>(GraphStatus* stat) {
	stat->hash = 0;
}

template<>
inline void resetStatus<MCTSStatus>(MCTSStatus* stat) {
	stat->plays = stat->wins = 0;
}

template<>
inline void resetStatus<GraphMCTSStatus>(GraphMCTSStatus* stat) {
	resetStatus<GraphStatus>(stat);
	resetStatus<MCTSStatus>(stat);
	stat->value = 0;
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
