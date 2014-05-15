#ifndef STATUS_HPP
#define STATUS_HPP
#include <cstddef>
#include "../Engine/engine.hpp"
#include "../Engine/Board.hpp"

class StatusTemplate {
public:
	virtual void reset() = 0;
	virtual ~StatusTemplate() {};
};

class GraphStatus : public StatusTemplate {
public:
	GraphStatus();
	engine::Hash hash;
	virtual void reset();
};


class MCTSStatus : public StatusTemplate {
public:
	MCTSStatus();
	virtual void reset();

	uint32_t wins, plays;
};

class TreeMCTSStatus : public MCTSStatus {
public:
	TreeMCTSStatus();
	TreeMCTSStatus* getFirstChild() const;
	size_t getNumChildren() const;
	void setChildren(TreeMCTSStatus* firstChild, const size_t& numChildren);
	virtual void reset();

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
	virtual void reset();

	int result;
	unsigned int depth;
	BoundType type;
};



#endif // STATUS_HPP
